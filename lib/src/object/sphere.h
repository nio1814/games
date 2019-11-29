#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"


class object_sphere : public Object
{
public:
  float radius;
//	GLUquadricObj	*quad;						// Quadratic For Drawing A Sphere

  object_sphere(float mass=1, float radius=1, const Vector3D position=Vector3D());
  ~object_sphere();

  virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
  virtual void draw();
  virtual bool detectCollision(const std::shared_ptr<Object> object);
  virtual bool detectCollision(const std::shared_ptr<const object_sphere> sphere);
//  virtual bool detectCollision(const object_plane* plane);
  //virtual bool doCollisions(const object_holder *allObjs);
  virtual void collide(ConstPointer object);
  virtual void collide(std::shared_ptr<const object_sphere> sphere);
};


#endif // SPHERE_H
