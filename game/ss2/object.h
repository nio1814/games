#ifndef OBJECT_H
#define OBJECT_H

#include "mass.h"
#include "vector2d.h"
#include "characters.h"

#include <memory>
#include <map>

class Sprite;

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
	void scaleToSpriteSize();

	float directionFloat();
	void moveLeft();
	void moveRight();
	void noLeftRightMove();
	void jump();

	void checkTouch(std::shared_ptr<Object> otherObject);
	bool touching(Side side);
	void update(float timeElapsed);
	void reset();
	void setSprite(const Sprite &sprite);
private:
	float diagonalLength() const;
	void resetTouches();

	Vector2D m_size;
	float m_rotation;
	bool m_facingRight;
	float m_speed = 1;
	float m_jumpStrength = 5;
	std::map<Side,bool> m_touching;
	std::unique_ptr<Sprite> m_sprite;
	Action m_action;
	bool m_mobile = false;
};

#endif // OBJECT_H
