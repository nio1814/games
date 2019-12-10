#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3d.h"

class Quaternion
{
public:
  Quaternion(){};
  Quaternion(const float w, const float x, const float y, const float z);
  Quaternion(const matrix2D3 matrix);
  Quaternion(const Vector3D axis, const float degrees);

  Quaternion inverse();
  Vector3D rotate(const Vector3D& vector) const;

  float w = 1;
  float x = 0;
  float y = 0;
  float z = 0;
private:
  matrix2D3 rotationMatrix() const;
};

#endif // QUATERNION_H
