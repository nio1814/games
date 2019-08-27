#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T01:34:44
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssgame
TEMPLATE = app

INCLUDEPATH += ../lib/src src

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    ../lib/src/datastructs.cpp \
    src/movement.cpp \
    src/animation.cpp \
    src/objects.cpp \
    ../lib/src/keys.cpp \
    ../lib/src/vector3d.cpp \
    ../lib/src/constants.cpp \
    src/text.cpp \
    src/screen.cpp \
    ../lib/src/texturecode.cpp \
    ../lib/src/camera.cpp \
    ../lib/src/masking.cpp \
    src/functions.cpp \
    src/playerkeys.cpp \
    src/sound.cpp \
    ../lib/src/fmod/fmod.cpp \
    src/tga.cpp \
    src/level.cpp \
    src/game.cpp \
    ../lib/src/qtgl.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    ../lib/src/datastructs.h \
    src/movement.h \
    src/animation.h \
    src/objects.h \
    ../lib/src/keys.h \
    ../lib/src/vector3d.h \
    ../lib/src/constants.h \
    src/text.h \
    src/screen.h \
    ../lib/src/texturecode.h \
    ../lib/src/camera.h \
    ../lib/src/src/masking.h \
    src/functions.h \
    src/playerkeys.h \
    src/sound.h \
    ../lib/src/qtgl.h \
    src/game.h \
    src/level.h

FORMS    += mainwindow.ui

DISTFILES += \
    src/fmodvc.lib \
    src/fmod.dll \
    src/pspbrwse.jbf

RESOURCES += \
    ssgame.qrc
