#ifndef LINES_H
#define LINES_H

#include "line.h"
#include "objects.h"

class object_lines : public Objects<Line>
{
  public:
  object_lines();

  //holder needed to assign object pointer to holder
  void addObjects(int numMass, float m, Vector3D v1, Vector3D v2, float cmf, object_holder* holder, Vector3D offsetDir, float offsetDist);
  //virtual void operate(float dt, const object_holder *allObjs);// The complete procedure of Objects
};

#endif // LINES_H
