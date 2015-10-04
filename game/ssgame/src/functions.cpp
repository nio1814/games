#include<qglobal.h>

#ifdef Q_OS_WIN32
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>
#elif defined(Q_OS_LINUX)
#include <GL/gl.h>
#endif

#include <math.h>

#include "functions.h"

bool done=false;

GLfloat Max(GLfloat num1, GLfloat num2)
{
	GLfloat m;

	if(num1 > num2)
		m = num1;
	else
		m = num2;

	return m;
}

GLfloat Min(GLfloat num1, GLfloat num2)
{
	GLfloat m;

	if(num1 > num2)
		m = num2;
	else
		m = num1;

	return m;
}


GLfloat dist(const Object *obj1, const Object *obj2)
{
	GLfloat distance = static_cast<GLfloat>(sqrt((obj1->pos.x - obj2->pos.x)*(obj1->pos.x - obj2->pos.x) + (obj1->pos.y - obj2->pos.y)*(obj1->pos.y - obj2->pos.y)));

	return distance;
}


GLfloat dist(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	GLfloat distance = static_cast<GLfloat>(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));

	return distance;
}


int mod(int num, int N)
{
	int out;
	out = num % N;
	while(out<0)
		out+=N;

	return out;
}
