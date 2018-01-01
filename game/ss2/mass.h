#ifndef MASS_H
#define MASS_H

#include "vector3d.h"

class Mass
{
public:
	Mass(Vector3D position=Vector3D());
	~Mass();

	void setVelocity(float velocityX, float velocityY);
	void update(float timeElapsed);
	Vector3D position();
	void setHasGravity(bool status);
protected:
	Vector3D m_position;
private:
	float m_mass;
	Vector3D m_velocity;
	bool m_hasGravity = false;
};

#endif // MASS_H
