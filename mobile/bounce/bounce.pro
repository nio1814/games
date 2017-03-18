#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T14:44:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bounce
TEMPLATE = app

INCLUDEPATH += ../../game/lib/src/
INCLUDEPATH += ../bouncing

win32 {
	LIBS += -lopengl32
}

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    ../bouncing/object_2.cpp \
    ../bouncing/objects.cpp \
    ../../game/lib/src/ellipse.cpp \
    ../../game/lib/src/vector3d.cpp \
    ../../game/lib/src/mass.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    ../bouncing/object_2.h \
    ../bouncing/objects.h \
    ../../game/lib/src/ellipse.h \
    ../../game/lib/src/vector3d.h \
    ../../game/lib/src/mass.h

CONFIG += mobility
MOBILITY = 

