#ifndef GLWIDGET_H
#define GLWIDGET_H

//#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
class GLWidget : public QOpenGLWidget
#else
#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
#endif
{
public:
    GLWidget(QWidget *parent);

signals:

public slots:
};

#endif // GLWIDGET_H
