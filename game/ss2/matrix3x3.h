#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <valarray>
#include "vector3d.h"

class Matrix3x3
{
public:
	Matrix3x3(){};
	std::valarray<float> m_array;								//matrix rows

	Matrix3x3(const Vector3D &r1, const  Vector3D &r2, const  Vector3D &r3);
	Matrix3x3& operator= (Matrix3x3 m);

	Vector3D transform(const Vector3D* vec);
	Vector3D cartesianToSpherical(Vector3D cartesian);
};

#endif // MATRIX3X3_H
