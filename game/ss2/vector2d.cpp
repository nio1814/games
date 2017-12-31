#include "vector2d.h"

#include <valarray>

Vector2D::Vector2D()
{

}

Vector2D::Vector2D(std::vector<float> vector) :
	VectorND(vector)
{
}
