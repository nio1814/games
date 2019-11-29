#ifndef PLANES_H
#define PLANES_H

#include "objects.h"
#include "plane.h"


class object_planes : public Objects<Plane>
{
  public:
  //object_plane *objs;

  object_planes();
  object_planes(int numObjs, float mass, float wid, float len, float ph, float th);

  void addObjects(int numMass, float m, float wid, float len, float ph, float th, object_holder* holder, Vector3D basePos, Vector3D offsetDir, float distBetween, Vector3D mAxis);
  //virtual void operate(float dt, const object_holder *allObjs);// The complete procedure of Objects
};

#endif // PLANES_H
