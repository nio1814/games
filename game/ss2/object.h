#ifndef OBJECT_H
#define OBJECT_H

#include "mass.h"

#include <memory>

class Object : public Mass
{
public:
	Object(float width, float height, float positionX, float positionY);
	~Object();

	void draw();
	Vector2D minPosition();
	Vector2D maxPosition();
	float directionFloat();
private:
	Vector2D m_size;
	float m_rotation;
	bool m_facingRight;
	float m_speed;
};

#endif // OBJECT_H
