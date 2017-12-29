#include "mass.h"

Mass::Mass() : m_mass(1.0f)
{

}

Mass::~Mass()
{

}

void Mass::setVelocity(float velocityX, float velocityY)
{
	m_velocity.x = velocityX;
	m_velocity.y = velocityY;
}

void Mass::update(float timeElapsed)
{
	m_position += m_velocity*timeElapsed;
}
