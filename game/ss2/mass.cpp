#include "mass.h"

#include <iostream>

Mass::Mass(Vector3D position) :
	m_position(position),
	m_mass(1.0f)
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
	if(m_hasGravity)
		m_velocity += Vector3D(0,m_gravity,0);
	m_position += Vector3D(m_velocity*timeElapsed);
}

Vector3D Mass::position() const
{
	return m_position;
}

void Mass::setHasGravity(bool status)
{
	m_hasGravity = status;
}

Vector3D Mass::velocity()
{
	return m_velocity;
}
