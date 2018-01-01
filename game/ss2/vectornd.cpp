/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/
#include "vectornd.h"

VectorND::VectorND()
{}

VectorND::VectorND(std::vector<float> vector)
{
//	m_array = std::valarray<float>(vector.data(), vector.size());
	m_array = vector;
}

VectorND::VectorND(const VectorND &vector)
{
	m_array = vector.vector();
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
//	m_array *= value;
	std::vector<float> newVector = m_array;

	for (float& r : newVector)
		r *= value;

	return VectorND(newVector);
}

/*std::valarray<float> VectorND::array() const
{
	return m_array;
}*/

std::vector<float> VectorND::vector() const
{
//	return std::vector<float>(std::begin(m_array), std::end(m_array));
	return m_array;
}

VectorND& VectorND::operator+= (VectorND v)			// operator+= is used to add another Vector3D to this Vector3D.
{
//	m_array += v.array();
	int minSize = std::min(size(), v.size());
	for (int n=0; n<minSize; n++)
		m_array[n] += v[n];

	return *this;
}

VectorND &VectorND::operator-=(VectorND v)
{
//	m_array -= v.array();
	int minSize = std::min(size(), v.size());
	for (int n=0; n<minSize; n++)
		m_array[n] -= v[n];

	return *this;
}

float VectorND::operator[](int index)
{
	return m_array[index];
}
