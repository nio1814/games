#ifndef LEVEL_H
#define LEVEL_H

#include "light.h"

class MeshObject;

class Level
{
public:
	Level();
	~Level();
		void addPlayer(const char* modelfile);
		void initObject(MeshObject* obj);
	void addLight(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec);

		MeshObject* player;
};

#endif // LEVEL_H
