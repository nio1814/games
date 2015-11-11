#include "glwidget.h"

#include "level.h"
#include "meshobject.h"
#include "model3d.h"
#include "mass.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	level = new Level;
//	level.addLight(GL_LIGHT0, Vector3D(4,2,-2), Vector3D(0.6,0.5,0.5), Vector3D(0.8,1,0.8), Vector3D(1,1,1));	
	level->addPlayer(":data/mercedes3.ogl");
	level->player->mass->dir = Y;
	level->player->mesh->centerMesh();
	level->player->mass->pos = level->player->mesh->center;

}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(40,30);
}

QSize GLWidget::sizeHint() const
{
	return QSize(500,300);
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
	return;
}

GLWidget::~GLWidget()
{

}

