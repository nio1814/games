#include "glwidget.h"

#include "qtlogo.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
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
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

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
