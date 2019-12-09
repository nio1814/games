#include "collection.h"
#include "sphere.h"

object_holder::object_holder()
{
  numObjects = 0;
  majorAxis = Z;
  //spheres = new object_spheres;
  //planes = new object_planes;
  //lines = new object_lines;
  tree = new pointerTree;
}

object_holder::~object_holder()
{
  //delete spheres;
  //delete planes;
  //delete lines;
  delete tree;
}

object_sphere* object_holder::addSpheres(int numObjs, float mass, float radius, Vector3D basePos, Vector3D offsetDir)
{
  object_sphere* sphereout = NULL;

  spheres.addObjects(numObjs, mass, radius, this, basePos, offsetDir);
//    object_sphere sphere(mass, radius);
//    sphere.mass->pos = basePos;
//	sphereout = &spheres->objs[numObjects];
  sphereout = spheres.objs.last();
  numObjects += numObjs;

  //objects.append(new object_sphere(mass, radius));
  //QPointer<Object> newObj = objects.last();
  //newObj->mass->pos = basePos;

  return sphereout;
}

object_sphere* object_holder::addSpheres(float mass, float radius, Vector3D basePos)
{
  object_sphere* sphereout = NULL;

  spheres.addObjects(1, mass, radius, this, basePos, Vector3D(0,0,0));
//    object_sphere sphere(mass, radius);
//    sphere.mass->pos = basePos;
//	sphereout = &spheres->objs[numObjects];
    sphereout = spheres.objs.last();
  numObjects++;

  return sphereout;
}

void object_holder::addPlane(const Plane &plane)
{
    planes.addObject(plane);
}

Plane* object_holder::addPlanes(int numObjs, float mass, float wid, float len, float ph, float th, Vector3D basePos, Vector3D offDir, float distBetween)
{
  Plane* planeout = NULL;

  planes.addObjects(numObjs, mass, wid, len, ph, th, this, basePos, offDir, distBetween, majorAxis);
  numObjects += numObjs;

  return planeout;
}

Plane* object_holder::addPlanes(float mass, float wid, float len, float ph, float th, Vector3D basePos)
{
  Plane* planeout = NULL;

  planes.addObjects(1, mass, wid, len, ph, th, this, basePos, Vector3D(0,0,0), 0, majorAxis);
  numObjects++;

  return planeout;
}

Line* object_holder::addLines(int numObjs, float mass, Vector3D v1, Vector3D v2, float cmf, Vector3D offsetDir, float offsetDist)
{
  Line* lineout = NULL;

  lines.addObjects(numObjs, mass, v1, v2, cmf, this, offsetDir, offsetDist);
  numObjects += numObjs;

  return lineout;
}

void object_holder::run(GLfloat dt)
{
  spheres.operate(this);
//	for(int s=0; s<spheres.size(); s++)
//		spheres[s].operate(this);
  lines.operate(this);
  planes.operate(this);

//	for(int s=0; s<spheres.size(); s++)
//		spheres[s].simulate(dt);								// Step 3: iterate the masses by the change in time
    spheres.simulate(dt);
  lines.simulate(dt);
  planes.simulate(dt);

  return;
}

void object_holder::draw()
{
  spheres.draw();
  planes.draw();
  lines.draw();

  return;
}

void object_holder::setMass(Shape objType, int index, float mass)
{
  if(objType == SPHERE)
    spheres.objs[index]->mass->m = mass;
//        spheres[index].mass->m = mass;
  else if(objType == PLANE)
    planes.objs[index]->mass->m = mass;

  return;
}

void object_holder::setElas(Shape objType, int index, float el)
{
  if(objType == SPHERE)
    spheres.objs[index]->mass->elas = el;
//		spheres[index].mass->elas = el;
  else if(objType == PLANE)
    planes.objs[index]->mass->elas = el;

  return;
}

void object_holder::setPos(Shape objType, int index, Vector3D pos)
{
  if(objType == SPHERE)
    spheres.objs[index]->mass->pos = pos;
//		spheres[index].mass->pos = pos;
  else if(objType == PLANE)
    planes.objs[index]->mass->pos = pos;

  return;
}

void object_holder::setNormal(Shape objType, int index, Vector3D norm)
{
  if(objType == PLANE)
  {
    planes.objs[index]->normal = norm.unit();
    planes.objs[index]->makeBase(&majorAxis);
  }

  return;
}

void object_holder::flipBase(Shape objType, int index)
{
  if(objType == PLANE)
  {
    planes.objs[index]->flipBase();
  }

  return;
}


void object_holder::setTexture(Shape objType, int index, texture_s* txr)
{
  if(objType == SPHERE)
    spheres.objs[index]->texture = txr;
//		spheres[index].texture = txr;
  else if(objType == PLANE)
    planes.objs[index]->texture = txr;

  return;
}

void object_holder::setColor(Shape objType, int index, const Vector3D& color)
{
  if(objType == SPHERE)
    if(spheres.objs[index]->texture)
      spheres.objs[index]->texture->color = color;
//        spheres[index].texture->color = color;
  else if(objType == PLANE)
    planes.objs[index]->texture->color = color;

  return;
}

NodeClass<void*>* object_holder::makeTree()
{
  void* pt = this;
  string sphere = "sphere ";
  string plane = "plane ";
  string line = "line ";
  char numtext[15];
  char blanktext[15];

  if(tree != NULL)
    delete tree;

  tree = new pointerTree;

    for(int s = 0; s<spheres.size(); s++)
//	for(int s = 0; s<spheres.size(); s++)
  {
    sprintf(numtext, "%i", s+1);
    tree->addLeaf(spheres.objs[s], tpOBJECT, sphere + numtext);
    //tree->addLeaf(&spheres[s], tpOBJECT, sphere + numtext);
  }
    for(int p = 0; p<planes.size(); p++)
  {
    sprintf(numtext, "%i", p+1);
    tree->addLeaf(&planes.objs[p], tpOBJECT, plane + numtext);
  }
    for(int l = 0; l<lines.size(); l++)
  {
    sprintf(numtext, "%i", l+1);
    tree->addLeaf(&lines.objs[l], tpOBJECT, line + numtext);
  }

  return tree;
}

object_sphere* object_holder::getSphere(int index) const
{
  return spheres.objs[index];
//    return &spheres[index];
}

Plane* object_holder::getPlane(int index) const
{
  return planes.objs[index];
}

Line* object_holder::getLine(int index) const
{
  return lines.objs[index];
}

bool isSame(objP p1, objP p2)
{
  bool same = true;

  if(p1.index != p2.index)
    same = false;
  else if(p1.shape != p2.shape)
    same = false;
  else if(p1.holder != p2.holder)
    same = false;

  return same;
}
