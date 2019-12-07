#ifndef OBJECTS
#define OBJECTS

/*#include <windows.h>
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>*/

//#include <GL/glu.h>

#include <QVector3D>
#include <QVector>
#include <QList>

#include <3ds.h>

#include "mass.h"
#include <texture.h>
//#include "camera.h"
#include "datastructs.h"

#include "qtgl.h"

#include <memory>

extern GLfloat dt;
extern bool bGravityOn;
extern Vector3D gravityDir;
extern GLfloat gravityAcc;


#define MAXTEXTURE 100
#define NUMSHAPES 5
enum BoxSide{bTOP, bBOTTOM, bLEFT, bRIGHT, bFRONT, bBACK};
enum triPoint{triMID, triEND1, triEND2};

#define OBJECTPROPERTIES 14
#define SPHEREPROPERTIES 14
#define MAXOBJECTS 50
#define MAXTOUCHES 5

class object_triangle;



struct objP3ds						//pointer to a 3ds object
{
	int faceidx;
	t3DObject* obj3ds;
};


// class Objects		---> A container object for simulating masses


//single object
class Object : public Mass
{
public:
  using Pointer = std::shared_ptr<Object>;
  using ConstPointer = std::shared_ptr<const Object>;
  enum Shape{PLANE, SPHERE, LINE, BOX, TRI};

//  void setPosition(Vector3D position);
  void setGravity(const Vector3D gravity);
	
//	Object();
   Object(const Vector3D &position=Vector3D(), const float mass=1);							// Constructor creates some masses with mass values m
    Object(const Object& obj);
//	~Object();

    Object& operator= (const Object& obj);

	virtual void init();							// this method will call the init() method of every mass
	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
													// in advanced containers, this method will be overrided and some forces will act on masses
	}

	virtual void draw()
	{												// 
	}

  void simulate(const float dt);				// Iterate the masses by the change in time

    virtual void rotate(Vector3D axis, GLfloat degrees)
    {
      Q_UNUSED(axis);
      Q_UNUSED(degrees);
    }

//	virtual void operate(const object_holder *allObjs);
  virtual void* getProperty(int idx, dataType &shape);
	virtual bool detectCollision(std::shared_ptr<Object> object) = 0;
  bool touching(ConstPointer object);
  bool touching();
//  virtual bool detectCollision(const object_sphere* obj2)
//  {
//    Q_UNUSED(obj2);
//    return false;
//  }

//  virtual bool detectCollision(const object_plane* plane)
//  {
//    Q_UNUSED(plane);
//    return false;
//  }

//  virtual bool detectCollision(const object_line* line)
//  {
//    Q_UNUSED(line);
//    return false;
//  }

//	virtual void collisions();
  virtual void collide(ConstPointer object) = 0;
//	virtual void collide(const object_sphere* sphere){};
//	virtual void collide(const object_plane* plane){};
//	virtual void collide(const object_line* line){};
  void addTouchedObject(Pointer object);
  void clearTouchedObjects();
  
  bool bDraw;
  bool bMovable;								//object can move
  Shape shape;
  Vector3D moveForce;							//force acting on object
  Texture texture;
  std::vector<std::shared_ptr<const Object>> touchedObjects;
protected:
  bool hasTexture();

  matrix2D3 basis;
private:
  bool isTouching;							//object is touching something
  bool isTouching3ds;
  objP3ds touchObj3ds;
  //	objP *touches;								//other objects this object is touching
  //	void* touches2[NUMSHAPES];
  //	int totalTouches;
  //	int numTouches[NUMSHAPES];
  bool bDetect;
  bool bCollide;
  bool bVisible;
  Vector3D gravity;
};

//Single Triangle
class object_triangle : Object
{
	Vector3D vertex[3];

};



//bool detectCollision(Object *obj, const object_holder *allobj, objP &p);
//bool detectCollision(object_sphere *sphere, const object_holder *allobj, objP &p);		//detect sphere-holder
//bool detectCollision(object_line *line, const object_holder *allobj, objP &p, Vector3D *cp, Vector3D *cn);		//detect line-holder(input contact point and norm by reference)

#endif

