#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T23:10:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = btchat
TEMPLATE = app


SOURCES += main.cpp\
        remoteselector.cpp \
    chatserver.cpp

HEADERS  += remoteselector.h \
    chatserver.h

FORMS    += remoteselector.ui
