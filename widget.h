#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include <ball.h>
#include "myscene.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    MyScene *scene;
    QTimer timer;
};

#endif // WIDGET_H
