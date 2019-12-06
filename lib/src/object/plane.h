#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "quaternion.h"

class Plane : public Object
{
public:
  Quaternion quaternion;
  float width, length;
//	bool touching;

//	object_plane();
  Plane(float wid=1, float len=1, float phi=0, float theta=0, Vector3D axis=Z);
  Plane(float width, float length, Vector3D position, const Vector3D& up, const Vector3D& toRight);

  Plane& operator = (const Plane& plane);

  Vector3D normal() const;
  Vector3D right();
  Vector3D forward();
  void flipBase();
  void rotate(const Vector3D& axis, GLfloat degrees);
  void rotateAroundNormal(GLfloat degrees);

  virtual bool detectCollision(std::shared_ptr<Object> object);
  virtual bool detectCollision(std::shared_ptr<Plane> plane);

  virtual void collide(ConstPointer object);
  void orient(const Vector3D& up, const Vector3D& toRight, Vector3D toFront=Vector3D());
private:
  virtual void draw();
  //virtual bool doCollisions(const object_holder *allObjs);

  //make length and width vectors by rotating from major axis
  void orient(const matrix2D3& basis);
  void orient(const Vector3D &majorAxis, const float theta, const float phi);
  Vector3D basisPosition(const Vector3D point) const;
  bool inPlane(const Vector3D &point);
  bool atSurface(const Vector3D &point);
  bool isAbove(const Vector3D &point) const;
};

std::shared_ptr<Plane> copyPlane(std::shared_ptr<const Plane> plane);

#endif // PLANE_H
