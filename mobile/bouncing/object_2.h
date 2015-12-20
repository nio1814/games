#ifndef OBJECT
#define OBJECT

#include <qvector.h>

class Mass;
class QOpenGLShaderProgram;

enum Shape{PLANE, SPHERE, LINE, BOX, TRI, ELLIPSE};

class Object
{
public:
	virtual void draw(QOpenGLShaderProgram* program) {}
	bool doDraw();
protected:
	Mass* m_mass;
private:
	Shape objType; 
	bool m_draw;
};

#endif

