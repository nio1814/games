#include "objects.h"

#include "plane.h"

Object::Pointer Objects::addObject(Object::Pointer object)
{
  this->objects.push_back(object);
//  T* newObj = objs.last();
//  newObj->self.index = objs.size();
  //	newObj->self.holder = holder;
//  newObj->self.shape = objType;

  return object;
}

std::shared_ptr<object_plane> Objects::addPlane(const float mass, const float width, const float length, const float phi, const float theta, const Vector3D majorAxis)
{
  std::shared_ptr<object_plane> plane = std::make_shared<object_plane>(mass, width, length, phi, theta, majorAxis);
  this->addObject(plane);

  return plane;
}

std::shared_ptr<object_plane> Objects::addPlane(const float width, const float length, const Vector3D position, const Vector3D normal, const matrix2D3 basis)
{
  std::shared_ptr<object_plane> plane = std::make_shared<object_plane>(width, length, position, normal, basis);
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
    object->mass->simulate(dt);				// Iterate the mass and obtain new position and new velocity
}

void Objects::detectCollisions()
{
  for (int index1 = 0; index1 < this->objects.size(); index1++)
  {
    std::shared_ptr<Object> object1 = this->objects[index1];
    for (int index2 = index1 + 1; index2 < this->objects.size(); index2++)
    {
      std::shared_ptr<Object> object2 = this->objects[index2];
    }
  }
}

void Objects::run(const float timeDelta)
{
  for (Object::Pointer object : this->objects)
  {
    object->simulate(timeDelta);
  }
}

