#include "objects.h"

#include "plane.h"
#include "sphere.h"

#include <cmath>


bool detectCollision(std::shared_ptr<object_sphere> sphere, std::shared_ptr<Plane> plane)
{
  Vector3D toPlane = sphere->pos - plane->pos;
  if(plane->normal().length() < 1e7)
    return false;
  GLfloat normalDistance = std::abs(toPlane.dot(plane->normal()));
  
  if (normalDistance <= sphere->radius)
  {
    GLfloat wDist = fabs(toPlane.dot(plane->right()));
    if (wDist <= .5f * plane->width)
    {
      GLfloat lDist = fabs(toPlane.dot(plane->forward()));
      if (lDist <= .5f * plane->length)
      {
        //detect = true;
        sphere->addTouchedObject(plane);
        plane->addTouchedObject(sphere);
        //m_touchedObjects.append(plane);
        //                p.index = pidx;
        //                p.shape = plane->objType;
        //                p.holder = allobj;
                //p.holder = reinterpret_cast<object_holder*>(allobj);
        return true;
      }
    }
  }

  return false;
}

bool detectCollision(Object::Pointer object1, Object::Pointer object2)
{
  if (object1->shape == Object::SPHERE && object2->shape == Object::PLANE)
    return detectCollision(std::dynamic_pointer_cast<object_sphere>(object1), std::dynamic_pointer_cast<Plane>(object2));
  else if(object2->shape == Object::SPHERE && object1->shape == Object::PLANE)
    return detectCollision(std::dynamic_pointer_cast<object_sphere>(object2), std::dynamic_pointer_cast<Plane>(object1));

  return false;
}

void collide(std::shared_ptr<object_sphere> sphere, std::shared_ptr<const Plane> plane)
{
  GLfloat MINBOUNCEVEL = .1f;

  GLfloat m1, m2, v1normMag;
  Vector3D v1, v2, vpara, planeNorm;
  //int awayDir;

  m1 = sphere->m;
  m2 = plane->m;
  v1 = sphere->vel;
  v2 = plane->vel;

  /*if(plane->isAbove(&mass->pos))
    planeNorm = plane->normal;
  else
    planeNorm = plane->normal*-1;*/
  planeNorm = (sphere->pos - plane->pos).proj(plane->normal());
  planeNorm.unitize();
  v1normMag = fabs(v1.dot(planeNorm));

  if (fabs(v1.length()) < MINBOUNCEVEL)
    v1 -= v1;
  else if (plane->bMovable)
    v1 = v1 * ((m1 - m2) / (m1 + m2)) + v2 * (2 * m2 / (m1 + m2));
  else
    v1 += planeNorm * (1 + sphere->elasticity) * v1normMag;

  sphere->velnew = v1;
  sphere->force += planeNorm * std::abs(planeNorm.dot(sphere->force));

  sphere->pos += planeNorm * (sphere->radius - planeNorm.dot(sphere->pos - plane->pos));

  vpara = v1 - v1.proj(Y);

  //	sphere->xrotspeed = vpara.dot(&Vector3D(0,0,1))/(sphere->radius*2*PI);
  sphere->avelnew = vpara.dot(Vector3D(0, 0, 1)) / (sphere->radius * 2 * M_PI);
  //	sphere->zrotspeed = vpara.dot(&Vector3D(-1,0,0))/(sphere->radius*2*PI);
  sphere->avelnew += vpara.dot(Vector3D(-1, 0, 0)) / (sphere->radius * 2 * M_PI);
}


void collide(Object::Pointer object1, Object::ConstPointer object2)
{
  if (object1->shape == Object::SPHERE && object2->shape == Object::PLANE)
    collide(std::dynamic_pointer_cast<object_sphere>(object1), std::dynamic_pointer_cast<const Plane>(object2));
}

Object::Pointer Objects::addObject(Object::Pointer object)
{
  this->objects.push_back(object);
//  T* newObj = objs.last();
//  newObj->self.index = objs.size();
  //	newObj->self.holder = holder;
//  newObj->self.shape = objType;

  return object;
}

std::shared_ptr<Plane> Objects::addPlane(const float width, const float length, const Vector3D& position, const float phi, const float theta, const Vector3D majorAxis)
{
  std::shared_ptr<Plane> plane = std::make_shared<Plane>(width, length, position, phi, theta, majorAxis);
  this->addObject(plane);

  return plane;
}

std::shared_ptr<Plane> Objects::addPlane(const float width, const float length, const Vector3D& position, const Vector3D normal, const Vector3D& right)
{
  std::shared_ptr<Plane> plane = std::make_shared<Plane>(width, length, position, normal, right);
  this->addObject(plane);

  return plane;
}

int Objects::size() const
{
  return this->objects.size();
}

Object::Pointer Objects::last()
{
  return this->objects.back();
}

void Objects::draw()
{
  //	for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
  //  for(int a=0; a<objs.size(); a++)
  for(const Object::Pointer object : this->objects)
    {
      if(object->bDraw)
        object->draw();
    }

  return;
}

void Objects::simulate(float dt)					// Iterate the masses by the change in time
{
  //	for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
  //  for(int a=0; a<objs.size(); a++)
  for (Object::Pointer object : this->objects)
  {
    object->simulate(dt);				// Iterate the mass and obtain new position and new velocity
  }
}

void Objects::detectCollisions()
{
  for (Object::Pointer object : this->objects)
    object->clearTouchedObjects();

  for (size_t index1 = 0; index1 < this->objects.size(); index1++)
  {
    std::shared_ptr<Object> object1 = this->objects[index1];
    for (size_t index2 = index1 + 1; index2 < this->objects.size(); index2++)
    {
      std::shared_ptr<Object> object2 = this->objects[index2];
      if (object1->shape == object2->shape)
        object1->detectCollision(object2);
      else
        detectCollision(object1, object2);
    }
  }
}

void Objects::run(const float timeDelta)
{
  this->detectCollisions();

  for (Object::Pointer object : this->objects)
  {
    for (Object::ConstPointer objectTouched : object->touchedObjects)
    {
      if (object->shape == objectTouched->shape)
        object->collide(objectTouched);
      else
        collide(object, objectTouched);
    }
  }

  for (Object::Pointer object : this->objects)
  {
    object->solve();
    object->simulate(timeDelta);
  }
}

