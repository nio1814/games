#include "box.h"

object_box::object_box() : Object()
{
  width = 0.0f;
  length = 0.0f;
  height = 0.0f;
  rotate = 0.0f;

  for(int i=0; i<6; i++)
    touching[i] = false;
}

object_box::object_box(float mass, float wid, float len, float hei, float ph, float th, Vector3D pos, Vector3D mAxis) : Object(mass)
{
  Vector3D currentAxis;

  object_box();
  currentAxis = mAxis.rotatePhiTheta(&mAxis, ph, th);
  planes.addObjects(2, mass, wid, len, ph, th, NULL, pos + (currentAxis*.5f*hei) + pos, -currentAxis, hei, mAxis);
}
