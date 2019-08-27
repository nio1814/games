#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T00:52:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stick
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    simulation.cpp \
    ../lib/src/qtgl.cpp \
    ../lib/src/camera.cpp \
    ../lib/src/object.cpp \
    ../lib/src/vector3d.cpp \
    ../lib/src/keys.cpp \
    ../lib/src/mass.cpp \
    ../lib/src/sphere.cpp \
    ../lib/src/datastructs.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    simulation.h \
    ../lib/src/qtgl.h \
    ../lib/src/camera.h \
    ../lib/src/object.h \
    ../lib/src/vector3d.h \
    ../lib/src/keys.h \
    ../lib/src/mass.h \
    ../lib/src/sphere.h \
    ../lib/src/datastructs.h
