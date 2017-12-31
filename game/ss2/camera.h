#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"

class Camera
{
public:
	Camera(Vector3D position={0,0,1}, Vector3D look={0,0,0}, const Vector3D up={0,1,0}, float distance=1.0f);

	Vector3D& position();
	Vector3D& look();
	Vector3D& up();
private:
	Vector3D m_position;
	Vector3D m_look;
	Vector3D m_up;
	float m_distance;
};

#endif // CAMERA_H
