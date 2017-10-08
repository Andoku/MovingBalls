#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T09:49:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoveGraphicsItem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myscene.cpp \
    ball.cpp

HEADERS  += widget.h \
    utils.h \
    myscene.h \
    ball.h

FORMS    += widget.ui
