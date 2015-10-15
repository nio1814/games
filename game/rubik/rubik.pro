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
    shape.cpp \
    ../lib/src/vector3d.cpp \
    ../lib/src/camera.cpp \
    ../lib/src/keys.cpp \
    ../lib/src/qtgl.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    shape.h \
    ../lib/src/vector3d.h \
    ../lib/src/camera.h \
    ../lib/src/keys.h \
    ../lib/src/qtgl.h

FORMS    += mainwindow.ui
