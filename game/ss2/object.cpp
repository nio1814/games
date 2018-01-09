#include "object.h"

#include "qtgl.h"
#include "sprite.h"

#include <vector>
#include <iostream>

Object::Object(float width, float height, float positionX, float positionY) :
	Mass(Vector3D(positionX, positionY, 0)),
	m_sizeOriginal({width,height}),
	m_size(Vector2D({width, height})),
	m_speed(1.0f),
	m_action(Stand)
{
	resetTouches();
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

Vector2D Object::size()
{
	return m_size;
}

void Object::scaleToSpriteSize()
{
	if(m_sprite)
	{
		Vector2D scale = Vector2D(m_sprite->sizeScale());
//		float height = m_sprite->heightWidthScale()*m_size.x();
//		m_size.setY(height);
		m_size = m_sizeOriginal*scale;
	}
}

float Object::directionFloat()
{
	return m_facingRight ? 1.0f : -1.0f;
}

void Object::moveLeft()
{
	float velocityX = std::min(m_velocity.x(), -m_speed);
	m_velocity.setX(velocityX);
	m_facingRight = false;
	if(m_touching[BottomSide])
		setAction(Run);
}

void Object::moveRight()
{
	float velocityX = std::max(m_velocity.x(), m_speed);
	m_velocity.setX(velocityX);
	m_facingRight = true;
	if(m_touching[BottomSide])
		setAction(Run);

}

void Object::noLeftRightMove()
{
	m_velocity.setX(0);
	if(m_touching[BottomSide])
		setAction(Stand);
}

void Object::jump()
{
	if(m_sprite->hasAction(Jump) &&
			(m_action==Stand || m_action==Run) &&
			m_touching[BottomSide])
	{
		m_velocity.setY(m_jumpStrength);
		m_sprite->setAction(Jump);
		m_action = Jump;
	}
}

void Object::checkTouch(std::shared_ptr<Object> otherObject)
{
	Vector3D otherPosition = otherObject->position();
	float distance = m_position.distance(otherPosition);

	if(distance < diagonalLength() + otherObject->diagonalLength())
	{
		VectorND vectorBetween = otherPosition - m_position;
		float otherWidth = otherObject->size().x();
		bool withinWidth = std::abs(vectorBetween.x()) <= .5f*(otherWidth+m_size.x());
		float otherHeight = otherObject->size().y();
		float combinedHeight = otherHeight + m_size.y();
		bool above = m_position.y() > otherPosition.y();
		if(withinWidth && std::abs(vectorBetween.y()) <= .5*combinedHeight)
		{
			if(above)
			{
				m_touching[BottomSide] = true;
				m_position.setY(otherPosition.y() + .5*combinedHeight);
				if(m_action!=Run)
				{
					m_action = Stand;
					m_sprite->setAction(Stand);
				}
			}
			else
				m_touching[TopSide] = true;
		}
	}
	else
		resetTouches();
}

bool Object::touching(Object::Side side)
{
	return m_touching[side];
}

void Object::update(float timeElapsed)
{
	if(m_sprite)
		m_sprite->update(timeElapsed);
	scaleToSpriteSize();
	if(m_touching[BottomSide])
	{
		float velocityY = std::max(m_velocity.y(), 0.0f);
		m_velocity.setY(velocityY);
	}
	else if(m_hasGravity)
		m_velocity += Vector3D(0,m_gravity,0)*timeElapsed;

	m_position += Vector3D(m_velocity*timeElapsed);

}

void Object::reset()
{
	resetTouches();
}

void Object::setSprite(const Sprite& sprite)
{
	m_sprite = std::make_unique<Sprite>(sprite);
//	m_sprite->setActionPointer(m_action);
	m_sizeOriginal.setY(m_sprite->heightWidthScale()*m_sizeOriginal.x());

	switch(m_sprite->character())
	{
		case Mario1Little:
			m_speed = 3;
			break;
		default:
			break;
	}
}

float Object::diagonalLength() const
{
	return m_size.length();
}

void Object::resetTouches()
{
	for (Side side : {LeftSide,RightSide,BottomSide,TopSide})
		m_touching[side] = false;
}

void Object::setAction(Action action)
{
	m_action = action;
	m_sprite->setAction(action);
}

void Object::draw()
{
	if (m_sprite && m_sprite->textureIndex()>=0)
	{
		glBindTexture(GL_TEXTURE_2D, m_sprite->textureIndex());
//		std::cerr << glGetError() << std::endl;
		glEnable(GL_TEXTURE_2D);
	}

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
//	glColor3f(1,0,0);
	glVertex3f(minPos.x(), maxPos.y(), 0.0f);
	glTexCoord2f(isRightOne, 1.0f);
//	glColor3f(0,1,0);
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
