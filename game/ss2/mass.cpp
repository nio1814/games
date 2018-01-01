#include "mass.h"

#include <iostream>

Mass::Mass() : m_mass(1.0f)
{

}

Mass::~Mass()
{

}

void Mass::setVelocity(float velocityX, float velocityY)
{
	m_velocity = {velocityX, velocityY, 0};
}

void Mass::update(float timeElapsed)
{
	m_position += Vector3D(m_velocity*timeElapsed);
}

Vector3D Mass::position()
{
	return m_position;
}
