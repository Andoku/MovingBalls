#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <mutex>

class Ball : public QGraphicsItem
{
public:
    Ball(QPointF pos, QPointF V = QPointF(0, 0), QGraphicsItem *parent = 0);

    /**
     * @brief Установить состояние шарика
     * @param[in] pos новые координаты шарика
     * @param[in] V новая скорость шарика
     */
    void setState(QPointF pos, QPointF V = QPointF(0, 0));

    /**
     * @brief Получить координаты шарика
     * @return координаты шарика (x, y)
     */
    QPointF getPos();

    /**
     * @brief Получить скорость шарика
     * @return скорость шарика (Vx, Vy)
     */
    QPointF getV();

    /**
     * @brief Получить радиус шарика
     * @return радиус шарика в пикселях
     */
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
