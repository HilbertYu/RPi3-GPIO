#-------------------------------------------------
#
# Project created by QtCreator 2017-06-11T11:46:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gpioclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    hysocket.h

FORMS    += mainwindow.ui
