#include "glwidget.h"

#include <QKeyEvent>

#include "camera.h"
#include "keys.h"
#include "constants.h"
#include "mouse.h"
#include "qtgl.h"

#define CAMOVESPEED 2.0f

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
        : QOpenGLWidget(parent)
#else
	   : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		m_twisting(false), m_timer(NULL)
#endif
{
    setMouseTracking(true);

	fovAngle = Vector2D(0.0f,45.0f);
	cam = new CameraPoint(Vector3D(0.0f,0.0f,6.0f),Vector3D(0,0,0),Y,6.0f);
    mouse = new Mouse(m_windowSizeX,m_windowSizeY);
	m_timer = new QTimer;

    light.pos = Vector3D(rand()*5.0f/RAND_MAX+2,rand()*5.0f/RAND_MAX+2,rand()*5.0f/RAND_MAX+2);
	light.ambient = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	light.diffuse = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
    light.specular = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	/*light.ambient = Vector3D(.10f,.10f,.10f);
	light.diffuse = Vector3D(1,1,1);
	light.specular = Vector3D(1,1,1);*/

  GLfloat LightAmbient[]=		{ 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat LightPosition[]=	{ 5.0f, 5.0f, 6.0f, 1.0f };

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

//    SetCursorPos(m_windowSizeX/2, m_windowSizeY/2);
}

GLWidget::~GLWidget()
{
	delete cam;
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(40,30);
}

QSize GLWidget::sizeHint() const
{
	return QSize(1000,700);
}

void GLWidget::initializeGL()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.2f, 0.2f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);

    light.enable();
    lightActive = false;

	return;
}

void GLWidget::resizeGL(int w, int h)
{
	if (h==0)										// Prevent A Divide By Zero By
		h=1;										// Making Height Equal One

	m_windowSizeX = w;
    m_windowSizeY = h;
    mouse->screenWidth = w;
    mouse->screenHeight = h;

	glViewport(0,0,w,h);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
										// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
//	gluPerspective(fovAngle.y,(GLfloat)w/(GLfloat)h,clipClose,clipFar);
	fovAngle.x = (GLfloat)w/(GLfloat)h*fovAngle.y;
    glPerspective(fovAngle.y, (GLfloat)w/(GLfloat)h, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

void GLWidget::paintGL()
{

}

void GLWidget::runUpdate()
{
#if (QT_VERSION >= 0x050500)
	update();
#else
	updateGL();
#endif
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	keyDown(event->key());

//	if(m_timer.isNull())
//	{
//		m_timer = new QTimer;
//		connect(m_timer, SIGNAL(timeout()), this, SLOT(runKeys()));
//		m_timer->start(50);
//	}
	emit runKeys();

	return;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	keyUp(event->key());
//	delete m_timer;

	return;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mouse->btnDown(event->button());
//    mos->updatePos(event->pos());

    return;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouse->updatePos(event->pos());

    emit runMouse();
    emit animate();

    return;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse->btnUp(event->button());

    return;
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    mouse->wheelOld = mouse->wheel;
    mouse->wheel += event->delta();

    emit runMouse();
    emit animate();

    return;
}
