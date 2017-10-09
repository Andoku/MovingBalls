#include <QCursor>
#include <QPainter>

#include "ball.h"
#include "utils.h"

Ball::Ball(QPointF pos, QPointF V, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    xy(pos),
    V(V),
    radius(30)
{
    const int r = randomBetween(0, 255);
    const int g = randomBetween(0, 255);
    const int b = randomBetween(0, 255);
    color = QColor(r, g, b);
    this->setPos(xy);
}

void Ball::setState(QPointF pos, QPointF V)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    this->xy = pos;
    this->V = V;
}

QPointF Ball::getPos()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return xy;
}

QPointF Ball::getV()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return V;
}

qreal Ball::getRadius()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return radius;
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF Ball::boundingRect() const
{
    return QRectF(-radius, -radius, 2*radius, 2*radius);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ball::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setState(mapToScene(event->pos()));
}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    setState(mapToScene(event->pos()));
}

void Ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Ball::advance(int step)
{
    if (!step)
        return;

    this->setPos(getPos());
}
