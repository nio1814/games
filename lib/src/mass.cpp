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
float gravityMag = 9.81;
//extern float gravityMag = 0;
Vector3D gravityVec = Y*-9.81;

Mass::Mass(float m)								// Constructor
{
	this->m = m;
  elasticity = DEFAULTELASTICITY;
	dir.y = 1.0f;
	I = DEFAULTINERTIA;
	theta = dtheta = 0.0f;
	avel = avelnew = 0.0f;
	torque = torquenew = 0.0f;
}

Mass::Mass(const Mass &mass)
{
  *this = mass;
}

Mass::Mass(const Vector3D &position, const float mass) :
  m(mass),
  pos(position)
{

}

Mass& Mass::operator= (const Mass& mass)
{
    m = mass.m;
    elasticity = mass.elasticity;
    dir = mass.dir;								// direction of mass
    pos = mass.pos;
    posnew = mass.posnew;
    dpos = mass.dpos;
    vel = mass.vel;
    velnew = mass.velnew;						// Velocity
    force = mass.force;
    forcenew = mass.forcenew;					// Force applied on this mass at an instance
    I = mass.I;									//momment of inertia
    theta = mass.theta;
    dtheta = mass.dtheta;						//angle of mass
    avel = mass.avel;
    avelnew = mass.avelnew;						//angular velocity
    torque = mass.torque;
    torquenew = mass.torquenew;

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
	avelnew = avel;
	dtheta = 0;
}


void Mass::simulate(float dt)
{
	force = forcenew;
	vel = velnew;

	vel += (force / m) * dt;				// Change in velocity is added to the velocity.
											// The change is proportinal with the acceleration (force / m) and change in time
	dpos = vel * dt;
	pos += dpos;						// Change in position is added to the position.
											// Change in position is velocity times the change in time
	
	torque = torquenew;						//update torque to sum of torques at instance
	avel = avelnew;

	avel += (torque / I) * dt;				// Change in velocity is added to the velocity.
											// The change is proportinal with the acceleration (force / m) and change in time

	dtheta += avel * dt * RAD2DEG;
	theta += dtheta;			// Change in angle is added to the position.
	theta = fmod(theta, 360.0f);
	dir = dir.rotate3D(axis, dtheta);

  this->forcenew = {0, 0, 0};
  velnew = vel;
}

