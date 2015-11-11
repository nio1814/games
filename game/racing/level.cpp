#include "level.h"

#include "meshobject.h"
#include "model3d.h"
#include "mass.h"
#include "light.h"

Level::Level()
{
	player = new MeshObject;

}

Level::~Level()
{
	delete player;

}


void Level::initObject(MeshObject *obj)
{
	obj->mass->axis.z = 1.0f;
	//obj->mesh->centerMesh();
	obj->mass->pos = obj->mesh->center;

	return;
}

void Level::addPlayer(const char* modelfile)
{
	player->mesh = new MeshModel;
	player->isDynamicMesh = true;
	player->mesh->loadFile(modelfile);
	initObject(player);

	return;
}

void Level::addLight(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec)
{
	return;
}
