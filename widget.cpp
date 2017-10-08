#include <QDateTime>

#include "widget.h"
#include "ui_widget.h"
#include "utils.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(640, 640);
    this->setFixedSize(640, 640);

    scene = new MyScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->resize(600, 600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0, 0, 500, 500);

    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer.start(1000 / 50);
}

Widget::~Widget()
{
    delete scene;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    scene->removeAllBalls();

    const int minNumberOfCircles = 2;
    const int maxNumberOfCircles = 10;
    const int numberOfCircles = randomBetween(minNumberOfCircles, maxNumberOfCircles);

    for(int i = 0; i < numberOfCircles; ++i) {
        scene->addBall(randomBetween(30, 470), randomBetween(30, 470));
    }
}
