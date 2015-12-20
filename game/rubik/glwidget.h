#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>
#include <qpointer.h>
#include <qtimer.h>

#include "shape.h"
#include "light.h"

class CameraPoint;
class QTimer;
class Mouse;

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
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* );

signals:

public slots:
    void animate();
    void runKeys();
    void runMouse();

private:
	void rotateLR(GLfloat angle);
	void rotateUD(GLfloat angle);

    bool lightActive;
	Light light;
    CameraPoint* cam;
    Vector2D fovAngle;
    rcube_c rcube;
    bool m_twisting;
    int m_windowSizeX;
    int m_windowSizeY;
    Mouse* mos;
    Vector3D moslook;
    QPointer<QTimer> m_timer;
};

#endif // GLWIDGET_H
