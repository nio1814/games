#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T21:42:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rubik
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui
