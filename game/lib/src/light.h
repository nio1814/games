#ifndef LIGHT
#define LIGHT

#include <windows.h>									// Header File For Windows
#include <gl\gl.h>										// Header File For The OpenGL32 Library

#include "vector3d.h"

class light_c
{
public:
	Vector3D pos;
	Vector3D ambient;
	Vector3D diffuse;
	Vector3D specular;
	bool enabled;
	GLenum lightNum;
	
	light_c();
	light_c(GLenum lnum);
	light_c(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec);
	
	bool enable();
	bool disable();
};
	

#endif