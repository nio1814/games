#include "glwidget.h"

#include <qtimer.h>

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
    : QOpenGLWidget(parent)
#else
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
    m_elapsed = 0;
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

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    glBegin(GL_TRIANGLES);
//    glColor3f(.3, .1, .7);
    glColor3f(qrand()/(float)RAND_MAX, qrand()/(float)RAND_MAX, qrand()/(float)RAND_MAX);
    glVertex3f(0,0,0);
    glVertex3f(1,m_elapsed/10000.0,0);
    glVertex3f(0,1,0);
    glEnd();

    return;
}

void GLWidget::animate()
{
    m_elapsed += qobject_cast<QTimer*>(sender())->interval();
    update();
}
