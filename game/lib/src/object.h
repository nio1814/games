#ifndef OBJECTS
#define OBJECTS

/*#include <windows.h>
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>*/

//#include <GL/glu.h>

#include <3ds.h>

#include "mass.h"
#include <texture.h>
#include "camera.h"
#include "datastructs.h"

#include <qpointer.h>

extern GLfloat dt;
extern bool bGravityOn;
extern Vector3D gravityDir;
extern GLfloat gravityAcc;

#define MAXTEXTURE 100
enum Shape{PLANE, SPHERE, LINE, BOX, TRI};
#define NUMSHAPES 5
enum BoxSide{bTOP, bBOTTOM, bLEFT, bRIGHT, bFRONT, bBACK};
enum triPoint{triMID, triEND1, triEND2};

#define OBJECTPROPERTIES 14
#define SPHEREPROPERTIES 14
#define MAXOBJECTS 50
#define MAXTOUCHES 5

class Object;

class object_plane;
class object_planes;
class object_box;
class object_sphere;
class object_spheres;
class object_line;
class object_triangle;
class object_holder;

struct objP							//pointer to an object
{
	int index;
	Shape shape;
	const object_holder* holder;
};

struct objP3ds						//pointer to a 3ds object
{
	int faceidx;
	t3DObject* obj3ds;
};

bool isSame(objP p1, objP p2);


// class Objects		---> A container object for simulating masses
template <class T>
class Objects
{
public:
	int numOfMasses;								// number of masses in this container
	Shape objType; 
//	QVector<QPointer<T> > objs;
	QVector<T*> objs;
	
	Objects();
	Objects(int numOfMasses, float m);			// Constructor creates some masses with mass values m
	
	//virtual void addObject(int numOfMasses, float m);
	virtual void release();							// delete the masses created
	virtual void init();							// this method will call the init() method of every mass
	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
													// in advanced containers, this method will be overrided and some forces will act on masses
	}

	virtual void draw();					// 
	virtual void simulate(float dt);				// Iterate the masses by the change in time
	virtual void operate(const object_holder *allObjs);// The complete procedure of Objects
};


//single object
class Object
{
public:
	Mass* mass;									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)
	Shape objType; 
	texture_s* texture;
	Vector3D moveForce;							//force acting on object
	bool isTouching;							//object is touching something
	objP touchObj;
	bool isTouching3ds;
	objP3ds touchObj3ds;
	objP self;									//pointer to this object
	objP *touches;								//other objects this object is touching
	void* touches2[NUMSHAPES];
	int totalTouches;
	int numTouches[NUMSHAPES];
	bool bDraw;
	bool bDetect;
	bool bCollide;
	bool bVisible;
	bool bMovable;								//object can move
	
//	Object();
    Object(float m=1);							// Constructor creates some masses with mass values m
	~Object();
	virtual void init();							// this method will call the init() method of every mass
	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
													// in advanced containers, this method will be overrided and some forces will act on masses
	}

	virtual void draw()
	{												// 
	}

	virtual void simulate(float dt);				// Iterate the masses by the change in time
	//virtual bool doCollisions(const object_holder *allObjs);
	virtual void operate(const object_holder *allObjs);
	virtual void* getProperty(int idx, dataType &type);
	virtual bool detectCollision(const object_holder* objs);
	virtual bool detectCollision(const object_sphere* obj2){return false;};
};


//Sphere Container
class object_spheres : public Objects<object_sphere>
{
	public:
	object_spheres();
	object_spheres(int numObjs, float mass, float radius);
	
	void addObjects(int numOfMasses, float m, float radius, object_holder* holder, Vector3D basePos, Vector3D offsetDir);
	virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
	//virtual void operate(float dt, const object_holder *allObjs);
};


//Single Sphere
class object_sphere : public Object
{
public:
	float radius;
//	GLUquadricObj	*quad;						// Quadratic For Drawing A Sphere

	object_sphere();
	object_sphere(float mass, float radius);
	~object_sphere();
	
	virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
	virtual void draw();
	virtual bool detectCollision(const object_sphere* obj2);
	//virtual bool doCollisions(const object_holder *allObjs);
};


//Plane Container
class object_planes : public Objects<object_plane>
{
	public:
	//object_plane *objs;

	object_planes();
	object_planes(int numObjs, float mass, float wid, float len, float ph, float th);

	void addObjects(int numMass, float m, float wid, float len, float ph, float th, object_holder* holder, Vector3D basePos, Vector3D offsetDir, float distBetween, Vector3D mAxis);
	//virtual void operate(float dt, const object_holder *allObjs);// The complete procedure of Objects
};


//Single Plane--------------------------------------------------------
class object_plane : public Object
{
	public:
	float width, length;
	Vector3D normal, wvec, lvec;
	Vector2D angles;									//(phi, theta)
	bool touching;
	
	object_plane();
	object_plane(float mass, float wid, float len, float phi, float theta, Vector3D mAxis);
	virtual void draw();
	//virtual bool doCollisions(const object_holder *allObjs);
	//make length and width vectors by rotating from major axis
	void makeBase(const Vector3D* mAxis);
	void flipBase();
	bool inPlane(const Vector3D *v);
	bool atSurface(const Vector3D *v);
	bool isAbove(const Vector3D *v) const;
};

//Box-----------------------------------------------------------------
class object_box : public Object
{
public:
	float width, length, height;
	Vector3D normal, wvec, lvec;
	GLuint		texture[6];									// 1 Texture
	GLfloat rotate;
	Vector3D angles;
	bool touching[6];
	object_planes planes;
	
	object_box();
	object_box(float mass, float wid, float len, float hei, float ph, float th, Vector3D pos, Vector3D mAxis);
//	virtual void draw();
	//virtual bool doCollisions(const object_holder *allObjs);
//	void makeBase();
//	void flipBase();
};

//Line Container
class object_lines : public Objects<object_line>
{
	public:
	object_lines();

	//holder needed to assign object pointer to holder
	void addObjects(int numMass, float m, Vector3D v1, Vector3D v2, float cmf, object_holder* holder, Vector3D offsetDir, float offsetDist);
	//virtual void operate(float dt, const object_holder *allObjs);// The complete procedure of Objects
};

//Single Line
class object_line : public Object
{
public:
	Vector3D vertex[2];										//vertices
	float length, width;
	float comf;												//com location(as fraction from v1 to v2)
	Vector3D normal, lvec;
	Vector2D anglesSph;										//spherical angles(phi, theta)
	
	object_line();
	object_line(float mass, Vector3D v1, Vector3D v2);			//input mass and 2 vertices
	object_line(float mass, Vector3D v1, Vector3D v2, float cmf);			//input mass and 2 vertices and 
	virtual void draw();
	virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
	//virtual bool doCollisions(const object_holder *allObjs);
	virtual void* getProperty(int idx, dataType &type);
	void initGeo();
	void calcGeo();
	Vector3D calcVertexVel(int vnum);
};

//Single Triangle
class object_triangle : Object
{
	Vector3D vertex[3];

};


class object_holder
{
	public:
		Vector3D majorAxis;
		int numObjects;
		int numShape[NUMSHAPES];
		
		object_holder();
		~object_holder();
		object_sphere* addSpheres(int numObjs, float mass, float radius, Vector3D basePos, Vector3D offsetDir);
		object_sphere* addSpheres(float mass, float radius, Vector3D basePos);
		object_plane* addPlanes(int numObjs, float mass, float wid, float len, float ph, float th, Vector3D basePos, Vector3D offDir, float distBetween);
		object_plane* addPlanes(float mass, float wid, float len, float ph, float th, Vector3D basePos);
		object_line* addLines(int numObjs, float mass, Vector3D v1, Vector3D v2, float cmf, Vector3D offsetDir, float offsetDist);
		void setMass(Shape objType, int index, float mass);
		void setElas(Shape objType, int index, float el);
		void setPos(Shape objType, int index, Vector3D pos);
		void setVel(Shape objType, int index, Vector3D vel);
		void setForce(Shape objType, int index, Vector3D force);
		void setNormal(Shape objType, int index, Vector3D norm);
		void flipBase(Shape objType, int index);
		void setTexture(Shape objType, int index, texture_s* txr);
		void setColor(Shape objType, int index, const Vector3D& color);
		NodeClass<void*>* makeTree();
		
		object_sphere* getSphere(int index) const;
		object_plane* getPlane(int index);
		object_line* getLine(int index);

		void run(GLfloat dt);
		void draw();
	
	//private:
//		QList<QPointer<Object> > objects;
		object_spheres spheres;
//		QList<QPointer<object_sphere> > spheres;
		object_planes planes;
		object_lines lines;
		//object_boxes* boxes;
		pointerTree* tree;
};

bool detectCollision(Object *obj, const object_holder *allobj, objP &p);
bool detectCollision(object_sphere *sphere, const object_holder *allobj, objP &p);		//detect sphere-holder
bool detectCollision(object_line *line, const object_holder *allobj, objP &p, Vector3D *cp, Vector3D *cn);		//detect line-holder(input contact point and norm by reference)

#endif

