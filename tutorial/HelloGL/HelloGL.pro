#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T14:02:02
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    glwidget.cpp \
    qtlogo.cpp

HEADERS  += window.h \
    glwidget.h \
    qtlogo.h
