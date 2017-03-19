#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T23:55:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CachedTable
TEMPLATE = app


SOURCES += main.cpp\
        tableeditor.cpp \
    connection.cpp

HEADERS  += tableeditor.h \
    connection.h
