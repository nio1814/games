#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "vectornd.h"

class Vector2D : public VectorND
{
public:
	Vector2D();									// Constructor to set x = y = z = 0
	Vector2D(std::vector<float> vector);
	Vector2D(const VectorND& vector);
};

#endif // VECTOR2D_H
