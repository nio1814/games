#include "ellipse.h"

#include <QtMath>
#include <qtgl.h>
#include <qopenglshaderprogram.h>
#include "mass.h"

Ellipse::Ellipse(float radius) : Object(),
	m_radius(radius)
{}

void Ellipse::draw(QOpenGLShaderProgram* program)
{
	int numVertices = 12;
	QVector<GLfloat> vertices;

	for(int n=0; n<numVertices; n++)
	{
		float angle = 2*n*M_PI/numVertices;
		vertices.append(m_radius*qCos(angle));
		vertices.append(m_radius*qSin(angle));
	}

	QMatrix4x4 matrix;
	matrix.setToIdentity();
	matrix.translate(m_mass->pos.toQVector3D());

	GLuint maPosition = program->attributeLocation("vPosition");

	program->setAttributeArray(maPosition, GL_FLOAT, vertices.data(), 2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
	program->disableAttributeArray(maPosition);

	return;
}
