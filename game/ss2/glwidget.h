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

	void runUpdate();

	QPointer<QTimer> m_timer;
	int m_windowSizeX;
	int m_windowSizeY;
signals:

public slots:
	virtual void animate() {}

	virtual void runKeys() {}

	virtual void runMouse() {}
};

#endif // GLWIDGET_H
