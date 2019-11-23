#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"


class object_sphere : public Object
{
public:
  float radius;
//	GLUquadricObj	*quad;						// Quadratic For Drawing A Sphere

  object_sphere(float mass=1, float radius=1);
  ~object_sphere();

  virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
  virtual void draw();
  virtual bool detectCollision(const object_sphere* obj2);
//  virtual bool detectCollision(const object_plane* plane);
  //virtual bool doCollisions(const object_holder *allObjs);
  virtual void collide(const object_sphere *sphere2);
//  virtual void collide(const object_plane *plane);
};


#endif // SPHERE_H
