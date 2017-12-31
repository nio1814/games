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
