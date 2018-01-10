#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"

#include <memory>

class Camera
{
public:
	enum Mode{Fixed, Follow};
	Camera(Vector3D position={0,0,1}, Vector3D look={0,0,0}, const Vector3D up={0,1,0}, float distance=1.0f);

	Vector3D& position();
	Vector3D& look();
	Vector3D& up();

	void setMode(Mode mode);
	void setFollowPosition(std::shared_ptr<Vector3D>   followPosition);
	void setLookToPosition(Vector3D lookToPosition);
	void update(float timeElapsed);
private:
	Vector3D m_position;
	Vector3D m_look;
	Vector3D m_up;
	float m_distance;
	std::shared_ptr<Vector3D> m_positionFollow;
	std::shared_ptr<Vector3D> m_lookToPosition;
	Mode m_mode = Fixed;
};

#endif // CAMERA_H
