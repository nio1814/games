#include "glwidget.h"

#include "qtlogo.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), scale(16)
{
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GLWidget::initializeGL()
{
    qglClearColor(Qt::blue);

    logo = new QtLogo(this, 64);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(xRot/scale, 1, 0, 0);
    glRotatef(yRot/scale, 0, 1, 0);
    glRotatef(zRot/scale, 0, 0, 1);

    logo->draw();
}

void GLWidget::setXRotation(int angle)
{
    if(angle!=xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    if(angle!=yRot)
    {
	   yRot = angle;
	   emit yRotationChanged(angle);
	   updateGL();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();

	return;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();

	if (event->buttons() & Qt::LeftButton) {
		setYRotation(yRot + .5*scale*dx);
	}

	lastPos = event->pos();
}
