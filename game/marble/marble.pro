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

HEADERS  += mainwindow.h \
    ../lib/src/gameobject.h \
    commands.h \
    glwidget.h
