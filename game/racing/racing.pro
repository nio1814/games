#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T07:56:53
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = racing
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    level.cpp \
    meshobject.cpp \
    ../lib/src/model3d.cpp \
    ../lib/src/vector3d.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    level.h \
    meshobject.h \
    ../lib/src/model3d.h \
    ../lib/src/vector3d.h
