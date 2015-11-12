#include "glwidget.h"

#include "level.h"
#include "meshobject.h"
#include "model3d.h"
#include "mass.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	m_timer = new QElapsedTimer;
	m_level = new Level;
	m_level->addLight(GL_LIGHT0, Vector3D(4,2,-2), Vector3D(0.6,0.5,0.5), Vector3D(0.8,1,0.8), Vector3D(1,1,1));	
	m_level->addPlayer(":data/mercedes3.ogl");
	m_level->player->mass->dir = Y;
	m_level->player->mesh->centerMesh();
	m_level->player->mass->pos = m_level->player->mesh->center;

	/*MeshObject *object = m_level->addObject(":data/track1_4.ogl");
//	m_level->addTexture("data/visa09.tga");
	object->mesh->scale(1500);
	object->mesh->centerMesh();
	object->mesh->translate(Vector3D(0,0,object->mesh->maxs.z));*/
//	m_level->player->mass->pos = Vector3D(250,0,22);

}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(40,30);
}

QSize GLWidget::sizeHint() const
{
	return QSize(500,300);
}

void GLWidget::restartTimer()
{
	m_timer->start();

	return;
}

void GLWidget::resizeGL(int w, int h)
{
	h = qMax(h,1);

	glViewport (0, 0, (GLsizei)(w), (GLsizei)(h));				// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	glPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 1200.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GLWidget::initializeGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return;
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	m_level->draw();

	return;
}

GLWidget::~GLWidget()
{

}

void GLWidget::process()
{
	GLfloat dt = m_timer->elapsed()*1e-3;
//	qErrnoWarning("%f\n", dt);
	m_level->run(dt);
	m_timer->start();

	update();

	return;
}

