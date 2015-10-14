#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>

#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
class GLWidget : public QOpenGLWidget
#else
#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
#endif
{
	Q_OBJECT
public:
    GLWidget(QWidget *parent);

signals:

public slots:

};

#endif // GLWIDGET_H
