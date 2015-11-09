#ifndef MASS
#define MASS
/**************************************************************************

  File: mass.h  

  Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/

#include <math.h>
#include "vector3d.h"

extern bool gravityON;
extern float gravityMag;
extern Vector3D gravityVec;

// class Mass			---> An object to represent a mass
class Mass
{
public:
    Mass(const Mass& mass);
    Mass& operator = (const Mass& mass);

	float m;									// The mass value
	float elas;
	Vector3D dir;								// direction of mass
	Vector3D pos, posnew, dpos;						// Position in space
	Vector3D vel, velnew;						// Velocity
	Vector3D force, forcenew;					// Force applied on this mass at an instance
	float I;									//momment of inertia
	float theta, dtheta;						//angle of mass
	float avel, avelnew;						//angular velocity
	float torque, torquenew;
	Vector3D axis;								//axis of rotation

	Mass(float m);								// Constructor

	/*
	  void applyForce(Vector3D force) method is used to add external force to the mass. 
	  At an instance in time, several sources of force might affect the mass. The vector sum 
	  of these forces make up the net force applied to the mass at the instance.
	*/
	void applyForce(Vector3D force);
	
	void applyTorque(float torque);
	
	//void init() method sets the force values to zero
	void init();

	/*
	  void simulate(float dt) method calculates the new velocity and new position of 
	  the mass according to change in time (dt). Here, a simulation method called
	  "The Euler Method" is used. The Euler Method is not always accurate, but it is 
	  simple. It is suitable for most of physical simulations that we know in common 
	  computer and video games.
	*/
	void simulate(float dt);	
};

#endif
