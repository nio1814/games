#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "vectornd.h"

class Vector3D : public VectorND	//---> An object to represent a 3D vector or a 3D point in space
{
public:
	Vector3D();
	Vector3D(std::vector<float> vector);
	Vector3D(const VectorND& vector);
	Vector3D(float x, float y, float z);

	void setZ(float z);
};

#endif // VECTOR3D_H
