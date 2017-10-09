#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <vector>
#include <thread>
#include <atomic>

#include "ball.h"

class MyScene : public QGraphicsScene
{
public:
    MyScene(QObject *parent = Q_NULLPTR);
    ~MyScene();

    /**
     * @brief Добавить новый шарик
     * @param[in] pos координаты нового шарика
     */
    void addBall(QPointF pos);

    /**
     * @brief Удалить шарик
     * @param[in] ball указатель на шарик, которые надо удалить
     */
    void removeBall(Ball *ball);

    /**
     * @brief Удалить все шарики
     */
    void removeAllBalls();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    std::mutex ballsMutex;
    std::vector<Ball *> balls;
    std::atomic<bool> running;
    std::thread t;

    void physicsThread();
    void updateBalls();
};

#endif // MYSCENE_H
