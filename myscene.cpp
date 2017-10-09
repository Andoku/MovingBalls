#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <chrono>

#include "myscene.h"
#include "utils.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent),
    running(true),
    t(&MyScene::physicsThread, this) {}

MyScene::~MyScene()
{
    running = false;
    t.join();
    removeAllBalls();
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
    Ball *ball = qgraphicsitem_cast<Ball *>(item);

    if (mouseEvent->button() == Qt::RightButton) {
        if(ball) {
            removeBall(ball);
        } else {
            addBall(mouseEvent->scenePos());
        }
    } else {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void MyScene::addBall(QPointF pos)
{
    std::lock_guard<std::mutex> lock(ballsMutex);
    balls.push_back(new Ball(pos));
    addItem(balls.back());
}

void MyScene::removeBall(Ball *ball)
{
    std::lock_guard<std::mutex> lock(ballsMutex);
    balls.erase(std::remove(balls.begin(), balls.end(), ball), balls.end());
    removeItem(ball);
    delete ball;
}

void MyScene::removeAllBalls()
{
    std::lock_guard<std::mutex> lock(ballsMutex);
    clear();
    balls.clear();
}

void MyScene::updateBalls()
{
    const int k = 1000;

    std::lock_guard<std::mutex> lock(ballsMutex);
    static auto updateTime = std::chrono::system_clock::now();
    std::vector< std::vector<QPointF> > newBalls;
    for(size_t i = 0; i < balls.size(); ++i) {
        QPointF xy1 = balls[i]->getPos();
        QPointF V1 = balls[i]->getV();

        qreal radius = balls[i]->getRadius() * k;
        qreal ax = 0;
        qreal ay = 0;
        for(size_t j = 0; j < balls.size(); ++j) {
            if(i == j)
                continue;

            QPointF xy2 = balls[j]->getPos();
            qreal r = distance(xy1, xy2) * k;
            qreal F = (r <= radius) ? (1/radius - 1/(radius*radius)): (1/r - 1/(r*r));
            QPointF xy = xy2 - xy1;
            qreal alpha = (r == 0) ? 0 : atan2(xy.ry(), xy.rx());
            ax += F * cos(alpha);
            ay += F * sin(alpha);
        }

        auto currentTime = std::chrono::system_clock::now();
        double t = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - updateTime).count();

        QPointF xy;
        xy.setX(xy1.rx() + V1.rx()*t + ax*t*t/2);
        xy.setY(xy1.ry() + V1.ry()*t + ay*t*t/2);
        QPointF V(V1.rx() + ax*t, V1.ry() + ay*t);

        newBalls.push_back({xy, V});
    }

    for(size_t i = 0; i < balls.size(); ++i) {
        balls[i]->setState(newBalls[i][0], newBalls[i][1]);
    }

    updateTime = std::chrono::system_clock::now();
}

void MyScene::physicsThread()
{
    const int frequency = 50;
    while(running) {
        const auto start = std::chrono::system_clock::now();
        updateBalls();
        const auto end = std::chrono::system_clock::now();
        int difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        int toSleep = 1000000 / frequency - difference;
        toSleep = (toSleep > 0) ? toSleep : 0;
        std::this_thread::sleep_for(std::chrono::microseconds(toSleep));
    }
}
