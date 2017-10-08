#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <mutex>

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Ball(QPointF pos, QPointF V = QPointF(0, 0), QObject *parent = 0);
    ~Ball();

    void setState(QPointF pos, QPointF V = QPointF(0, 0));
    void getState(QPointF *pos, QPointF *V);
    std::chrono::system_clock::time_point getTime();

protected:
    void advance(int step) override;
private:
    QPointF xy;
    QPointF V;
    std::chrono::system_clock::time_point updateTime;
    std::mutex stateMutex;

    QColor color;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MOVEITEM_H
