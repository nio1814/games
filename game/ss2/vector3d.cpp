#include "vector3d.h"

Vector3D::Vector3D()
{
	m_array = {0,0,0};
}

Vector3D::Vector3D(std::vector<float> vector) :
	VectorND::VectorND(vector)
{

}

Vector3D::Vector3D(const VectorND &vector)
{
	int minSize = std::min(vector.size(), 3);
	m_array = vector.array()[std::slice(0,minSize,1)];
}

Vector3D::Vector3D(float x, float y, float z)
{
	m_array = {x,y,z};
}
