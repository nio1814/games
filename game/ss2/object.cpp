#include "object.h"

#include "qtgl.h"

#include <vector>

Object::Object(float width, float height, float positionX, float positionY) :
	m_size(Vector2D({width, height})),
	m_speed(1.0f)
{
}

Object::~Object()
{

}

Vector2D Object::minPosition()
{
	std::vector<float> minPos(2);
	for (int n=0; n<2; n++)
		minPos[n] = m_position[n] - m_size[n]/2.0f;

	return minPos;
}

Vector2D Object::maxPosition()
{
	std::vector<float> minPos(2);
	for (int n=0; n<2; n++)
		minPos[n] = m_position[n] + m_size[n]/2.0f;

	return minPos;
}

float Object::directionFloat()
{
	return m_facingRight ? 1.0f : -1.0f;
}

void Object::draw()
{
	glEnable(GL_TEXTURE_2D);

	float positionX = m_position.x();
	float positionY = m_position.y();
	float sizeY = m_size.y();

	glPushMatrix();
	glTranslatef(positionX, positionY+.5f*sizeY, 0.0f);
	glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-positionX, -(positionY + .5f*sizeY), 0.0f);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	Vector2D minPos = minPosition();
	Vector2D maxPos = maxPosition();
	float isRightOne = m_facingRight ? 1.0f : 0.0f;
	glTexCoord2f(1.0f-isRightOne, 1.0f);
	glVertex3f(minPos.x(), maxPos.y(), 0.0f);
	glTexCoord2f(isRightOne, 1.0f);
	glVertex3f(maxPos.x(), maxPos.y(), 0.0f);
	glTexCoord2f(isRightOne, 0.0f);
	glVertex3f(maxPos.x(), minPos.y(), 0.0f);
	glTexCoord2f(1.0f-isRightOne, 0.0f);
	glVertex3f(minPos.x(), minPos.y(), 0.0f);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
}
