#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T01:34:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssgame
TEMPLATE = app

INCLUDEPATH += ../lib/src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    src/game.cpp \
    src/world.cpp \
    ../lib/src/datastructs.cpp \
    src/movement.cpp \
    src/animation.cpp \
    src/objects.cpp \
    ../lib/src/keys.cpp \
    ../lib/src/vector3d.cpp \
    ../lib/src/tga.cpp \
    ../lib/src/constants.cpp \
    src/text.cpp \
    src/screen.cpp \
    src/texturecode.cpp \
    ../lib/src/camera.cpp \
    src/masking.cpp \
    src/functions.cpp \
    src/playerkeys.cpp \
    src/sound.cpp \
    ../lib/src/fmod/fmod.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    src/world.h \
    ../lib/src/datastructs.h \
    src/movement.h \
    src/animation.h \
    src/objects.h \
    ../lib/src/keys.h \
    ../lib/src/vector3d.h \
    ../lib/src/tga.h \
    ../lib/src/constants.h \
    src/text.h \
    src/screen.h \
    src/texturecode.h \
    ../lib/src/camera.h \
    src/masking.h \
    src/functions.h \
    src/playerkeys.h \
    src/sound.h

FORMS    += mainwindow.ui

DISTFILES += \
    src/fmodvc.lib \
    src/fmod.dll \
    src/pspbrwse.jbf
