#ifndef OBJECT_H
#define OBJECT_H

#include "mass.h"
#include "vector2d.h"

#include <memory>
#include <map>

class Object : public Mass
{
public:
	enum Side{LeftSide, BottomSide, RightSide, TopSide};
	Object(float width, float height, float positionX, float positionY);
	~Object();

	void draw();
	Vector2D minPosition();
	Vector2D maxPosition();
	Vector2D size();
	float directionFloat();
	void checkTouch(std::shared_ptr<Object> otherObject);
	void update(float timeElapsed);
private:
	float diagonalLength() const;
	void resetTouches();

	Vector2D m_size;
	float m_rotation;
	bool m_facingRight;
	float m_speed;
	std::map<Side,bool> m_touching;
};

#endif // OBJECT_H
