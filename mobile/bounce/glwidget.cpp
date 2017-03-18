#include "glwidget.h"

#include <qopenglfunctions.h>
#include <qopenglshaderprogram.h>

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
		: QOpenGLWidget(parent), m_program(NULL)
#else
       : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
	initializeObjects();
}

GLWidget::~GLWidget()
{
}

void GLWidget::resizeGL(GLsizei w, GLsizei h)		// Resize And Initialize The GL Window
{
    h = qMax(h,1);

#if QGLfo
	m_projection.setToIdentity();
	m_projection.perspective(45, GLfloat(w)/h, .01, 100);
#else
    glViewport(0,0,w,h);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
//    glPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
#endif
}


void GLWidget::initializeGL()										// All Setup For OpenGL Goes Here
{
	initializeOpenGLFunctions();

	QString vertexShaderCode = "uniform mat4 uMVPMatrix;	\n";
	vertexShaderCode += "attribute vec4 vPosition;	\n";
	vertexShaderCode += "void main() {	\n";
	vertexShaderCode +=	"	gl_Position = uMVPMatrix*vPosition;	\n";
	vertexShaderCode +=	"}	\n";

	QString fragmentShaderCode = "precision medium float;	\n";
	fragmentShaderCode += "void main() {	\n";
	fragmentShaderCode += "	gl_FragColor = vec4(0.6367, 0.7695, 0,22265, 1.0);	\n";
	fragmentShaderCode += "}	\n";

	m_program = new QOpenGLShaderProgram();
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode);
	m_program->link();

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.5f, 1.0f, 1.0f);				// Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear The Stencil Buffer To 0
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping

//	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);			// Set The Ambient Lighting For Light0
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);			// Set The Diffuse Lighting For Light0
//	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Set The Position For Light0

	glEnable(GL_LIGHT0);								// Enable Light 0
	glEnable(GL_LIGHTING);								// Enable Lighting

    return;										// Initialization Went OK
}

void GLWidget::initializeObjects()
{
	m_ellipses.addObject(new class Ellipse(1));
	m_ellipses.addObject(new class Ellipse(1.4));

	return;
}


void GLWidget::paintGL()									// Draw Everything
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	m_ellipses.draw(m_program);

    return;
}


void GLWidget::process()
{
//    delta = qobject_cast<QTimer*>(sender())->interval();

	update();

	return;
}
