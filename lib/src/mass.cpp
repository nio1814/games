/**************************************************************************

File: mass.h  

Prepared by Erkin Tunca for nehe.gamedev.net

**************************************************************************/

#include <math.h>

#include "constants.h"
#include "mass.h"
#include "vector3d.h"

const float DEFAULTELASTICITY = .95f;
const float DEFAULTINERTIA = 1;

bool gravityON = false;
float gravityMag = 9.81f;
//extern float gravityMag = 0;
Vector3D gravityVec = Y*-9.81f;

Mass::Mass(float m)								// Constructor
{
	this->mass = m;
  elasticity = DEFAULTELASTICITY;
	dir.y = 1.0f;
	momentOfInertia = DEFAULTINERTIA;
	theta = dtheta = 0.0f;
	angularVelocity = angularVelocityNext = 0.0f;
	torque = torquenew = 0.0f;
}

Mass::Mass(const Mass &mass)
{
  *this = mass;
}

Mass::Mass(const Vector3D &position, const float mass) :
  mass(mass),
  pos(position)
{

}

Mass& Mass::operator= (const Mass& from)
{
    mass = from.mass;
    elasticity = from.elasticity;
    dir = from.dir;								// direction of mass
    pos = from.pos;
    posnew = from.posnew;
    dpos = from.dpos;
    vel = from.vel;
    velnew = from.velnew;						// Velocity
    force = from.force;
    forcenew = from.forcenew;					// Force applied on this mass at an instance
    momentOfInertia = from.momentOfInertia;									//momment of inertia
    theta = from.theta;
    dtheta = from.dtheta;						//angle of mass
    angularVelocity = from.angularVelocity;
    angularVelocityNext = from.angularVelocityNext;						//angular velocity
    torque = from.torque;
    torquenew = from.torquenew;

    return *this;
}

void Mass::applyForce(Vector3D force)
{
	this->forcenew += force;					// The external force is added to the force of the mass
}

void Mass::applyTorque(float torque)
{
	this->torquenew += torque;					// The external force is added to the force of the mass
}

void Mass::init()
{
	force = Vector3D(0,0,0);
	forcenew = force;
	velnew = vel;
	
	torque = 0.0f;
	torquenew = torque;
	angularVelocityNext = angularVelocity;
	dtheta = 0;
}


void Mass::simulate(float dt)
{
	force = forcenew;
	vel = velnew;

	vel += (force / mass) * dt;				// Change in velocity is added to the velocity.
											// The change is proportinal with the acceleration (force / m) and change in time
	dpos = vel * dt;
	pos += dpos;						// Change in position is added to the position.
											// Change in position is velocity times the change in time
	
	torque = torquenew;						//update torque to sum of torques at instance
	angularVelocity = angularVelocityNext;

	angularVelocity += (torque / momentOfInertia) * dt;				// Change in velocity is added to the velocity.
											// The change is proportinal with the acceleration (force / m) and change in time

	dtheta += angularVelocity * dt * RAD2DEG;
	theta += dtheta;			// Change in angle is added to the position.
	theta = fmod(theta, 360.0f);
	dir = dir.rotate3D(axis, dtheta);

  this->forcenew = {0, 0, 0};

  velnew = vel;
}

