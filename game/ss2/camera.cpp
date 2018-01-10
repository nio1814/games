#include "camera.h"

Camera::Camera(Vector3D position, Vector3D look, const Vector3D up, float distance) :
	m_position(position),
	m_look(look),
	m_up(up),
	m_distance(distance)
{

}

Vector3D &Camera::position()
{
	return m_position;
}

Vector3D &Camera::look()
{
	return m_look;
}

Vector3D& Camera::up()
{
	return m_up;
}

void Camera::setMode(Camera::Mode mode)
{
	m_mode = mode;
}

void Camera::setFollowPosition(std::shared_ptr<Vector3D> followPosition)
{
	m_positionFollow = followPosition;
}

void Camera::setLookToPosition(Vector3D lookToPosition)
{
	m_lookToPosition = std::make_shared<Vector3D>(lookToPosition);
}

void Camera::update(float timeElapsed)
{
	switch(m_mode)
	{
		case Follow:
			if(m_positionFollow)
			{
				Vector3D toDestination = *m_positionFollow - m_position;
				m_position += toDestination*.1;
				if(m_lookToPosition)
				{
					Vector3D toLook = (m_position-*m_lookToPosition) - m_look;
					m_look += toLook*.2;
				}
			}
			break;
		case Fixed:
			break;
	}
}
