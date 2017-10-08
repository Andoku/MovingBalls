#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <vector>
#include <thread>

#include "ball.h"

class MyScene : public QGraphicsScene
{
public:
    MyScene(QObject *parent = Q_NULLPTR);
    ~MyScene();

    void addBall(qreal x, qreal y);
    void removeBall(Ball *ball);
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
