#include "lines.h"

object_lines::object_lines() : Objects<object_line>()
{
  objType = LINE;
//	objs = new object_line[MAXOBJECTS];
}

void object_lines::addObjects(int numMass, float m, Vector3D v1, Vector3D v2, float cmf, object_holder* holder, Vector3D offsetDir, float offsetDist)
{
  for(int i=0; i<numMass; i++)
  {
//		if(numOfMasses < MAXOBJECTS)
//		{
    objs.append(new object_line(m, v1, v2, cmf));
    object_line* line = objs.last();
            line->self.index = size();
      line->self.holder = holder;
      line->self.shape = objType;
//			objs[numOfMasses].mass->m = m;
//			objs[numOfMasses].vertex[0] = v1;
//			objs[numOfMasses].vertex[1] = v2;
      line->initGeo();
//		}
  }

  return;
}
