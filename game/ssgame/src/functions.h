#ifndef FUNCTIONS
#define FUNCTIONS

#include "objects.h"

extern bool done;

GLfloat Max(GLfloat num1, GLfloat num2);
GLfloat Min(GLfloat num1, GLfloat num2);

GLfloat dist(const object_c *obj1, const object_c *obj2);
GLfloat dist(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

int mod(int num, int N);

#endif
