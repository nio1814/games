#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T02:20:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = marble
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    ../lib/src/gameobject.cpp \
    commands.cpp \
    ../lib/src/mouse.cpp \
    ../lib/src/qtgl.cpp \
    ../lib/src/vector3d.cpp \
    ../lib/src/object.cpp \
    ../lib/src/camera.cpp \
    ../lib/src/keys.cpp \
    ../lib/src/3dsGT/3ds.cpp \
    ../lib/src/3dsGT/3dsLoader.cpp \
    ../lib/src/mass.cpp \
    ../lib/src/menu.cpp \
    ../lib/src/masking.cpp \
    ../lib/src/datastructs.cpp \
    ../lib/src/texturecode.cpp

HEADERS  += mainwindow.h \
    ../lib/src/gameobject.h \
    commands.h \
    glwidget.h \
    ../lib/src/3dsGT/3ds.h \
    ../lib/src/mouse.h \
    ../lib/src/qtgl.h \
    ../lib/src/vector3d.h \
    ../lib/src/object.h \
    ../lib/src/camera.h \
    ../lib/src/keys.h \
    ../lib/src/3dsGT/3dsLoader.h \
    ../lib/src/mass.h \
    ../lib/src/menu.h \
    ../lib/src/masking.h \
    ../lib/src/datastructs.h \
    ../lib/src/texturecode.h
