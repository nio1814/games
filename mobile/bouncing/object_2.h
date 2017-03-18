#ifndef OBJECT_H
#define OBJECT_H

#include <qvector.h>

class Mass;
class QOpenGLShaderProgram;

enum Shape{PLANE, SPHERE, LINE, BOX, TRI, ELLIPSE};

class Object
{
public:
	Object();
	virtual void draw(QOpenGLShaderProgram* program) {}
	bool doDraw();
protected:
	Mass* m_mass;
private:
	Shape objType; 
	bool m_draw;
};

#endif

