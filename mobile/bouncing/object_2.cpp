#include "object_2.h"

#include "mass.h"

Object::Object() : m_draw(true)
{
	m_mass = new Mass;
}

bool Object::doDraw()
{
	return m_draw;
}
