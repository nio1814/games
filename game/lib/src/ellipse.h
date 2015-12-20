#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "object_2.h"
#include "objects.h"

class Ellipse : public Object
{
public:
	Ellipse(float radius=1);
	void draw(QOpenGLShaderProgram* program);
private:
	float m_radius;
};

//template class Objects<class Ellipse>;
typedef Objects<class Ellipse> Ellipses;
//Objects<Ellipse>* test;

#endif // ELLIPSE_H
