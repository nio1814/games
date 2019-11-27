#ifndef PLANE_H
#define PLANE_H

#include "object.h"


class object_plane : public Object
{
public:
  float width, length;
  Vector3D normal, wvec, lvec;
  Vector2D angles;									//(phi, theta)
//	bool touching;

//	object_plane();
    object_plane(float mass=1, float wid=1, float len=1, float phi=0, float theta=0, Vector3D mAxis=Z);
  object_plane(float width, float length, Vector3D position, Vector3D normal=Z, Vector3D basisAxis=Z);
  object_plane(float width, float length, Vector3D position, Vector3D normal, matrix2D3 basis);

    object_plane& operator = (const object_plane& plane);

  virtual void draw();
  //virtual bool doCollisions(const object_holder *allObjs);
  //make length and width vectors by rotating from major axis
  void makeBase(const Vector3D* mAxis);
  void flipBase();
  void orient(const Vector3D& norm);
    void rotate(const Vector3D& axis, GLfloat degrees);
  void rotateAroundNormal(GLfloat degrees);
  bool inPlane(const Vector3D *v);
  bool atSurface(const Vector3D *v);
  bool isAbove(const Vector3D *v) const;
};

std::shared_ptr<object_plane> copyPlane(std::shared_ptr<const object_plane> plane);

#endif // PLANE_H
