#include <QCursor>
#include <QPainter>

#include "ball.h"
#include "utils.h"

Ball::Ball(QPointF pos, QPointF V, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    xy(pos),
    V(V),
    updateTime(std::chrono::system_clock::now())
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
    updateTime = std::chrono::system_clock::now();
}

void Ball::getState(QPointF *pos, QPointF *V)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    *pos = this->xy;
    *V = this->V;
}

std::chrono::system_clock::time_point Ball::getTime()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return updateTime;
}

QRectF Ball::boundingRect() const
{
    return QRectF(-30, -30, 60, 60);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(color);
    painter->drawEllipse(-30, -30, 60, 60);
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

    QPointF pos;
    QPointF V;
    getState(&pos, &V);
    this->setPos(pos);
}
