TEMPLATE = app

QT += qml quick opengl
CONFIG += c++11

win32 {
	LIBS += -lopengl32
}

SOURCES += main.cpp \
    scene.cpp \
    scenerenderer.cpp \
    ../../game/lib/src/ellipse.cpp \
    ../../game/lib/src/vector3d.cpp \
    objects.cpp \
    object_2.cpp

RESOURCES += qml.qrc

INCLUDEPATH += ../../game/lib/src

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    scene.h \
    scenerenderer.h \
    ../../game/lib/src/ellipse.h \
    ../../game/lib/src/vector3d.h \
    objects.h \
    object_2.h
