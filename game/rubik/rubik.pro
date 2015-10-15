#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T21:42:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rubik
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    Lesson5.cpp \
    shape.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    shape.h

FORMS    += mainwindow.ui
