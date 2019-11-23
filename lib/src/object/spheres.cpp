#include "spheres.h"

#include "sphere.h"

object_spheres::object_spheres() : Objects<object_sphere>()
{
  objType = SPHERE;
  //objs = reinterpret_cast<object_sphere*>(new object_sphere[NUMOBJECTS]);
//	objs = new object_sphere[MAXOBJECTS];

}

object_spheres::object_spheres(int numObjs, float mass, float radius) : Objects<object_sphere>(numObjs, mass)
{
  objType = SPHERE;
  //objs = reinterpret_cast<object_sphere*>(new object_sphere[NUMOBJECTS]);
//	objs = new object_sphere[MAXOBJECTS];
  //addObjects(numObjs, mass, radius);

  /*
  moveForce = Vector3D(0,0,0);

  for (int a = 0; a < numOfMasses; ++a)		// We will step to every pointer in the array
  {
    masses[a] = new Mass(mass);
    radii[a] = radius;
    xrot[a] = yrot[a] = xrotspeed[a] = yrotspeed[a] = 0.0f;
  }*/
}

void object_spheres::addObjects(int numMass, float m, float radius, object_holder* holder, Vector3D basePos, Vector3D offsetDir)
{
  for(int i=0; i<numMass; i++)
  {
//		if(numOfMasses < MAXOBJECTS)
//		{
    objs.append(new object_sphere(m, radius));
    object_sphere* sphere = objs.last();
      sphere->self.index = objs.size();
      sphere->self.holder = holder;
            sphere->self.shape = objType;
//			objs[numOfMasses]->mass->m = m;
      sphere->mass->pos.x = basePos.x;
      sphere->mass->pos.y = basePos.y;
      sphere->mass->pos.z = basePos.z;
//			objs[numOfMasses++].radius = radius;
//		}
  }

  return;
}

void object_spheres::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
    for (int a = 0; a < size(); ++a)								//we will apply force to all masses (actually we have 1 mass, but we can extend it in the future)
  {
    objs[a]->solve();
  }
}
