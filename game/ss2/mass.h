#ifndef MASS_H
#define MASS_H

#include "vector3d.h"

class Mass
{
public:
	Mass();
	~Mass();

	void setVelocity(float velocityX, float velocityY);
	void update(float timeElapsed);
protected:
	Vector3D m_position;
private:
	float m_mass;
	Vector3D m_velocity;
};

#endif // MASS_H
