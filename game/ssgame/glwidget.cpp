#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
    : QOpenGLWidget(parent)
#else
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{

}

void GLWidget::initializeGL()
{

    return;
}

void GLWidget::resizeGL(int w, int h)
{
    if (h==0)								// Prevent A Divide By Zero By
        h=1;							// Making Height Equal One

    glViewport(0, 0, w, h);					// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();							// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
//    qgluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    m_projection.setToIdentity();
    m_projection.perspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
    glLoadIdentity();							// Reset The Modelview Matrix

    return;
}
