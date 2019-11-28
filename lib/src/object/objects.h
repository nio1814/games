#ifndef OBJECTS_H
#define OBJECTS_H

#include "object.h"

class object_plane;

class Objects
{
public:
    int size() const;								// number of masses in this container
    Object::Pointer last();

  Shape objType;
//	QVector<QPointer<T> > objs;

//  Objects();
//  Objects(int numOfMasses, float m);			// Constructor creates some masses with mass values m

  //virtual void addObject(int numOfMasses, float m);
  Object::Pointer addObject(Object::Pointer object);
  std::shared_ptr<object_plane> addPlane(const float mass, const float width, const float length, const float phi, const float theta, const Vector3D majorAxis);
  std::shared_ptr<object_plane> addPlane(const float width, const float length, const Vector3D position, const Vector3D normal, const matrix2D3 basis);

  Vector3D majorAxis;
  matrix2D3 m_basis;

//  virtual void release();							// delete the masses created
//  virtual void init();							// this method will call the init() method of every mass
//  virtual void solve()							// no implementation because no forces are wanted in this basic container
//  {
                          // in advanced containers, this method will be overrided and some forces will act on masses
//  }

  void draw();					//
  void simulate(float dt);				// Iterate the masses by the change in time
//  virtual void operate(const object_holder *allObjs);// The complete procedure of Objects
  void detectCollisions();
  void run(const float timeDelta);
private:
  std::vector<Object::Pointer> objects;
};



//template <class T>
//Objects<T>::Objects(int numOfMasses, float m)		// Constructor creates some masses with mass values m
//{
//  Objects();
////	this->numOfMasses = numOfMasses;

//  /*movable = false;
//  masses = new Mass*[numOfMasses];			// Create an array of pointers
//  moveForce = Vector3D(0,0,0);

//  for (int a = 0; a < numOfMasses; ++a)		// We will step to every pointer in the array
//    masses[a] = new Mass(m);				// Create a Mass as a pointer and put it in the array
//  */
//}

//template <class T>
//void Objects<T>::release()							// delete the masses created
//{
//  /*for (int a = 0; a < numOfMasses; ++a)		// we will delete all of them
//  {
//    delete(masses[a]);
//    masses[a] = NULL;
//  }

//  delete(masses);
//  masses = NULL;*/
//}

//template <class T>
//void Objects<T>::init()								// this method will call the init() method of every mass
//{
////	for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
//  for(int a=0; a<objs.size(); a++)
//    objs[a]->mass->init();						// call init() method of the mass
//}





//template <class T>
//void Objects<T>::operate(const object_holder *allObjs)					// The complete procedure of Objects
//{
////	if(objs != NULL)
////	{
////		for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
//    for(int a=0; a<objs.size(); a++)
//    {
//      objs[a]->operate(allObjs);
//    }
////	}

//  return;
//}

//void Object::collisions()
//{
//	for(int n=0; n<m_touchedObjects.size(); n++)
//	{
//		const Object* touchedObj = m_touchedObjects[n];
//		switch(touchedObj->objType)
//		{
//			case SPHERE:
//				collide(static_cast<const object_sphere*>(m_touchedObjects[n]));
//				break;
//			case PLANE:
//				collide(static_cast<const object_plane*>(m_touchedObjects[n]));
//				break;
//		}
//	}
///*        if(point.shape == SPHERE)
//			collide(this, &allObjs->spheres->objs[point.index]);
//		else if(point.shape == PLANE)
//			collide(this, &allObjs->planes->objs[point.index]);*/


//	return;
//}



#endif // OBJECTS_H
