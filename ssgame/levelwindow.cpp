#include "levelwindow.h"

#include <qtimer.h>

#include "game.h"
#include "level.h"
#include "keys.h"
#include "playerkeys.h"

LevelWindow::LevelWindow(QWidget *parent) : GLWidget(parent), m_elapsed(0)
{
    m_game = new Game();
    m_game->addLevel(1);

    assignControls();
}

void LevelWindow::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = {.5, 5, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_TEXTURE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    doTextures();
    m_game->level().initTextures();

    return;
}

void LevelWindow::resizeGL(int w, int h)
{
    if (h==0)								// Prevent A Divide By Zero By
        h=1;							// Making Height Equal One

    glViewport(0, 0, w, h);					// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();							// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
//    glPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    m_projection.setToIdentity();
    m_projection.perspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    m_aspectRatio = (qreal)w / (qreal)(h ? h : 1);
//    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
//    glFrustum(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, 4.0f, 15.0f);
//    glOrtho(-2, 2, -2, 2, 1.5, 20);
//    glOrtho();
    glFrustum(-2,2,-2,2,1.5,20);

    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
    glLoadIdentity();							// Reset The Modelview Matrix

    return;
}

void LevelWindow::paintGL()
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

    m_game->draw();

    return;
}

void LevelWindow::keyPressEvent(QKeyEvent *event)
{
	return keyDown(event->key());
}

void LevelWindow::keyReleaseEvent(QKeyEvent *event)
{
	return keyUp(event->key());
}

void LevelWindow::mousePressEvent(QMouseEvent *event)
{
//	return keyDown(event->button()+255);
}

void LevelWindow::animate()
{
//    const int timeDelta = qobject_cast<QTimer*>(sender())->interval();
    const qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    const qint64 timeDelta = m_previousRenderTime > 0 ? currentTime - m_previousRenderTime : 0;
      m_game->update(timeDelta * 1e-3);
    m_previousRenderTime = currentTime;
      m_elapsed += timeDelta;
    update();

    return;
}
