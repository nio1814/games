#ifndef SPHERES_H
#define SPHERES_H

#include "objects.h"


class object_spheres : public Objects<object_sphere>
{
  public:
  object_spheres();
  object_spheres(int numObjs, float mass, float radius);

  void addObjects(int numOfMasses, float m, float radius, object_holder* holder, Vector3D basePos, Vector3D offsetDir);
  virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
  //virtual void operate(float dt, const object_holder *allObjs);
};


#endif // SPHERES_H
