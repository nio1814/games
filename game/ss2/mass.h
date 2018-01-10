#ifndef MASS_H
#define MASS_H

#include "vector3d.h"

class Mass
{
public:
	Mass(Vector3D position=Vector3D());
	~Mass();

	void setVelocity(float velocityX, float velocityY);
	virtual void update(float timeElapsed);
	Vector3D position() const;
	void setHasGravity(bool status);
	Vector3D velocity();
protected:
	Vector3D m_position;
	Vector3D m_velocity;
	bool m_hasGravity = false;
	float m_gravity = -9.8;
private:
	float m_mass;
};

#endif // MASS_H
