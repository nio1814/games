/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/
#include "vectornd.h"

VectorND::VectorND()
{}

VectorND::VectorND(std::vector<float> vector)
{
	m_array = std::valarray<float>(vector.data(), vector.size());
}

float VectorND::x()
{
	return m_array[0];
}

float VectorND::y()
{
	return m_array[1];
}

int VectorND::size() const
{
	return m_array.size();
}

VectorND &VectorND::operator=(VectorND v)
{
	m_array = v.m_array;

	return *this;
}

VectorND VectorND::operator* (float value)			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
{
	m_array *= value;

	return *this;
}

std::valarray<float> VectorND::array() const
{
	return m_array;
}

std::vector<float> VectorND::vector()
{
	return std::vector<float>(std::begin(m_array), std::end(m_array));
}

VectorND& VectorND::operator+= (VectorND v)			// operator+= is used to add another Vector3D to this Vector3D.
{
	m_array += v.array();

	return *this;
}

VectorND &VectorND::operator-=(VectorND v)
{
	m_array -= v.array();

	return *this;
}

float VectorND::operator[](int index)
{
	return m_array[index];
}
