#-------------------------------------------------
#
# Project created by QtCreator 2015-09-27T21:48:17
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint2d
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    helper.cpp \
    window.cpp \
    glwidget.cpp

HEADERS  += widget.h \
    helper.h \
    window.h \
    glwidget.h