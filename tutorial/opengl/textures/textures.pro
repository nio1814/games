#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T06:35:55
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = texture
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    glwidget.cpp

HEADERS  += window.h \
    glwidget.h

DISTFILES +=

RESOURCES += \
    textures.qrc
