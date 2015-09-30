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
    src/animation.cpp \
    src/dataStructs.cpp \
    src/error.cpp \
    src/functions.cpp \
    src/globalvar.cpp \
    src/headers.cpp \
    src/keys.cpp \
    src/masking.cpp \
    src/Masterx.cpp \
    src/movement.cpp \
    src/objects.cpp \
    src/screen.cpp \
    src/sound.cpp \
    src/text.cpp \
    src/Texture Code.cpp \
    src/TGA.cpp \
    src/world.cpp \
    ../lib/src/vector3d.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    src/animation.h \
    src/dataStructs.h \
    src/error.h \
    src/fmod.h \
    src/functions.h \
    src/globalvar.h \
    src/headers.h \
    src/keys.h \
    src/masking.h \
    src/Masterx.h \
    src/movement.h \
    src/objects.h \
    src/screen.h \
    src/sound.h \
    src/test2_private.h \
    src/text.h \
    src/Texture Code.h \
    src/TGA.h \
    src/world.h \
    ../lib/src/vector3d.h

FORMS    += mainwindow.ui

DISTFILES += \
    src/fmodvc.lib \
    src/fmod.dll \
    src/pspbrwse.jbf
