#ifndef VECTOR3D
#define VECTOR3D

/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/

#include <math.h>
#include <valarray>

class VectorND
{
public:
	VectorND();
//	VectorND(int N);
	VectorND(std::vector<float> vector);
	VectorND(const VectorND& vector);

	float x();
	float y();

	int size() const;

	VectorND unit() const;								// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
	float dot(const VectorND &v) const;						//calculate dot product
	VectorND project(const VectorND &v) const;

	VectorND& operator= (VectorND v);			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
//	VectorND& operator+ (VectorND v) const;				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
//	VectorND& operator- (const VectorND v) const;				// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
	VectorND operator* (float value);			// operator* is used to scale a Vector2D by a value. This value multiplies the Vector2D's x, y and z.
//	VectorND& operator/ (float value);			// operator/ is used to scale a Vector2D by a value. This value divides the Vector2D's x, y and z.
	VectorND& operator+= (VectorND v);			// operator+= is used to add another Vector3D to this Vector3D.
	VectorND& operator-= (VectorND v);			// operator-= is used to subtract another Vector3D from this Vector3D.
	float operator[] (int index);

//	std::valarray<float> array() const;
	std::vector<float> vector() const;

protected:
//	std::valarray<float> m_array;
	std::vector<float> m_array;
};


#endif
