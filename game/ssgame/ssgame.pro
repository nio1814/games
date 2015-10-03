#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T01:34:44
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssgame
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    src/game.cpp \
    src/world.cpp \
    ../lib/src/tga.cpp \
    ../lib/src/datastructs.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    src/world.h \
    ../lib/src/tga.h \
    ../lib/src/datastructs.h

FORMS    += mainwindow.ui

DISTFILES += \
    src/fmodvc.lib \
    src/fmod.dll \
    src/pspbrwse.jbf
