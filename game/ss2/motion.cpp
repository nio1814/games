#include "motion.h"

//#include <chrono>
#include <QDateTime>
#include <QDebug>

Motion::Motion(Vector2D positionInitial) :
	m_positionInitial(positionInitial)
{

}

Motion::Motion(const Motion &motion)
{
	*this = motion;
}

void Motion::setInitialPosition(Vector2D p)
{
	m_positionInitial = p;
}

void Motion::addCycle(float period, float range, Vector2D direction, float offset)
{
	m_cycles.push_back({period,offset,range,direction});
}

Vector2D Motion::position()
{
//	float time = std::chrono::duration_cast<std::chrono::duration<float> >(std::chrono::system_clock::now().time_since_epoch()).count();
//	float seconds = milliseconds*1e-3;
	double time = QDateTime::currentMSecsSinceEpoch()*1e-3;

	Vector2D p = m_positionInitial;
	for(Cycle cycle : m_cycles)
		p += cycle.direction*.5*cycle.range*std::cos(2*M_PI*time/cycle.period + cycle.offset);

	return p;
}

Vector2D Motion::velocity()
{
	double time = QDateTime::currentMSecsSinceEpoch()*1e-3;

	Vector2D v = Vector2D(0,0);
	for(Cycle cycle : m_cycles)
		v += cycle.direction*(cycle.range*M_PI/cycle.period)*std::cos(2*M_PI*time/cycle.period + cycle.offset);

	return v;
}

