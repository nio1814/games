#ifndef LIGHT
#define LIGHT

#include "qtgl.h"
#include "vector3d.h"

class Light
{
public:
	Vector3D pos;
	Vector3D ambient;
	Vector3D diffuse;
	Vector3D specular;
	bool enabled;
	GLenum lightNum;
	
        Light();
        Light(GLenum lnum);
        Light(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec);
	
	bool enable();
	bool disable();
};
	

#endif
