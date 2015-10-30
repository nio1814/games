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

GLfloat dt;										//time between rendering used to scale movement
bool bGravityOn = false;
GLfloat gravityAcc = 9.8f;
Vector3D gravityDir;

//Object Container--------------------------------
template <class T>
Objects<T>::Objects()
{
	numOfMasses = 0;
	objs = NULL;
}

template <class T>
Objects<T>::Objects(int numOfMasses, float m)		// Constructor creates some masses with mass values m
{
	Objects();
	this->numOfMasses = numOfMasses;

	/*movable = false;
	masses = new Mass*[numOfMasses];			// Create an array of pointers
	moveForce = Vector3D(0,0,0);

	for (int a = 0; a < numOfMasses; ++a)		// We will step to every pointer in the array
		masses[a] = new Mass(m);				// Create a Mass as a pointer and put it in the array
	*/
}

template <class T>
void Objects<T>::release()							// delete the masses created
{
	/*for (int a = 0; a < numOfMasses; ++a)		// we will delete all of them
	{
		delete(masses[a]);
		masses[a] = NULL;
	}
		
	delete(masses);
	masses = NULL;*/
}

template <class T>
void Objects<T>::init()								// this method will call the init() method of every mass
{
	for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
		objs[a].mass->init();						// call init() method of the mass
}

template <class T>
void Objects<T>::draw()
{
	for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
	{
		if(objs[a].bDraw)
			objs[a].draw();
	}

	return;
}

template <class T>
void Objects<T>::simulate(float dt)					// Iterate the masses by the change in time
{
	for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
		objs[a].mass->simulate(dt);				// Iterate the mass and obtain new position and new velocity
}

template <class T>
void Objects<T>::operate(const object_holder *allObjs)					// The complete procedure of Objects
{
	if(objs != NULL)
	{
		for (int a = 0; a < numOfMasses; ++a)		// We will iterate every mass
		{
			objs[a].operate(allObjs);
		}
	}

	return;
}


//SINGLE OBJECT----------------------------
Object::Object()
{
	bMovable = false;
	mass = new Mass(1);				// Create a Mass as a pointer and put it in the array
	touches = new objP[MAXTOUCHES];
	touches2[PLANE] = new object_plane*[MAXTOUCHES];
	touches2[SPHERE] = new object_sphere*[MAXTOUCHES];
	touches2[LINE] = new object_line*[MAXTOUCHES];
	touches2[BOX] = new object_box*[MAXTOUCHES];
	totalTouches = 0;
	for(int i=0;i<NUMSHAPES;i++)
		numTouches[i] = 0;
//	texture = &nullTexture;
	bDraw = true;
	bDetect = true;
	bCollide = true;
	bVisible = true;
	isTouching = false;
	isTouching3ds = false;
}

Object::Object(float m)			// Constructor creates some masses with mass values m
{
	Object();
	delete mass;
	mass = new Mass(m);				// Create a Mass as a pointer and put it in the array
}

Object::~Object()
{
	delete mass;				// Create a Mass as a pointer and put it in the array
	delete touches;
	delete texture;
}

void Object::init()								// this method will call the init() method of every mass
{
	mass->init();						// call init() method of the mass
	if(bGravityOn)
	{
		gravityVec = 
		mass->force = gravityVec*mass->m;
		mass->forcenew = mass->force;
	}
}

void Object::simulate(float dt)					// Iterate the masses by the change in time
{
	mass->simulate(dt);				// Iterate the mass and obtain new position and new velocity
}

void Object::operate(const object_holder *allObjs)					// The complete procedure of Objects
{
	if(bMovable)
	{
		init();										// Step 1: reset forces to zero(and do gravity)
		detectCollision(allObjs);
		//doCollisions(allObjs);
		solve();									// Step 2: apply forces
	}
	
}

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
	case 0:
		ptr = mass;
		type = tpMASS;
		break;
	case 1:
		ptr = &objType;
		type = tpSHAPE;
		break;
	case 2:
		ptr = texture;
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
	case 6:
		ptr = &touchObj;
		type = tpOBJP;
		break;
	case 7:
		ptr = &isTouching3ds;
		type = tpBOOL;
		break;
	case 8:
		//ptr = touchObj3ds;
		//type = tpMASS;
		break;
	case 9:
		ptr = &self;
		type = tpOBJP;
		break;
	case 10:
		ptr = touches;
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

bool Object::detectCollision(const object_holder* objs)
{
	bool detect = false;
	const object_sphere* spherePoint;
	
	for(int sidx = 0; sidx < objs->spheres->numOfMasses; sidx++)
	{
		spherePoint = objs->getSphere(sidx);
		detectCollision(objs->getSphere(sidx));
	}
	return detect;
	
}


//PLANE----------------------------------------



//SPHERE CONTAINER------------------------------
object_spheres::object_spheres() : Objects<object_sphere>()
{
	objType = SPHERE;
	//objs = reinterpret_cast<object_sphere*>(new object_sphere[NUMOBJECTS]);
	objs = new object_sphere[MAXOBJECTS];

}

object_spheres::object_spheres(int numObjs, float mass, float radius) : Objects<object_sphere>(numObjs, mass)
{
	objType = SPHERE;
	//objs = reinterpret_cast<object_sphere*>(new object_sphere[NUMOBJECTS]);
	objs = new object_sphere[MAXOBJECTS];
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
		if(numOfMasses < MAXOBJECTS)
		{
			objs[numOfMasses].self.index = numOfMasses;
			objs[numOfMasses].self.holder = holder;
			objs[numOfMasses].self.shape = objType;
			objs[numOfMasses].mass->m = m;
			objs[numOfMasses].mass->pos.x = basePos.x;
			objs[numOfMasses].mass->pos.y = basePos.y;
			objs[numOfMasses].mass->pos.z = basePos.z;
			objs[numOfMasses++].radius = radius;
		}
	}

	return;
}

void object_spheres::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
	for (int a = 0; a < numOfMasses; ++a)								//we will apply force to all masses (actually we have 1 mass, but we can extend it in the future)
	{
		objs[a].solve();
	}
}


//SINGLE SPHERE----------------------------------------------
object_sphere::object_sphere() : Object()
{
	objType = SPHERE;
	radius = 1;
    /*quad = gluNewQuadric();								// Create A New Quadratic
	gluQuadricNormals(quad, GL_SMOOTH);					// Generate Smooth Normals For The Quad
    gluQuadricTexture(quad, GL_TRUE);						// Enable Texture Coords For The Quad*/
	bMovable = true;
}

object_sphere::object_sphere(float mass, float rad) : Object(mass)
{
	objType = SPHERE;
	radius = rad;
    /*quad = gluNewQuadric();								// Create A New Quadratic
	gluQuadricNormals(quad, GL_SMOOTH);					// Generate Smooth Normals For The Quad
    gluQuadricTexture(quad, GL_TRUE);						// Enable Texture Coords For The Quad*/
	bMovable = true;
}

object_sphere::~object_sphere()
{
//	delete quad;								// Create A New Quadratic
}

void object_sphere::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
	//mass->applyForce(Vector3D(0.0f, gravity, 0.0f) * mass->m);				//gravitational force is as F = m * g. (mass times the gravitational acceleration)
	mass->applyForce(moveForce/mass->m);
	//mass->applyForce(mass->force);
	moveForce = Vector3D(0,0,0);
}

void object_sphere::draw()
{
	int numTexture = texture->numLayers;

	glColor4f(1.0f, 1.0f, 1.0f, .9f);						// Set Color To White
	//glColor3ub(texture->color.x, texture->color.y, texture->color.z);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	
	glPushMatrix();
	glTranslatef(mass->pos.x, mass->pos.y, mass->pos.z);
	
	glPushMatrix();
	//glRotatef(xrot,1.0f,0.0f,0.0f);						// Rotate On The X Axis By xrot
	//glRotatef(yrot,0.0f,1.0f,0.0f);						// Rotate On The Y Axis By yrot
	//glRotatef(zrot,0.0f,0.0f,1.0f);						// Rotate On The Y Axis By yrot
	glBindTexture(GL_TEXTURE_2D, texture->layer[0]);			// Select Texture 2 (1)
	
//	gluSphere(quad, radius, 32, 16);						// Draw First Sphere
	
	glBindTexture(GL_TEXTURE_2D, texture->layer[1]);			// Select Texture 3 (2)
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// Set Color To White With 40% Alpha
	//glColor3ub(texture->color.x, texture->color.y, texture->color.z);
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set Blending Mode To Mix Based On SRC Alpha
	//
	if(numTexture>0)
	{
		glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
		glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping

//		gluSphere(quad, radius, 32, 16);					// Draw Another Sphere Using New Texture
															// Textures Will Mix Creating A MultiTexture Effect (Reflection)
		glDisable(GL_TEXTURE_GEN_S);						// Disable Sphere Mapping
		glDisable(GL_TEXTURE_GEN_T);						// Disable Sphere Mapping
	}
	//

	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glPopMatrix();
	glTranslatef(-mass->pos.x, -mass->pos.y, -mass->pos.z);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);							// Disable 2D Texture Mapping
}

bool object_sphere::detectCollision(const object_sphere* obj2)
{
	bool detect = false;
	
	Vector3D vecToSphere;
	GLfloat dist;
	
	if(!isSame(self, obj2->self))
	{
		vecToSphere = mass->pos - obj2->mass->pos;
		dist = vecToSphere.length();

		if(dist < (radius + obj2->radius))
		{
			detect = true;
			//p.index = sidx;
			//p.shape = SPHERE;
			//p.holder = allobj;
		}
	}
	
	return detect;
}

/*bool object_sphere::doCollisions(const object_holder *allObjs)
{
	bool detect = false;
	objP point;

	detect = detectCollision(this, allObjs, point);

	if(detect)
	{
		isTouching = true;
		if(point.shape == SPHERE)
			collide(this, &allObjs->spheres->objs[point.index]);
		else if(point.shape == PLANE)
			collide(this, &allObjs->planes->objs[point.index]);
	}

	return detect;
}*/

//PLANE CONTAINER---------------------------
object_planes::object_planes() : Objects<object_plane>()
{
	objType = PLANE;
	objs = new object_plane[MAXOBJECTS];
}

object_planes::object_planes(int numObjs, float mass, float wid, float len, float ph, float th) : Objects<object_plane>(numObjs, mass)
{
	objType = PLANE;
	objs = new object_plane[MAXOBJECTS];
	//addObjects(numObjs, mass, wid, len, rot,0,0,0);
}

void object_planes::addObjects(int numMass, float m, float wid, float len, float ph, float th, object_holder* holder, Vector3D basePos, Vector3D offsetDir, float distBetween, Vector3D mAxis)
{
	for(int i=0; i<numMass; i++)
	{
		if(numOfMasses < MAXOBJECTS)
		{
			objs[numOfMasses].self.index = numOfMasses;
			objs[numOfMasses].self.holder = holder;
			objs[numOfMasses].self.shape = objType;
			objs[numOfMasses].mass->m = m;
			objs[numOfMasses].mass->pos.x = basePos.x;
			objs[numOfMasses].mass->pos.y = basePos.y;
			objs[numOfMasses].mass->pos.z = basePos.z;
			objs[numOfMasses].angles.x = ph;
			objs[numOfMasses].angles.y = th;
			objs[numOfMasses].width = wid;
			objs[numOfMasses].length = len;
			objs[numOfMasses++].makeBase(&mAxis);
		}
	}

	return;
}


//SINGLE PLANE----------------------------
object_plane::object_plane() : Object()
{
	objType = PLANE;
	width = length = 1.0f;
	angles = Vector2D(0,0);
	normal = new Vector3D(0,1,0);
	lvec = new Vector3D(1,0,0);
	wvec = new Vector3D(0,0,1);
	moveForce = Vector3D(0,0,0);
}

object_plane::object_plane(float mass, float wid, float len, float phi, float theta, Vector3D mAxis) : Object(mass)
{
	Object();
	object_plane();
	width = wid;
	length = len;
	angles = Vector2D(phi, theta);
	makeBase(&mAxis);
}

void object_plane::draw()
{
	Vector3D v;							//keeps coords of vertex for drawing
	int numTexture = texture->numLayers;
	
	glEnable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	glPushMatrix();
	glTranslatef(mass->pos.x, mass->pos.y, mass->pos.z);

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture->layer[0]);			// Select Texture 1 (0)
	glBegin(GL_QUADS);									// Begin Drawing A Quad
		//glNormal3f(0.0f, 1.0f, 0.0f);						// Normal Pointing Up
		glNormal3f(normal->x, normal->y, normal->z);						// Normal Pointing Up
		glColor3ub(0, 59, 255);
		glTexCoord2f(0.0f, 1.0f);					// Bottom Left Of Texture
		v = (-*wvec*width + *lvec*length)*.5f;
		glVertex3f(v.x, v.y, v.z);					// Bottom Left Corner Of Floor
		
		glTexCoord2f(0.0f, 0.0f);					// Top Left Of Texture
		v = (-*wvec*width - *lvec*length)*.5f;
		glVertex3f(v.x, v.y, v.z);					// Top Left Corner Of Floor
		
		glTexCoord2f(1.0f, 0.0f);					// Top Right Of Texture
		v = (*wvec*width - *lvec*length)*.5f;
		glVertex3f(v.x, v.y, v.z);					// Top Right Corner Of Floor
		
		glTexCoord2f(1.0f, 1.0f);					// Bottom Right Of Texture
		v = (*wvec*width + *lvec*length)*.5f;
		glVertex3f(v.x, v.y, v.z);					// Bottom Right Corner Of Floor
	glEnd();

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
}

void object_plane::makeBase(const Vector3D* mAxis)
{
	if(*mAxis == Z)
	{
		*wvec = X.rotate3D(&Z, angles.x);							//rotate x by phi
		*lvec = (Y.rotate3D(&Y, angles.x)).rotate3D(wvec,angles.y);	//rotate y down by phi then theta
	}
	else if(*mAxis == Y)
	{
		*wvec = Z.rotate3D(&Y, angles.x);
		*lvec = (X.rotate3D(&Y, angles.x)).rotate3D(wvec,angles.y);
	}
	else if(*mAxis == X)
	{
		*wvec = Y.rotate3D(&X, angles.x);
		*lvec = (Z.rotate3D(&Y, angles.x)).rotate3D(wvec,angles.y);
	}
	else
		//msgbox('incorrect major axis');
		;

	*normal = Cross(wvec, lvec);

	return;
}

void object_plane::flipBase()
{
	Vector3D* temp;
	temp = lvec;
	lvec = wvec;
	wvec = temp;

	return;
}
	
/*bool object_plane::doCollisions(const object_holder *allObjs)
{
	bool detect = false;
	objP point;

	detect = detectCollision(this, allObjs, point);
	touching = true;

	if(detect)
	{
		collide(this, allObjs, point);
	}

	return detect;
}*/

bool object_plane::inPlane(const Vector3D *v)
{
	bool in = false;
	Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

	in = (fabs(planeBasisv.x) < .5f*width) && (fabs(planeBasisv.y) < .5f*length);
	return in;
}

bool object_plane::atSurface(const Vector3D *v)
{
	bool atSurf = false;
	Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

	atSurf = (fabs(planeBasisv.z) < EPS);

	return atSurf;
}

bool object_plane::isAbove(const Vector3D *v) const
{
	bool above = false;
	Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

	above = (planeBasisv.z > 0.0f);

	return above;
}

//BOX---------------------------
object_box::object_box() : Object()
{
	width = 0.0f;
	length = 0.0f;
	height = 0.0f;
	rotate = 0.0f;
	
	for(int i=0; i<6; i++)
		touching[i] = false;
}

object_box::object_box(float mass, float wid, float len, float hei, float ph, float th, Vector3D pos, Vector3D mAxis) : Object(mass)
{
	Vector3D currentAxis;
	
	object_box();
	currentAxis = mAxis.rotatePhiTheta(&mAxis, ph, th);
	planes.addObjects(2, mass, wid, len, ph, th, NULL, pos + (currentAxis*.5f*hei) + pos, -currentAxis, hei, mAxis);
}
	

//LINE CONTAINER---------------------------
object_lines::object_lines() : Objects<object_line>()
{
	objType = LINE;
	objs = new object_line[MAXOBJECTS];
}

void object_lines::addObjects(int numMass, float m, Vector3D v1, Vector3D v2, float cmf, object_holder* holder, Vector3D offsetDir, float offsetDist)
{
	for(int i=0; i<numMass; i++)
	{
		if(numOfMasses < MAXOBJECTS)
		{
			objs[numOfMasses].self.index = numOfMasses;
			objs[numOfMasses].self.holder = holder;
			objs[numOfMasses].self.shape = objType;
			objs[numOfMasses].mass->m = m;
			objs[numOfMasses].vertex[0] = v1;
			objs[numOfMasses].vertex[1] = v2;
			objs[numOfMasses++].initGeo();
		}
	}

	return;
}


//SINGLE LINE----------------------------- 
object_line::object_line() : Object()
{
	objType = LINE;
	vertex[0] = Vector3D(0,0,0);
	vertex[1] = Vector3D(1,0,0);
	comf = .5f;
	moveForce = Vector3D(0,0,0);
	bMovable = true;
	initGeo();
}

object_line::object_line(float mass, Vector3D v1, Vector3D v2) : Object(mass)
{
	Object();
	object_line();
	vertex[0] = v1;
	vertex[1] = v2;
	width = 15;
	initGeo();
}

object_line::object_line(float mass, Vector3D v1, Vector3D v2, float cmf) : Object(mass)
{
	Object();
	object_line();
	vertex[0] = v1;
	vertex[1] = v2;
	initGeo();
}

void object_line::initGeo()
{
	lvec = (vertex[1] - vertex[0]).unit();
	length = (vertex[1] - vertex[0]).length();
	normal = Z - Z.proj(&lvec);							//make normal vector starting from Z
	
	mass->pos = vertex[0] + (vertex[1] - vertex[0]) * comf;
	mass->I = mass->m*pow(length,2)/12.0f;
	return;
}

void object_line::calcGeo()
{
	lvec = lvec.rotate3D(&mass->axis, mass->dtheta);
	vertex[0] = mass->pos - (lvec*length*comf);
	vertex[1] = mass->pos + (lvec*length*(1-comf));
	normal = Z - Z.proj(&lvec);							//make normal vector starting from Z

	return;
}

void object_line::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
	mass->applyForce(moveForce/mass->m);
	calcGeo();
	moveForce = Vector3D(0,0,0);
}

void object_line::draw()
{
	calcGeo();
	glLineWidth(4);
	glBegin(GL_LINES);								//horizontal line
		glNormal3f(normal.x, normal.y, normal.z);	//normal vector to line points up
		glColor3ub(255, 255, 255);					// Set Color To White
		glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
		glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
	glEnd();
	
	return;
}

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

void* object_line::getProperty(int idx, dataType &type)
{
	void* ptr = NULL;

	if((0 <= idx) && (idx <14))
		Object::getProperty(idx, type);
	else
	{
		switch(idx)
		{
		case 14:
			ptr = &vertex[0];
			type = tpVECTOR3D;
			break;
		/*case 15:
			ptr = &vertex[1];
			type = tpSHAPE;
			break;
		case 16:
			ptr = texture;
			type = tpTEXTURE;
			break;
		case 17:
			ptr = &movable;
			type = tpBOOL;
			break;
		case 18:
			ptr = &moveForce;
			type = tpVECTOR3D;
			break;
		case 19:
			ptr = &isTouching;
			type = tpBOOL;
			break;
		case 6:
			ptr = &touchObj;
			type = tpOBJP;
			break;
		case 7:
			ptr = &isTouching3ds;
			type = tpBOOL;
			break;
		case 8:
			//ptr = touchObj3ds;
			//type = tpMASS;
			break;
		case 9:
			ptr = &self;
			type = tpOBJP;
			break;
		case 10:
			ptr = touches;
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
			break;*/
		default:
			break;
		}
	}

	return ptr;
}


Vector3D object_line::calcVertexVel(int vnum)
{
	Vector3D linVel, rotVel, velDir, velOut;
	GLfloat armLength;		//distance from com to vertex

	linVel = mass->vel;
	switch(vnum)
	{
		case 0:
			armLength = comf*length;
			velDir = Cross(mass->axis,vertex[0]-vertex[1]);
			velDir.unitize();
			rotVel = velDir*armLength*mass->avel;
			break;
		case 1:
			armLength = (1.0f-comf)*length;
			velDir = Cross(mass->axis, vertex[1]-vertex[0]);
			velDir.unitize();
			rotVel = velDir*armLength*mass->avel;
			break;
		default:
			break;
	}
	velOut = linVel + rotVel;

	return velOut;
}

//OBJECT HOLDER----------------------------------------------
object_holder::object_holder()
{
	numObjects = 0;
	majorAxis = Z;
	spheres = new object_spheres;
	planes = new object_planes;
	lines = new object_lines;
	tree = new pointerTree;
}

object_holder::~object_holder()
{
	delete spheres;
	delete planes;
	delete lines;
	delete tree;
}

object_sphere* object_holder::addSpheres(int numObjs, float mass, float radius, Vector3D basePos, Vector3D offsetDir)
{
	object_sphere* sphereout = NULL;

	spheres->addObjects(numObjs, mass, radius, this, basePos, offsetDir);
	sphereout = &spheres->objs[numObjects];
	numObjects += numObjs;
	
	return sphereout;
}

object_sphere* object_holder::addSpheres(float mass, float radius, Vector3D basePos)
{
	object_sphere* sphereout = NULL;

	spheres->addObjects(1, mass, radius, this, basePos, Vector3D(0,0,0));
	sphereout = &spheres->objs[numObjects];
	numObjects++;
	
	return sphereout;
}

object_plane* object_holder::addPlanes(int numObjs, float mass, float wid, float len, float ph, float th, Vector3D basePos, Vector3D offDir, float distBetween)
{
	object_plane* planeout = NULL;
	
	planes->addObjects(numObjs, mass, wid, len, ph, th, this, basePos, offDir, distBetween, majorAxis);
	numObjects += numObjs;

	return planeout;
}

object_plane* object_holder::addPlanes(float mass, float wid, float len, float ph, float th, Vector3D basePos)
{
	object_plane* planeout = NULL;
	
	planes->addObjects(1, mass, wid, len, ph, th, this, basePos, Vector3D(0,0,0), 0, majorAxis);
	numObjects++;

	return planeout;
}

object_line* object_holder::addLines(int numObjs, float mass, Vector3D v1, Vector3D v2, float cmf, Vector3D offsetDir, float offsetDist)
{
	object_line* lineout = NULL;
	
	lines->addObjects(numObjs, mass, v1, v2, cmf, this, offsetDir, offsetDist);
	numObjects += numObjs;

	return lineout;
}

void object_holder::run(GLfloat dt)
{
	spheres->operate(this);
	lines->operate(this);
	planes->operate(this);
	
	spheres->simulate(dt);								// Step 3: iterate the masses by the change in time
	lines->simulate(dt);
	planes->simulate(dt);

	return;
}

void object_holder::draw()
{
	spheres->draw();
	planes->draw();
	lines->draw();
	return;
}

void object_holder::setMass(Shape objType, int index, float mass)
{
	if(objType == SPHERE)
		spheres->objs[index].mass->m = mass;
	else if(objType == PLANE)
		planes->objs[index].mass->m = mass;

	return;
}

void object_holder::setElas(Shape objType, int index, float el)
{
	if(objType == SPHERE)
		spheres->objs[index].mass->elas = el;
	else if(objType == PLANE)
		planes->objs[index].mass->elas = el;

	return;
}

void object_holder::setPos(Shape objType, int index, Vector3D pos)
{
	if(objType == SPHERE)
		spheres->objs[index].mass->pos = pos;
	else if(objType == PLANE)
		planes->objs[index].mass->pos = pos;

	return;
}

void object_holder::setNormal(Shape objType, int index, Vector3D norm)
{
	if(objType == PLANE)
	{
		*planes->objs[index].normal = norm.unit();
		planes->objs[index].makeBase(&majorAxis);
	}	

	return;
}

void object_holder::flipBase(Shape objType, int index)
{
	if(objType == PLANE)
	{
		planes->objs[index].flipBase();
	}

	return;
}


void object_holder::setTexture(Shape objType, int index, texture_s* txr)
{
	if(objType == SPHERE)
		spheres->objs[index].texture = txr;
	else if(objType == PLANE)
		planes->objs[index].texture = txr;

	return;
}

void object_holder::setColor(Shape objType, int index, Vector3D color)
{
	if(objType == SPHERE)
		spheres->objs[index].texture->color = color;
	else if(objType == PLANE)
		planes->objs[index].texture->color = color;

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

	for(int s = 0; s<spheres->numOfMasses; s++)
	{
		sprintf(numtext, "%i", s+1);
		tree->addLeaf(&spheres->objs[s], tpOBJECT, sphere + numtext);
	}
	for(int p = 0; p<planes->numOfMasses; p++)
	{
		sprintf(numtext, "%i", p+1);
		tree->addLeaf(&planes->objs[p], tpOBJECT, plane + numtext);
	}
	for(int l = 0; l<lines->numOfMasses; l++)
	{
		sprintf(numtext, "%i", l+1);
		tree->addLeaf(&lines->objs[l], tpOBJECT, line + numtext);
	}

	return tree;
}

object_sphere* object_holder::getSphere(int index) const
{
	return &spheres->objs[index];
}

object_plane* object_holder::getPlane(int index)
{
	return &planes->objs[index];
}

//FUNCTION DEFINITIONS
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
