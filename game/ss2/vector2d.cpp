#include "vector2d.h"

#include <valarray>

Vector2D::Vector2D()
{

}

Vector2D::Vector2D(std::vector<float> vector) :
	VectorND(vector)
{
}

Vector2D::Vector2D(const VectorND &vector)
{
	int minSize = std::min(vector.size(), 2);
	m_array.clear();
	for (int n=0; n<minSize; n++)
		m_array.push_back(vector.vector()[n]);
}
