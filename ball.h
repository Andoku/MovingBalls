#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <mutex>

class Ball : public QGraphicsItem
{
public:
    Ball(QPointF pos, QPointF V = QPointF(0, 0), QGraphicsItem *parent = 0);

    void setState(QPointF pos, QPointF V = QPointF(0, 0));
    QPointF getPos();
    QPointF getV();
    qreal getRadius();

protected:
    void advance(int step) override;
private:
    QPointF xy;
    QPointF V;
    qreal radius;

    std::mutex stateMutex;

    QColor color;

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MOVEITEM_H
