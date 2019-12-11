/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/
#include "vector3d.h"

#include <math.h>

#include "constants.h"

#include "qtgl.h"

const float EPSILON = (float)1e-1;

//Define global axes
extern const Vector3D X = Vector3D(1.0f,0.0f,0.0f);
extern const Vector3D Y = Vector3D(0.0f,1.0f,0.0f);
extern const Vector3D Z = Vector3D(0.0f,0.0f,1.0f);

Vector3D::Vector3D()									// Constructor to set x = y = z = 0
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(const std::vector<float>& vector)
{
  if(vector.size() == 3)
  {
    this->x = vector[0];
    this->y = vector[1];
    this->z = vector[2];
  }
  else
    throw std::runtime_error("Must initialize Vector3D with 3 elements");
}

Vector3D::Vector3D(int angx, int angy, int angz, float length)
{
  x = length*cos(angx*DEGREES_TO_RADIANS);
  y = length*cos(angy*DEGREES_TO_RADIANS);
  z = length*cos(angz*DEGREES_TO_RADIANS);
}

Vector3D::Vector3D(float x, float y, float z)			// Constructor that initializes this Vector3D to the intended values of x, y and z
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D& Vector3D::operator= (const Vector3D &v)				// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
{
	this->x = v.x;
  this->y = v.y;
  this->z = v.z;

	return *this;
}

/*Vector3D& Vector3D::operator= (const Vector3D v)				// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}*/

Vector3D& Vector3D::operator= (Vector2D v)				// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
{
	x = v.x;
	y = v.y;
	z = 0;
	return *this;
}

Vector3D Vector3D::operator+ (Vector3D v) const				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator- (const Vector3D v) const		// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator* (float value) const			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
{
	return Vector3D(x * value, y * value, z * value);
}

Vector3D Vector3D::operator/ (float value)			// operator/ is used to scale a Vector3D by a value. This value divides the Vector3D's x, y and z.
{
	return Vector3D(x / value, y / value, z / value);
}

Vector3D& Vector3D::operator+= (Vector3D v)			// operator+= is used to add another Vector3D to this Vector3D.
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3D& Vector3D::operator-= (Vector3D v)			// operator-= is used to subtract another Vector3D from this Vector3D.
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3D& Vector3D::operator*= (float value)			// operator*= is used to scale this Vector3D by a value.
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3D& Vector3D::operator/= (float value)			// operator/= is used to scale this Vector3D by a value.
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

bool Vector3D::operator== (const Vector3D v) const			// operator== is used to see if another Vector3D is the same as this Vector3D.
{
	bool equal = true;
	
	if(x != v.x)
		equal = false;
	else if(y != v.y)
		equal = false;
	else if(z != v.z)
		equal = false;
	
	return equal;
}

Vector3D Vector3D::operator- ()	const					// operator- is used to set this Vector3D's x, y, and z to the negative of them.
{
	return Vector3D(-x, -y, -z);
}

float Vector3D::length() const							// length() returns the length of this Vector3D
{
  return sqrtf(x*x + y*y + z*z);
}

bool Vector3D::isNull()
{
  return this->length() == 0;
}

float Vector3D::dot(const Vector3D& v)	const							// length() returns the length of this Vector3D
{
	return x*v.x + y*v.y + z*v.z;
}			   		

float Vector3D::angle(const Vector3D& v)								// length() returns the length of this Vector3D
{
	float magv1, magv2;
	float dotp;
	float ang = 0;

	magv1 = this->length();
	magv2 = v.length();
	dotp = this->dot(v);

	if(magv1*magv2 != 0)
	{
		ang = dotp/(magv1*magv2);
		ang = acos(ang)*RAD2DEG;
	}

	return ang;
}

Vector3D Vector3D::proj(const Vector3D& v) const
{
	Vector3D projV, onto;
	
	onto = v.unit();
	projV = onto*(this->dot(onto));

	return projV;
}

Vector3D Vector3D::proj(const Vector3D &v1, const Vector3D &v2) const
{
	Vector3D normal, inPlane;

	normal = Cross(v1, v2).unit();
	return (*this - this->proj(normal));
}

Vector3D Vector3D::rotate3D(const Vector3D &vin, float angle) const
{
	Vector3D v, vout;
	matrix2D3 T;
	GLfloat angrad, cosang, sinang, t;
	//bool arbitrary = false;

  angrad = angle*DEGREES_TO_RADIANS;
	cosang = cos(angrad);
	sinang = sin(angrad);
	v = vin.unit();
	if(v.length() < EPS)
    T = matrix2D3(X, Y, Z, true);
	else if(v == X)
    T = matrix2D3(X, Vector3D(0,cosang,-sinang), Vector3D(0,sinang,cosang), true);
	else if(v == Y)
    T = matrix2D3(Vector3D(cosang,0,sinang), Y, Vector3D(-sinang,0,cosang), true);
	else if(v == Z)
    T = matrix2D3(Vector3D(cosang,-sinang,0), Vector3D(sinang,cosang,0), Z, true);
	else
	{
	//	arbitrary = true;
		t = 1 - cosang;
    T = matrix2D3(Vector3D(t*v.x*v.x+cosang, t*v.x*v.y-sinang*v.z, t*v.x*v.z+sinang*v.y),
      Vector3D(t*v.x*v.y+sinang*v.z, t*v.y*v.y+cosang, t*v.y*v.z-sinang*v.x),
      Vector3D(t*v.x*v.z-sinang*v.y, t*v.y*v.z+sinang*v.x, t*v.z*v.z+cosang), true);
		//T = matrix2D3(&Vector3D(cosang,0,-sinang), &Vector3D(0,1,0), &Vector3D(sinang,0,cosang));
	}

  vout = T.transform(*this);

	return vout;
}

Vector3D Vector3D::rotatePhiTheta(const Vector3D *majAxis, float phi, float theta) const
{
	Vector3D vout;
	
	if(*majAxis == Y)
	{
		vout = this->rotate3D(X, theta);
		vout = vout.rotate3D(Y, phi);
	}
	//else
	//		MessageBox(NULL,"Invalid Major Axis.","vector3d.cpp: rotatePhiTheta",MB_OK | MB_ICONINFORMATION);
	
	return vout;
}


Vector3D Vector3D::decompose(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3) const
{
	Vector3D temp, coords;
	Vector3D xBase,yBase,zBase;
	temp = *this;

	xBase = v1.unit();
	yBase = v2.unit();
	zBase = v3.unit();

	coords.x = temp.dot(xBase);
	temp -= temp.proj(xBase);
	coords.y = temp.dot(yBase);
	temp -= temp.proj(yBase);
	coords.z = temp.dot(zBase);

	return coords;
}

Vector3D Vector3D::pointOnLine(float frac) const
{
	return (*this + *this*frac);
}

Vector3D Vector3D::cart2sph(Vector3D *v)
{
	float r, phi, theta;

	r = v->length();
	
	if(y >= 0)
		phi = v->angle(X);		//quadrants I,II
	else
		phi = 360 - v->angle(X);	//quadrants III, IV

	theta = v->angle(Z);

	return Vector3D(r, phi, theta);
}

Vector3D Vector3D::cart2angxyz()
{
	//order: z ang, y ang, x angle
	Vector3D vxy, vxz, vyz;				//vector in each plane
	Vector3D temp;
	Vector3D angles;

	//z ang
	vxy = proj(X,Y);
	if(vxy.y >= 0)
		angles.z = vxy.angle(X);		//quadrants I,II
	else
		angles.z = 360 - angle(X);	//quadrants III, IV
	vxz = rotate3D(Z, -angles.z);

	//y ang
	if(vxz.x >= 0)
		angles.y = vxz.angle(Z);		//quadrants I,II
	else
		angles.y = 360 - vxz.angle(Z);	//quadrants III, IV
	vyz = vxz.rotate3D(Y, -angles.y);

	//x ang
	if(vyz.y <= 0)
		angles.x = vyz.angle(Z);		//quadrants I,II
	else
		angles.x = 360 - vyz.angle(Z);	//quadrants III, IV

	return angles;
}

Vector3D Vector3D::angxyz2cart()
{
	Vector3D v = Z;

	v = v.rotate3D(X, x);
	v = v.rotate3D(Y, y);
	v = v.rotate3D(Z, z);

	return v;
}


void Vector3D::unitize()								// unitize() normalizes this Vector3D that its direction remains the same but its length is 1.
{
	float length = this->length();

	if (length == 0)
		return;

	x /= length;
	y /= length;
	z /= length;
}

Vector3D Vector3D::unit() const							// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
{
	float length = this->length();

	if (length == 0)
		return *this;
	
	return Vector3D(x / length, y / length, z / length);
}

//float* Vector3D::toArray() const
//{
//	float out[3];

//	out[0] = x;
//	out[1] = y;
//	out[2] = z;

//	return out;
//}

QVector3D Vector3D::toQVector3D() const
{
	return QVector3D(x,y,z);
}

//VECTOR2D
Vector2D::Vector2D()									// Constructor to set x = y = z = 0
{
	x = 0;
	y = 0;
}

//Vector2D::Vector2D(int angx, int angy, int angz, float length)
//{
//	x = length*cos(angx*DEG2RAD);
//	y = length*cos(angy*DEG2RAD);
//}

Vector2D::Vector2D(float x, float y)			// Constructor that initializes this Vector2D to the intended values of x, y and z
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::operator= (Vector2D v)				// operator= sets values of v to this Vector2D. example: v1 = v2 means that values of v2 are set onto v1
{
	x = v.x;
	y = v.y;
	
	return *this;
}

Vector2D Vector2D::operator+ (Vector2D v)				// operator+ is used to add two Vector2D's. operator+ returns a new Vector2D
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator- (Vector2D v)				// operator- is used to take difference of two Vector2D's. operator- returns a new Vector2D
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator* (float value)			// operator* is used to scale a Vector2D by a value. This value multiplies the Vector2D's x, y and z.
{
	return Vector2D(x * value, y * value);
}

Vector2D Vector2D::operator/ (float value)			// operator/ is used to scale a Vector2D by a value. This value divides the Vector2D's x, y and z.
{
	return Vector2D(x / value, y / value);
}

Vector2D& Vector2D::operator+= (Vector2D v)			// operator+= is used to add another Vector2D to this Vector2D.
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D& Vector2D::operator-= (Vector2D v)			// operator-= is used to subtract another Vector2D from this Vector2D.
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D& Vector2D::operator*= (float value)			// operator*= is used to scale this Vector2D by a value.
{
	x *= value;
	y *= value;
	return *this;
}

Vector2D& Vector2D::operator/= (float value)			// operator/= is used to scale this Vector2D by a value.
{
	x /= value;
	y /= value;
	return *this;
}

bool Vector2D::operator== (Vector2D v)				// operator== is used to see if another Vector2D is the same as this Vector2D.
{
	bool equal = true;
	
	if(x != v.x)
		equal = false;
	else if(y != v.y)
		equal = false;
	
	return equal;
}

Vector2D Vector2D::operator- ()						// operator- is used to set this Vector2D's x, y, and z to the negative of them.
{
	return Vector2D(-x, -y);
}

float Vector2D::length()								// length() returns the length of this Vector2D
{
	return sqrtf(x*x + y*y);
}

float Vector2D::dot(Vector2D *v)								// length() returns the length of this Vector2D
{
	return x*v->x + y*v->y;
}

float Vector2D::dot(Vector2D v)								// length() returns the length of this Vector2D
{
	return x*v.x + y*v.y;
}			   		

Vector2D Vector2D::mult(Vector2D v)					//calculate componentwise product
{
	return Vector2D(x*v.x, y*v.y);
}

float Vector2D::angle(Vector2D *v)								// length() returns the length of this Vector2D
{
	float magv1, magv2;
	float dotp;
	float ang = 0;

	magv1 = this->length();
	magv2 = v->length();
	dotp = this->dot(v);

	if(magv1*magv2 != 0)
	{
		ang = dotp/(magv1*magv2);
		ang = acos(ang)*RAD2DEG;
	}

	return ang;
}

Vector2D Vector2D::proj(Vector2D *v)
{
	Vector2D projV,onto;
	onto = v->unit();
	projV = onto*(this->dot(onto));

	return projV;
}

Vector2D Vector2D::proj(Vector2D *v1, Vector2D *v2)
{
	Vector2D line, toObj, alongv, point;

	line = *v2 - *v1;
	toObj = *this - *v1;
	alongv = toObj.proj(&line)*.2f;
	point = *v1 + alongv;

	return point;
}

/*Vector2D Vector2D::rotate3D(Vector2D *v, float angle)
{
	Vector2D rotvec, vecxz, vecxy, vout;
	matrix2D3 T;
	GLfloat angrad, cosang, sinang;
	GLfloat angxz, angxy;
	bool arbitrary = false;

	angrad = angle*DEG2RAD;
	cosang = cos(angrad);
	sinang = sin(angrad);
	if(*v == X)
		T = matrix2D3(&Vector2D(1,0,0), &Vector2D(0,cosang,0), &Vector2D(0,-sinang,cosang));
	else if(*v == Y)
		T = matrix2D3(&Vector2D(cosang,0,sinang), &Vector2D(0,1,0), &Vector2D(-sinang,0,cosang));
	else if(*v == Z)
		T = matrix2D3(&Vector2D(cosang,-sinang,0), &Vector2D(sinang,cosang,0), &Vector2D(0,0,1));
	else
	{
		arbitrary = true;
		T = matrix2D3(&Vector2D(cosang,0,-sinang), &Vector2D(0,1,0), &Vector2D(sinang,0,cosang));
		vecxz = *this;
		vecxz.y = 0;
		angxz = vecxz.angle(&X);
		vecxy = *this;
		vecxy.y = 0;
		angxy = vecxy.angle(&Y);
	}

	vout = T.transform(this);

	return vout;
}*/

void Vector2D::unitize()								// unitize() normalizes this Vector2D that its direction remains the same but its length is 1.
{
	float length = this->length();

	if (length == 0)
		return;

	x /= length;
	y /= length;
}

Vector2D Vector2D::unit()								// unit() returns a new Vector2D. The returned value is a unitized version of this Vector2D.
{
	float length = this->length();

	if (length == 0)
		return *this;
	
	return Vector2D(x / length, y / length);
}


//VECTOR4D
Vector4D::Vector4D()									// Constructor to set x = y = z = 0
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4D::Vector4D(float x, float y, float z, float w)			// Constructor that initializes this Vector3D to the intended values of x, y and z
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

VectorND::VectorND()
{
	v = NULL;

	return;
}

VectorND::VectorND(int N)
{
	v = new float(N);

	return;
}

VectorND::~VectorND()
{
	delete(v);

	return;
}

//MATRIX
matrix2D3::matrix2D3(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, const bool asRows)
{
  this->A[0] = v1;
  this->A[1] = v2;
  this->A[2] = v3;

  if(!asRows)
  {

  }
}

matrix2D3::matrix2D3(const std::vector<float> values)
{
  if(values.size() == 9)
  {
    A[0] = {values[0], values[1], values[2]};
    A[1] = {values[3], values[4], values[5]};
    A[2] = {values[6], values[7], values[8]};
  }
  else
    throw std::runtime_error("Must initialize matrix2D3 with 9 elements");
}

Vector3D matrix2D3::transform(const Vector3D& in) const
{
  Vector3D out;

  out.x = A[0].dot(in);
  out.y = A[1].dot(in);
  out.z = A[2].dot(in);

  return out;
}

Vector3D matrix2D3::cartesianToSpherical(Vector3D cartesian)
{
	float r = cartesian.length();
	float theta = A[2].angle(cartesian);
	Vector3D inPlane = cartesian - cartesian.proj(A[2]);
	float phi = A[0].angle(inPlane);
	if(inPlane.dot(A[1])<0)
		phi = -phi;

	return Vector3D(r, phi, theta);

}

matrix2D3& matrix2D3::operator= (matrix2D3 m)
{
	A[0] = m.A[0];
	A[1] = m.A[1];
	A[2] = m.A[2];
	
	return *this;
}

float matrix2D3::at(int rowIndex, int columnIndex) const
{
  switch (columnIndex) {
    case 0:
      return this->A[rowIndex].x;
      break;
    case 1:
      return this->A[rowIndex].y;
      break;
    case 2:
      return this->A[rowIndex].z;
      break;
    }
  throw std::runtime_error("Invalid column index");
}

void matrix2D3::transpose()
{
  Vector3D rows[3];
  for(int row=0; row<3; row++)
      rows[row] = Vector3D(this->at(0, row), this->at(1, row), this->at(2, row));
  matrix2D3(rows[0], rows[1], rows[2], true);
}

Vector3D Cross(const Vector3D& vVector1, const Vector3D& vVector2)
{
	Vector3D vNormal;									
	
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
	
	return vNormal;										
}


Vector3D Normal(Vector3D vTriangle[])					
{	
	Vector3D vVector1 = vTriangle[2] - vTriangle[0];
	Vector3D vVector2 = vTriangle[1] - vTriangle[0];
	Vector3D vNormal = Cross(vVector1, vVector2);
	//vNormal = Normalize(vNormal);
	vNormal.unitize();	
	
	return vNormal;										
}

Vector3D pointOnLine(const Vector3D *v1, const Vector3D *v2, float frac)
{
	Vector3D line, point;

	line = *v2 - *v1;
	point = *v1 + line*frac;

	return point;
}

Vector3D char2vec3(char in)
{
	Vector3D out;
	
	switch(in)
	{
		case 'X':
			out = Vector3D(1,0,0);
			break;
		case 'Y':
			out = Vector3D(0,1,0);
			break;
		case 'Z':
			out = Vector3D(0,0,1);
			break;
		default:
			break;
	}
	
	return out;
}
