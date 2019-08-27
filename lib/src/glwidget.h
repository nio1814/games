#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGlobal>
#include <qpointer.h>
#include <qtimer.h>

#include "light.h"

QT_FORWARD_DECLARE_CLASS(CameraPoint)
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
	void runUpdate();

	bool lightActive;
	CameraPoint* cam;
	Mouse* mos;
	Vector3D moslook;
	QPointer<QTimer> m_timer;
	Vector2D fovAngle;
	int m_windowSizeX;
	int m_windowSizeY;
signals:

public slots:
	virtual void animate() {}

	virtual void runKeys() {}

	virtual void runMouse() {}

private:
	Light light;
    bool m_twisting;
};

#endif // GLWIDGET_H
