#include "level.h"

#include "meshobject.h"
#include "model3d.h"
#include "mass.h"
#include "light.h"
#include "keys.h"
#include "camera.h"

float DT_INC = 0.03f;
float MAX_DT = 0.1f;

float ACCELRATE = 10.0f;
float DECELRATE = 15.0f;
float TURNRAD = 160.0f;
float TURNRATE = 1.0f;
float CAMMOVERATE = .80f;
float DRAGCONST = 0.001f;

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

void Level::run(GLfloat dt)
{
	int o;

	for(o=0; o<objs.size(); o++)
	{
		contactPoints[o].touch = player->bbox->detectCollisionM(objs[o]->bbox, &contactPoints[o].point, &contactPoints[o].norm);
		if(contactPoints[o].touch)
		{
			doCollision(player, objs[o], contactPoints[o].point, contactPoints[o].norm);
			doCollision(objs[o], player, contactPoints[o].point, -contactPoints[o].norm);
		}
	}
	updateObjects(dt);
	updateCamera(dt);

	return;
}

void Level::updateObjects(GLfloat dt)
{
	int numIts;
	Vector3D dragForce;
	GLfloat aFrictionTorque;

	player->init();

	//Apply friction
	//if(fabs(player->mass->vel.length()) > 1e-3)
	//	player->mass->applyForce(-player->moveDir*0.1f);

	//Turn left
	if(isKeys(Qt::Key_Left))
	{
		//player->mass->avelnew = player->mass->vel.length()/TURNRAD;
		//player->mass->applyForce(player->mass->dir.rotate3D(&player->mass->axis,90)*pow(player->mass->vel.length(),2)/TURNRAD);
		player->mass->dtheta += TURNRATE;
		player->mass->velnew = player->mass->velnew.rotate3D(player->mass->axis, TURNRATE);
	}

	//Turn right
	if(isKeys(Qt::Key_Right))
	{
		//player->mass->avelnew = -player->mass->vel.length()/TURNRAD;
		//player->mass->applyForce(player->mass->dir.rotate3D(&player->mass->axis,-90)*pow(player->mass->vel.length(),2)/TURNRAD);
		player->mass->dtheta -= TURNRATE;
		player->mass->velnew = player->mass->velnew.rotate3D(player->mass->axis, -TURNRATE);
	}

	//Accelerate
	if(isKeys(Qt::Key_Up))
	{
		/*if(isKeys(controls[0][btnLEFT]))
			player->mass->applyForce(player->mass->dir.rotate3D(&player->mass->axis,10)*ACCELRATE);
		else*/
			player->mass->applyForce(player->mass->dir*ACCELRATE);
	}

	//Brake
	if(isKeys(Qt::Key_Down))
		player->mass->applyForce(-player->mass->dir*DECELRATE);

	//player->mass->velnew = player->mass->vel.proj(&player->mass->dir);
	dragForce = -player->mass->vel.unit()*pow(player->mass->vel.length(),2)*DRAGCONST;
	player->mass->applyForce(dragForce);
	if(fabs(player->mass->avel)>1e-3)
	{
		aFrictionTorque = -5*player->mass->avel/fabs(player->mass->avel);
		player->mass->applyTorque(aFrictionTorque);
	}

	numIts = dt/DT_INC + 1;
	numIts = 1;
	int numIts2 = dt/MAX_DT + 1;
	for(int i=0; i<numIts; i++)
	{
		player->simulate(dt);
		player->updateBoundingBox();
		for(int o=0; o<objs.size(); o++)
		{
			if(objs[o]->isMoveable)
			{
				objs[o]->init();
				objs[o]->simulate(dt);
				if(objs[o]->hasBBox)
					objs[o]->updateBoundingBox();
			}
		}
	}

	return;
}

void Level::updateCamera(GLfloat dt)
{
	GLfloat followDist = 20.0f;
	GLfloat followHeight = 10.0f;
	Vector3D targetPos;
	Vector3D moveDir;
	Vector3D toCam;
	
	switch(camview)
	{
		case FOLLOW:
			moveDir = player->mass->dir;
			moveDir.z = 0;
			cam.look = player->mass->pos;

			toCam = -moveDir*followDist + cam.up*followHeight;
			toCam.unitize();
			toCam = toCam*followDist;

			targetPos = cam.look + toCam;
			cam.pos += (targetPos - cam.pos)*qMin(dt,1.0f)*CAMMOVERATE;
			break;
		case LOCKED:
			cam.look = player->mass->pos;
			break;
		case FIRST:
			cam.pos = player->mass->pos + Z+X;
			cam.look = cam.pos + player->mass->dir;
	}

	return;
}
