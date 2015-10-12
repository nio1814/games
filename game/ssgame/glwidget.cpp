#include "glwidget.h"

#include <qtimer.h>

#include "game.h"
#include "level.h"
#include "keys.h"
#include "playerkeys.h"

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
    : QOpenGLWidget(parent)
#else
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
    m_elapsed = 0;
    m_game = new Game();
    m_game->addLevel(0);
    doTextures();
    assignControls();
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

//    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = {.5, 5, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

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
    m_aspectRatio = (qreal)w / (qreal)(h ? h : 1);
//    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
//    glFrustum(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, 4.0f, 15.0f);
//    glOrtho(-.5, .5, -.5, .5, 4, 15);
//    glOrtho();
    glFrustum(-2,2,-2,2,1.5,20);

    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
//    glLoadIdentity();							// Reset The Modelview Matrix

    return;
}

void GLWidget::paintGL()
{
     GLfloat T = 10000;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat x = 0.1*m_elapsed/10000.0f;
    GLfloat y = 0.03*m_elapsed/10000.0f;
    GLfloat z = 1*m_elapsed/10000.0f;
//    m_model.translate(x,y,0);

//     glTranslatef(x,y,-z);
    glTranslatef(0,0,-15);

//    glRotatef(10*m_elapsed/T,0,1,0);
//    glRotatef(100*m_elapsed/T,1,1,0);


    glBegin(GL_TRIANGLES);
//    glColor3f(.3, .1, .7);
    glColor3f(cos(m_elapsed/T), sin(m_elapsed/T*1.53), sin(m_elapsed/T*.42));
    glVertex3f(0,0,-1);
    glVertex3f(1,m_elapsed/10000.0,0);
    glVertex3f(0,1,0);
    glEnd();

    // draw a cube (6 quadrilaterals)
    glBegin(GL_QUADS);				// start drawing the cube.

    // top of cube
    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
    glNormal3f(0,1,0);
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)

    // bottom of cube
    glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
    glNormal3f(0,-1,0);
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Bottom)

    // front of cube
    glColor3f(1.0f,0.0f,0.0f);
    glNormal3f(0,0,1);// Set The Color To Red
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Front)

    // back of cube.
    glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
    glNormal3f(0,0,-1);
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Bottom Right Of The Quad (Back)

    // left of cube
    glColor3f(0.0f,0.0f,1.0f);			// Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Left)

    // Right of cube
    glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);	        // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Right)
    glEnd();


    m_game->draw();

    return;
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	return keyDown(event->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	return keyUp(event->key());
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
//	return keyDown(event->button()+255);
}

void GLWidget::animate()
{
    int dt = qobject_cast<QTimer*>(sender())->interval();

    m_game->update(dt*1e-3);

    m_elapsed += dt;
    update();

    return;
}
