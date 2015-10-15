#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>

//#include "vector3d.h"
#include "shape.h"

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
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
signals:

public slots:
    void animate();

private:
    int runControls();

    bool light;
    Vector2D fovAngle;
    rcube_c rcube;
    int m_windowSizeX;
    int m_windowSizeY;
    Vector3D moslook;
};

#endif // GLWIDGET_H
