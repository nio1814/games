#include "light.h"

light_c::light_c()
{
	enabled = false;
	lightNum = (GLenum)0;
}

light_c::light_c(GLenum lnum)
{
	light_c();
	
	lightNum = lnum;
}

light_c::light_c(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec)
{
	light_c();
	
	pos = ptn;
	ambient = amb;
	diffuse = dif;
	specular = spec;
	lightNum = lnum;
}

bool light_c::enable()
{
	bool success = false;	//need to figure out a way to see if success
	GLfloat posA[] = {pos.x,pos.y,pos.z,1.0f};
	GLfloat ambA[] = {ambient.x,ambient.y,ambient.z,1.0f};
	GLfloat difA[] = {diffuse.x,diffuse.y,diffuse.z,1.0f};
	GLfloat specA[] = {specular.x,specular.y,specular.z,1.0f};
	
	glEnable(lightNum);
	enabled = true;

	glLightfv(lightNum, GL_POSITION, posA);
	glLightfv(lightNum, GL_AMBIENT, ambA);
	glLightfv(lightNum, GL_DIFFUSE, difA);
	glLightfv(lightNum, GL_SPECULAR, specA);
	
	return success;
}
