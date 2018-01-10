#include "vector3d.h"

Vector3D::Vector3D()
{
	m_array = {0,0,0};
}

Vector3D::Vector3D(std::vector<float> vector) :
	VectorND::VectorND(vector)
{

}

Vector3D::Vector3D(const VectorND &vector) : Vector3D()
{
	int minSize = std::min(vector.size(), 3);
//	m_array = vector.array()[std::slice(0,minSize,1)];
	m_array.clear();
//	std::copy(vector.vector().begin(), vector.vector().begin()+minSize, m_array.begin());
	for (int n=0; n<minSize; n++)
		m_array.push_back(vector.vector()[n]);
}

Vector3D::Vector3D(float x, float y, float z)
{
	m_array = {x,y,z};
}

void Vector3D::setZ(float z)
{
	m_array[2] = z;
}
