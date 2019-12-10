#include "quaternion.h"
#include "constants.h"

#include <cmath>

Quaternion::Quaternion(const float w, const float x, const float y, const float z) :
  w(w),
  x(x),
  y(y),
  z(z)
{}

Quaternion::Quaternion(const matrix2D3 matrix)
{
  const float trace = matrix.at(0, 0) + matrix.at(1, 1) + matrix.at(2, 2);

  if(trace > 0)
  {
    const float S = sqrt(trace+1.0) * 2;
    this->w = 0.25 * S;
    this->x = (matrix.at(2, 1) - matrix.at(1, 2)) / S;
    this->y = (matrix.at(0, 2) - matrix.at(2, 0)) / S;
    this->z = (matrix.at(1, 0) - matrix.at(0, 1)) / S;
  }
  else if ((matrix.at(0, 0) > matrix.at(1, 1)) && (matrix.at(0, 0) > matrix.at(2, 2)))
  {
    const float S = sqrt(1.0 + matrix.at(0, 0) - matrix.at(1, 1) - matrix.at(2, 2)) * 2;
    this->w = (matrix.at(2, 1) - matrix.at(1, 2)) / S;
    this->x = 0.25 * S;
    this->y = (matrix.at(0, 1) + matrix.at(1, 0)) / S;
    this->z = (matrix.at(0, 2) + matrix.at(2, 0)) / S;
  }
  else if (matrix.at(1, 1) > matrix.at(2, 2))
  {
    const float S = sqrt(1.0 + matrix.at(1, 1) - matrix.at(0, 0) - matrix.at(2, 2)) * 2;
    this->w = (matrix.at(0, 2) - matrix.at(2, 0)) / S;
    this->x = (matrix.at(0, 1) + matrix.at(1, 0)) / S;
    this->y = 0.25 * S;
    this->z = (matrix.at(1, 2) + matrix.at(2, 1)) / S;
  }
  else
  {
    const float S = std::sqrt(1.0 + matrix.at(2, 2) - matrix.at(0, 0) - matrix.at(1, 1)) * 2; // S=4*this->z
    this->w = (matrix.at(1, 0) - matrix.at(0, 1)) / S;
    this->x = (matrix.at(0, 2) + matrix.at(2, 0)) / S;
    this->y = (matrix.at(1, 2) + matrix.at(2, 1)) / S;
    this->z = 0.25 * S;
    }
}

Quaternion::Quaternion(const Vector3D axis, const float degrees)
{
  const float radians = DEGREES_TO_RADIANS * degrees;
  const float s = std::sin(radians/2);
  this->x = axis.x * s;
  this->y = axis.y * s;
  this->z = axis.z * s;
  this->w = std::cos(radians/2);
}

Quaternion Quaternion::inverse()
{
  Quaternion inverted(*this);
  inverted.x *= -1;
  inverted.y *= -1;
  inverted.z *= -1;

  return inverted;
}

Vector3D Quaternion::rotate(const Vector3D &vector) const
{
  return this->rotationMatrix().transform(vector);
}

matrix2D3 Quaternion::rotationMatrix() const
{
  const float xx = x*x;
  const float yy = y*y;
  const float zz = z*z;
  const float yz = y*z;
  const float xy = x*y;
  const float xz = x*z;
  const float zw = z*w;
  const float yw = y*w;
  const float xw = x*w;

  return matrix2D3({1 - 2*yy - 2*zz, 2*xy - 2*zw, 2*xz + 2*yw,
                         2*xy + 2*zw, 1 - 2*xx - 2*zz, 2*yz - 2*xw,
                         2*xz - 2*yw, 2*yz + 2*xw, 1 - 2*xx - 2*yy});
}
