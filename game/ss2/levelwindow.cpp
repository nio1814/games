#include "levelwindow.h"

#include "level.h"
#include "camera.h"
#include "keys.h"

#include <QKeyEvent>

LevelWindow::LevelWindow(QWidget *parent) : GLWidget(parent)
{
	m_level = std::make_shared<Level>();

	m_keys = std::make_shared<Keys>();
	m_level->setKeys(m_keys);

	m_camera = std::make_unique<Camera>(Vector3D(0,0,5));

	m_timer = new QTimer(this);
	connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(run()));
//	connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start(50);
}

LevelWindow::~LevelWindow()
{
}

void LevelWindow::run()
{
	qint64 interval = QDateTime::currentDateTime().toMSecsSinceEpoch() - m_lastTime.toMSecsSinceEpoch();
	interval = std::min(interval, (qint64)100);
//	qWarning() << "update " << interval;

	m_level->update(interval*1e-3*m_throttle);

	m_lastTime = QDateTime::currentDateTime();

	update();
}

void LevelWindow::initializeGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(20.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

//	static GLfloat lightPosition[4] = {.5, 5, 7, 1};
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	GLenum error = glGetError();
	if(error!=GL_NO_ERROR)
		qWarning() << "Error " << error << " initializing GL";

	m_level->load();

	return;
}

void LevelWindow::resizeGL(int w, int h)
{
	if (h==0)								// Prevent A Divide By Zero By
		h=1;							// Making Height Equal One

	glViewport(0, 0, w, h);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix
	glEnable(GL_NORMALIZE);
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
//	qWarning() << "paint";
//	GLfloat T = 10000;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

//	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//	int elapsed = QDateTime::currentDateTime().toMSecsSinceEpoch();
//	GLfloat x = 0.1*elapsed/10000.0f;
//	GLfloat y = 0.03*elapsed/10000.0f;
//	GLfloat z = 1*elapsed/10000.0f;

	glLookAt(m_camera->position().vector(), m_camera->look().vector(), m_camera->up().vector());

	/*glBegin(GL_TRIANGLES);
	glColor3f(.3, .1, .7);
	glColor3f(cos(elapsed/T), sin(elapsed/T*1.53), sin(elapsed/T*.42));
	glVertex3f(0,0,-1);
	glVertex3f(1,elapsed/10000.0,0);
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
	glVertex3f( cos(elapsed/100), 1.0f, 1.0f);		// Top Right Of The Quad (Front)
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

//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
*/
	m_level->draw();

	return;
}

void LevelWindow::keyPressEvent(QKeyEvent *event)
{
//	(*m_keys)[event->key()] = true;
	m_keys->setKeyPressed(event->key(), true);

//	qWarning() << event->key();

	switch (event->key())
	{
		case Qt::Key_C:
			if (m_mode==GameMode)
				m_mode = CameraMode;
			else if (m_mode==CameraMode)
				m_mode = GameMode;
			break;
			qWarning() << m_mode;
	}

	switch (m_mode)
	{
		case GameMode:
//			m_level->updateKeys();
			break;
		case CameraMode:
			switch (event->key()) {
				case Qt::Key_Up:
					m_camera->position() += Vector3D(0,0,.1);
					break;
				case Qt::Key_Down:
					m_camera->position() -= Vector3D(0,0,.1);
					break;
				default:
					break;
			}
			break;
	}
}

void LevelWindow::keyReleaseEvent(QKeyEvent *event)
{
//	(*m_keys)[event->key()] = false;
	m_keys->setKeyPressed(event->key(), false);

//	m_level->updateKeys();
}

