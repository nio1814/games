#include "squirclerenderer.h"

#include <qopenglshaderprogram.h>

SquircleRenderer::SquircleRenderer(QObject *parent) : QObject(parent),
	m_t(0), m_program(NULL)
{

}

SquircleRenderer::~SquircleRenderer()
{
	delete m_program;
}

void SquircleRenderer::setT(qreal t)
{
	m_t = t;

	return;
}

void SquircleRenderer::setViewportSize(const QSize &size)
{
	m_viewportSize = size;

	return;
}

void SquircleRenderer::paint()
{
	if(!m_program)
	{
		initializeOpenGLFunctions();

		m_program = new QOpenGLShaderProgram;
		m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
										   "attribute highp vec4 vertices;"
											"varying highp vec2 coords;"
										  "void main() {"
										  "    gl_Position = vertices;"
										  "    coords = vertices.xy;"
										  "}");
		m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
										   "uniform lowp float t;"
										  "varying highp vec2 coords;"
										  "void main() {"
										  "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
										  "    i = smoothstep(t - 0.8, t + 0.8, i);"
										  "    i = floor(i * 20.) / 20.;"
										  "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
										  "}");
		m_program->bindAttributeLocation("vertices", 0);
		m_program->link();
	}

	m_program->bind();
	m_program->enableAttributeArray(0);

	GLfloat values[] = {-1,-1, 1,-1, -1,1, 1,1};
	m_program->setAttributeArray(0, GL_FLOAT, values, 2);
	m_program->setUniformValue("t", (GLfloat)m_t);

	glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

//	glDisable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_program->disableAttributeArray(0);
	m_program->release();


	return;
}
