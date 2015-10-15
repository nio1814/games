#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>

#include "shape.h"

class CameraPoint;
class QTimer;

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

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

signals:

public slots:
    void animate();
    void runKeys();

private:
    int runControls();
	void rotateLR(GLfloat angle);
	void rotateUD(GLfloat angle);

    bool lightActive;
//    light_c light;
    CameraPoint* cam;
    Vector2D fovAngle;
    rcube_c rcube;
    int m_windowSizeX;
    int m_windowSizeY;
    Vector3D moslook;
    QTimer *m_timer;
};

#endif // GLWIDGET_H
