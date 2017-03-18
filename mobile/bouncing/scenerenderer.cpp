#include "scenerenderer.h"

#include "scene.h"
#include <qopenglshaderprogram.h>

SceneRenderer::SceneRenderer(QObject *parent) : QObject(parent)
{
	m_lastTime = -1;
	m_backgroundColor = QColor(qrand()/255, qrand()/255, qrand()/255);


	QString vertexShaderCode = "uniform mat4 uMVPMatrix;	\n";
	vertexShaderCode += "attribute vec4 vPosition;	\n";
	vertexShaderCode += "void main() {	\n";
	vertexShaderCode +=	"	gl_Position = uMVPMatrix*vPosition;	\n";
	vertexShaderCode +=	"}	\n";

	QString fragmentShaderCode = "precision medium float;	\n";
	fragmentShaderCode += "void main() {	\n";
	fragmentShaderCode += "	gl_FragColor = vec4(0.6367, 0.7695, 0,22265, 1.0);	\n";
	fragmentShaderCode += "}	\n";

	initializeOpenGLFunctions();

	m_program = new QOpenGLShaderProgram();
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode);
	m_program->link();
}

SceneRenderer::~SceneRenderer()
{
	delete m_program;
}

void SceneRenderer::setViewportSize(const QSize &size)
{
	m_viewportSize = size;

	return;
}

void SceneRenderer::paint()
{
	float dt = .1;

	m_program->bind();

	glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), m_backgroundColor.alphaF());
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

	m_scene->render(m_program);

	m_program->release();

	return;
}
