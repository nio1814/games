#ifndef MOTION_H
#define MOTION_H

#include "vector2d.h"

#include <vector>

class Motion
{
	struct Cycle{
		float period;
		float offset;
		float range;
		Vector2D direction;
	};

public:
	Motion(Vector2D positionInitial=Vector2D(0,0));
	Motion(const Motion& motion);

	void setInitialPosition(Vector2D p);
	void addCycle(float period, float range, Vector2D direction, float offset=0);

	Vector2D position();
	Vector2D velocity();
private:
	Vector2D m_positionInitial;
	std::vector<Cycle> m_cycles;
};

#endif // MOTION_H
