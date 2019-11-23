#include "planes.h"

object_planes::object_planes() : Objects<object_plane>()
{
  objType = PLANE;
//	objs = new object_plane[MAXOBJECTS];
}

object_planes::object_planes(int numObjs, float mass, float wid, float len, float ph, float th) : Objects<object_plane>(numObjs, mass)
{
  objType = PLANE;
//	objs = new object_plane[MAXOBJECTS];
  //addObjects(numObjs, mass, wid, len, rot,0,0,0);
}

void object_planes::addObjects(int numMass, float m, float wid, float len, float ph, float th, object_holder* holder, Vector3D basePos, Vector3D offsetDir, float distBetween, Vector3D mAxis)
{
  for(int i=0; i<numMass; i++)
  {
//		if(numOfMasses < MAXOBJECTS)
//		{
    objs.append(new object_plane(m, wid, len, ph, th, mAxis));
    object_plane* plane = objs.last();
            plane->self.index = objs.size();
      plane->self.holder = holder;
      plane->self.shape = objType;
//			objs[numOfMasses].mass->m = m;
      plane->mass->pos.x = basePos.x;
      plane->mass->pos.y = basePos.y;
      plane->mass->pos.z = basePos.z;
//			objs[numOfMasses].angles.x = ph;
//			objs[numOfMasses].angles.y = th;
//			objs[numOfMasses].width = wid;
//			objs[numOfMasses].length = len;
//			objs[numOfMasses++].makeBase(&mAxis);
//		}
  }

  return;
}
