#include "object.h"

#include <math.h>
#include <string.h>
#include <sstream>

#include "constants.h"
//#include "text.h"
#include "keys.h"
#include "camera.h"
#include "vector3d.h"
#include "mass.h"
#include "texture.h"
#include "sphere.h"

GLfloat dt;										//time between rendering used to scale movement
bool bGravityOn = false;
GLfloat gravityAcc = 9.8f;
Vector3D gravityDir;

//SINGLE OBJECT----------------------------
Object::Object(const Vector3D& position, const float mass) :
  Mass(position, mass),
  bDraw(true),
  isTouching(false),
  isTouching3ds(false),
  bDetect(true)
{
  bMovable = false;
  basis.A[0] = X;
  basis.A[1] = Y;
  basis.A[2] = Z;
}

//Object::Object(float m) : Object()			// Constructor creates some masses with mass values m
//{
////	Object();
////	delete mass;
//	mass = new Mass(m);				// Create a Mass as a pointer and put it in the array
//}

Object::Object(const Object &obj) : Mass()
{
    *this = obj;
}

Object& Object::operator = (const Object& obj)
{
//    mass = new Mass(*obj.mass);									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)
    shape = obj.shape;
    texture = obj.texture;
    moveForce = obj.moveForce;							//force acting on object
    isTouching = obj.isTouching;							//object is touching something
    isTouching3ds = obj.isTouching3ds;
    touchObj3ds = obj.touchObj3ds;
//    memcpy(touches, obj.touches, MAXTOUCHES*sizeof(objP));
    //touches2[NUMSHAPES];
//    memcpy(touches2, obj.touches2, MAXTOUCHES*sizeof(Shape));
//    totalTouches = obj.totalTouches;
    //numTouches[NUMSHAPES];
    bDraw = obj.bDraw;
    bDetect = obj.bDetect;
    bCollide = obj.bCollide;
    bVisible = obj.bVisible;
    bMovable = obj.bMovable;

    touchedObjects = obj.touchedObjects;

    return *this;
}

//Object::~Object()
//{
//	delete mass;				// Create a Mass as a pointer and put it in the array
//	delete touches;
//	delete texture;
//}

void Object::init()								// this method will call the init() method of every mass
{
	touchedObjects.clear();
//	mass->init();						// call init() method of the mass
  if(bGravityOn)
  {
//        gravityVec =

	}
}

void Object::simulate(const float dt)					// Iterate the masses by the change in time
{
  this->forcenew += this->gravity;
  Mass::simulate(dt);				// Iterate the mass and obtain new position and new velocity
}

//void Object::operate(const object_holder *allObjs)					// The complete procedure of Objects
//{
//	if(bMovable)
//	{
//		init();										// Step 1: reset forces to zero(and do gravity)
////		detectCollision(allObjs);
////		collisions();
//		solve();									// Step 2: apply forces
//	}
	
//}


/*bool Object::doCollisions(const object_holder *allObjs)
{
	bool detect = false;
	objP point;

	detect = detectCollision(this, allObjs, point);

	if(detect)
	{
		isTouching = true;
		//collide(this, allObjs, point);
	}

	return detect;
}*/

void* Object::getProperty(int idx, dataType &type)
{
	void* ptr = NULL;

	switch(idx)
	{
//  case 0:
//    ptr = mass;
//    type = tpMASS;
//    break;
  case 1:
		ptr = &type;
		type = tpSHAPE;
		break;
	case 2:
    ptr = &texture;
		type = tpTEXTURE;
		break;
	case 3:
		ptr = &bMovable;
		type = tpBOOL;
		break;
	case 4:
		ptr = &moveForce;
		type = tpVECTOR3D;
		break;
	case 5:
		ptr = &isTouching;
		type = tpBOOL;
		break;
//	case 6:
//		ptr = &touchObj;
//		type = tpOBJP;
//		break;
	case 7:
		ptr = &isTouching3ds;
		type = tpBOOL;
		break;
	case 8:
		//ptr = touchObj3ds;
		//type = tpMASS;
		break;
//	case 9:
//		ptr = &self;
//		type = tpOBJP;
//		break;
	case 10:
//		ptr = touches;
		type = tpOBJP;
		break;
	case 11:
		ptr = &bDraw;
		type = tpBOOL;
		break;
	case 12:
		ptr = &bDetect;
		type = tpBOOL;
		break;
	case 13:
		ptr = &bCollide;
		type = tpBOOL;
		break;
	default:
		break;
	}

  return ptr;
}

bool Object::touching(ConstPointer object)
{
  return std::find(this->touchedObjects.cbegin(), this->touchedObjects.cend(), object) != this->touchedObjects.cend();
}

bool Object::touching()
{
  return this->touchedObjects.size() > 0;
}

void Object::addTouchedObject(Pointer object)
{
  if (!this->touching(object))
    this->touchedObjects.push_back(object);
}

void Object::clearTouchedObjects()
{
  this->touchedObjects.clear();
}

bool Object::hasTexture()
{
  return this->texture.hasTextures();
}

void Object::setGravity(const Vector3D gravity)
{
//  mass->force ;
  this->gravity = gravity;
//  forcenew = force = this->gravity * m;
}

//bool Object::detectCollision(const object_holder* objs)
//{
//	bool detect = false;
//	const object_sphere* spherePoint;
	
//    for(int sidx = 0; sidx < objs->spheres.size(); sidx++)
////    for(int sidx = 0; sidx < objs->spheres.size(); sidx++)
//	{
//		spherePoint = objs->getSphere(sidx);
//		detectCollision(objs->getSphere(sidx));
//	}

//    for(int p=0; p<objs->planes.size(); p++)
//        detectCollision(objs->getPlane(p));
//	for(int l=0; l<objs->lines.size(); l++)
//		detectCollision(objs->getLine(l));

//	return detect;
	
//}


//SPHERE CONTAINER------------------------------



//SINGLE SPHERE----------------------------------------------


//PLANE CONTAINER---------------------------



//SINGLE PLANE----------------------------


//BOX---------------------------

	

//LINE CONTAINER---------------------------



//SINGLE LINE----------------------------- 
//object_line::object_line() : Object()
//{
//	objType = LINE;
//	vertex[0] = Vector3D(0,0,0);
//	vertex[1] = Vector3D(1,0,0);
//	comf = .5f;
//	moveForce = Vector3D(0,0,0);
//	bMovable = true;
//	initGeo();
//}



//object_line::object_line(float mass, Vector3D v1, Vector3D v2, float cmf) : Object(mass)
//{
//	Object();
//	object_line();
//	vertex[0] = v1;
//	vertex[1] = v2;
//	initGeo();
//    bMovable = true;
//}



/*bool object_line::doCollisions(const object_holder *allObjs)
{
	bool detect = false;
	objP point;
	Vector3D *contactPoint, *contactNorm;
	contactPoint = new Vector3D;
	contactNorm = new Vector3D;

	detect = detectCollision(this, allObjs, point, contactPoint, contactNorm);

	if(detect)
	{
		isTouching = true;
		switch(point.shape)
		{
			case PLANE:
				collide(this, &allObjs->planes->objs[point.index], *contactPoint, *contactNorm);
			default:
				break;
		}
	}
	
	delete contactPoint;
	delete contactNorm;

	return detect;
}*/




//OBJECT HOLDER----------------------------------------------




//FUNCTION DEFINITIONS

