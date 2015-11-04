#ifndef VECTOR3D
#define VECTOR3D

/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/

#include <math.h>

class QVector3D;

class Vector2D
{
public:
	float x;									// the x value of this Vector3D
	float y;									// the y value of this Vector3D

	Vector2D();									// Constructor to set x = y = z = 0

	Vector2D(float x, float y);			// Constructor that initializes this Vector2D to the intended values of x, y and z
	Vector2D(int angx, int angy, int angz, float length);	//constructor from angles
	Vector2D& operator= (Vector2D v);			// operator= sets values of v to this Vector2D. example: v1 = v2 means that values of v2 are set onto v1
	Vector2D operator+ (Vector2D v);				// operator+ is used to add two Vector2D's. operator+ returns a new Vector2D
	Vector2D operator- (Vector2D v);				// operator- is used to take difference of two Vector2D's. operator- returns a new Vector2D
	Vector2D operator* (float value);			// operator* is used to scale a Vector2D by a value. This value multiplies the Vector2D's x, y and z.
	Vector2D operator/ (float value);			// operator/ is used to scale a Vector2D by a value. This value divides the Vector2D's x, y and z.
	
	Vector2D& operator+= (Vector2D v);			// operator+= is used to add another Vector2D to this Vector2D.
	Vector2D& operator-= (Vector2D v);			// operator-= is used to subtract another Vector2D from this Vector2D.
	Vector2D& operator*= (float value);			// operator*= is used to scale this Vector2D by a value.
	Vector2D& operator/= (float value);			// operator/= is used to scale this Vector2D by a value.
	bool operator== (Vector2D v);				// operator== is used to see if another Vector2D is the same as this Vector2D.

	Vector2D operator- ();						// operator- is used to set this Vector2D's x, y, and z to the negative of them.
	float length();								// length() returns the length of this Vector2D		   		
	float dot(Vector2D *v);						//calculate dot product
	float dot(Vector2D v);						//calculate dot product
	Vector2D mult(Vector2D v);					//calculate componentwise product
	float angle(Vector2D *v);					//calculate the angle between another vector
	Vector2D proj(Vector2D *v);
	Vector2D proj(Vector2D *v1, Vector2D *v2);	//project onto basis of vectors v1 and v2
	//Vector2D rotate3D(Vector2D *v, float angle);
	void unitize();								// unitize() normalizes this Vector2D that its direction remains the same but its length is 1.
	Vector2D unit();								// unit() returns a new Vector2D. The returned value is a unitized version of this Vector2D.

};

		
class Vector3D		//---> An object to represent a 3D vector or a 3D point in space
{
public:
	float x;									// the x value of this Vector3D
	float y;									// the y value of this Vector3D
	float z;									// the z value of this Vector3D

	Vector3D();									// Constructor to set x = y = z = 0

	Vector3D(float x, float y, float z);			// Constructor that initializes this Vector3D to the intended values of x, y and z
	Vector3D(int angx, int angy, int angz, float length);	//constructor from angles
	Vector3D& operator= (const Vector3D &v);			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	//Vector3D& operator= (const Vector3D v);			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	Vector3D& operator= (Vector2D v);			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	Vector3D operator+ (Vector3D v) const;				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
	Vector3D operator- (const Vector3D v) const;				// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
	Vector3D operator* (float value) const;			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
	Vector3D operator/ (float value);			// operator/ is used to scale a Vector3D by a value. This value divides the Vector3D's x, y and z.
	
	Vector3D& operator+= (Vector3D v);			// operator+= is used to add another Vector3D to this Vector3D.
	Vector3D& operator-= (Vector3D v);			// operator-= is used to subtract another Vector3D from this Vector3D.
	Vector3D& operator*= (float value);			// operator*= is used to scale this Vector3D by a value.
	Vector3D& operator/= (float value);			// operator/= is used to scale this Vector3D by a value.
	bool operator== (const Vector3D v) const;				// operator== is used to see if another Vector3D is the same as this Vector3D.

	Vector3D operator- () const;						// operator- is used to set this Vector3D's x, y, and z to the negative of them.
	float length() const;								// length() returns the length of this Vector3D		   		
	float dot(const Vector3D *v) const;						//calculate dot product
	float dot(Vector3D v) const;						//calculate dot product
	float angle(const Vector3D *v);					//calculate the angle between another vector(degrees)
	Vector3D proj(const Vector3D *v) const;
	Vector3D proj(const Vector3D &v1, const Vector3D &v2) const;
	Vector3D rotate3D(const Vector3D &v, float angle) const;//rotate vector about v with given angle in degrees
	Vector3D rotatePhiTheta(const Vector3D *majAxis, float phi, float theta) const;//rotate vector about an axis, using phi and theta angles
	Vector3D decompose(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3)const ;	//find coordinates of vector with basis of input vectors
	Vector3D pointOnLine(float frac) const;					//find the point on the line v a fraction frac of the length along line
	Vector3D cart2sph(Vector3D *v);				//convert vector from cartesian to spherical coordinates(r,phi,theta)
	Vector3D cart2angxyz();						//convert vector in cartesian to x,y,z angles
	Vector3D angxyz2cart();						//convert vector of x,y,z anglesin to cartesian  
	void unitize();								// unitize() normalizes this Vector3D that its direction remains the same but its length is 1.
	Vector3D unit() const;								// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
	float* toArray() const;						//converts vector to a array of floats
	QVector3D toQVector3D() const;
};	

class Vector4D		//---> An object to represent a 3D vector or a 3D point in space
{
public:
	float x;									// the x value of this Vector3D
	float y;									// the y value of this Vector3D
	float z;									// the z value of this Vector3D
	float w;
	
	Vector4D();									// Constructor to set x = y = z = 0
	Vector4D(float x, float y, float z, float w);			// Constructor that initializes this Vector3D to the intended values of x, y and z
};

class VectorND
{
public:
	float* v;
	float n;

	VectorND();
	VectorND(int N);
	~VectorND();
};

class matrix2D3
{
public:
	Vector3D A[3];								//matrix rows

	matrix2D3(){}
	matrix2D3(const Vector3D &r1, const  Vector3D &r2, const  Vector3D &r3);
	matrix2D3& operator= (matrix2D3 m);
	
	Vector3D transform(const Vector3D* vec);
};


//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
Vector3D Cross(const Vector3D& vVector1, const Vector3D& vVector2);

// This returns the dot product between 2 vectors
float Dot(const Vector3D* vVector1, const Vector3D* vVector2);

//	This returns the normal of a polygon (The direction the polygon is facing)
Vector3D Normal(Vector3D vTriangle[]);

Vector3D pointOnLine(const Vector3D *v1, const Vector3D *v2, float frac);	//find the point on the line from v1 to v2 a fraction frac of the length along line

Vector3D char2vec3(char in);

extern const Vector3D X,Y,Z;

#endif
