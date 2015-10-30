#include "gameobject.h"

#include <math.h>
#include <string.h>

#include <QTime>

#include <keys.h>
#include <3dsGT/3ds.h>
#include <3dsGT/3dsLoader.h>
#include <mouse.h>
#include <constants.h>
#include "texture.h"
#include "masking.h"

//#include "commands.h"

level::level()
{
	started = false;
	numPlayers = 0;
	majAxis = Vector3D(0,0,1);
	bGravity = false;
	gravityM = 9.81;
	gravityV = majAxis*gravityM;
	//numTextures = 0;

    cameras = new CameraPoints;
	lights = NULL;
	//alltexture = new texture_s[MAXTEXTURES];
	//player1 = player2 = NULL;

}


level::level(int players)
{
	level();
	numPlayers = players;
}


void level::setMajAxis(Vector3D axis)
{
	majAxis = axis;
	allObj.majorAxis = axis;
	
	return;
}

void level::create(int index)
{
	int numExtraSpheres = rand()%15;

	switch(index)
	{
		case 0:
			allObj.addSpheres(2.0f, .55f,   Vector3D(-1.0f,1.5f,0.0f));
			allObj.addSpheres(1.0f, .35f,   Vector3D(1, 2, 1.5));

			for(int i=0; i<numExtraSpheres; i++)
			{
				allObj.addSpheres(fabs(.70f*cos((float)rand())), fabs(.50f*cos((float)rand()))+.1f,  Vector3D(3*cos((float)rand()), 4*fabs(cos((float)rand())), 3*cos((float)rand())));
				allObj.setColor(SPHERE, i, Vector3D(rand()%256, rand()%256, rand()%256) );
			}

			ball = &allObj.spheres->objs[1];
			//level1.player1 = ball;
			//ball->texture = balltxr;

			allObj.addPlanes(1,1,8,8,0,  Vector3D(0,0,0));
			allObj.setNormal(PLANE, 0, Vector3D(0,1,0));
//			allObj.setTexture(PLANE, 0, tile1txr);

			allObj.addPlanes(3,1,8,2,0,  Vector3D(-4,1,0));
			allObj.setNormal(PLANE, 1, Vector3D(1,0,0));

			cameras->addPoint(Vector3D(0, 4.6, 8), Vector3D(0, 0, 0), X, 10.0f);
			//level1.allObj.cameras->addPoint(Vector3D(xCam, 3.60f, -14.6f), Vector3D(-11.8f, -3.0f, -13.8f), 5.0f);
			cameras->addPoint(Vector3D(0, 3.60f, 0), Vector3D(0, 3.0f, -13.8f), Y, 10.0f);

			break;
		case 1:
//			game.addLevel("data/model/myschool3.3ds",Vector3D(5,5,2),Vector3D(-5,0,3), Vector3D(0,0,1),FIRST);
//			loadmap(1.5f);
			majAxis = Z;
			break;
		case 2:
//			game.addLevel("data/model/map1.3ds", Vector3D(5,5,2),Vector3D(-5,0,3), Vector3D(0,0,1),FIRST);
//			loadmap(1.0f);
			majAxis = Z;
			break;
	}

	return;
}

void level::run(GLfloat dt)
{
	return;
}


/*Vector3D level::setCam(Object* obj, CameraView view)
{
    cameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
	cameraPoint* nextcam;
	Vector3D cam2cam, cam2obj, cam2look;
	Vector3D pos, look, alongv, movepos;
	Vector3D objpos;
	GLfloat camdist, objvel, camRotate;

	camRotate = 0;

	if(cameras->currentPoint == cameras->numPoints-1)
	{
		nextcam = cam;
	}
	else
		nextcam = &cameras->cpoints[cameras->currentPoint+1];

	objpos = obj->mass->pos;
	objvel = obj->mass->vel.length();
	cam2obj = obj->mass->pos - cam->pos;

	/*cam2cam = nextcam->pos - cam->pos;
	camdist = cam2cam.length();
	alongv = cam2obj.proj(&cam2cam)*.1f;
	cam->movepos = cam->pos + alongv;*/
/*	if(view == FOLLOW)
	{
		if(obj->moveForce == Vector3D(0,0,0))
		{
			movepos = objpos - cam2obj.unit()*cam->followDist;
		}
		else
		{
			movepos = objpos - (obj->moveForce.unit()*cam->followDist + cam2obj.unit()*cam->followDist)/2;
		}
		cam->pos += (movepos - cam->pos)*.2f*delta*objvel;
		cam->look += (objpos - cam->look)*.7f*delta*objvel;

		//look = obj->mass->pos.proj(&nextcam->look, &cam->look);
		
		//gluLookAt(cam->movepos.x, cam->movepos.y, cam->movepos.z, look.x, look.y, look.z, cam->up.x, cam->up.y, cam->up.z);
	}
	else if(view == LOCKED)
	{
		cam->look += (objpos - cam->look)*.7f*delta*objvel;
	}
	else if(view == FIRST)
	{
		cam->look += (objpos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
		cam2look = cam->look - cam->pos;
		cam->pos = objpos;
		//cam->pos += (objpos - cam->pos)*1.95f*delta;
		if(isKeys(VK_LEFT))
			camRotate = 100*delta;
		else if(isKeys(VK_RIGHT))
			camRotate = -100*delta;
		cam2look = cam2look.rotate3D(&majAxis, camRotate);
		cam->look = cam2look + cam->pos;
	}

	gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x, cam->up.y, cam->up.z);
	cam2look = cam->look - cam->pos;

	return cam2look;
}
*/

void level::addCamera(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist)
{
	cameras->addPoint(campos, lookpos, upin, dist);
	
	return;
}


Vector3D level::setCam(Vector3D* pos)
{
    CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
    CameraPoint* nextcam;
	Vector3D cam2cam, cam2obj, cam2look;
	Vector3D look, alongv, movepos;
	GLfloat camdist, objvel, camRotate;

	camRotate = 0;
	
    if(cameras->currentPoint == cameras->numPoints()-1)
	{
		nextcam = cam;
	}
	else
		nextcam = &cameras->cpoints[cameras->currentPoint+1];

	cam2obj = *pos - cam->pos;

	if(cameras->camview == FOLLOW)
	{
		movepos = *pos - cam2obj.unit()*cam->followDist;
		cam->pos += (*pos - cam->pos)*.2f*delta*objvel;
		cam->look += (*pos - cam->look)*.7f*delta*objvel;
	}
	else if(cameras->camview == LOCKED)
	{
		cam->look += (*pos - cam->look)*.7f*delta*objvel;
	}
	else if(cameras->camview == FIRST)
	{
		cam->look += (pos->proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
		cam2look = cam->look - cam->pos;
		cam->pos = *pos;

        if(isKeys(Qt::Key_Left))
			camRotate = 100*delta;
        else if(isKeys(Qt::Key_Right))
			camRotate = -100*delta;
		cam2look = cam2look.rotate3D(&majAxis, camRotate);
		cam->look = cam2look + cam->pos;
	}

    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());
	cam2look = cam->look - cam->pos;

	return cam2look;
}

void level::updateCam()
{
    CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
	
	if(cam->look == cam->pos)
	{
		cam->pos += X;
	}
	
	switch(cameras->camview)
	{
		case FIRST:
			//cam->look += (cam->pos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
			break;
		case FOLLOW:
			break;
		default:
//			MessageBox(NULL,"Invalid Camera View.","ERROR",MB_OK | MB_ICONINFORMATION);
            qErrnoWarning("Invalid Camera View %d", cameras->camview);
			break;
	}

    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());

	cam->oldPos = cam->pos;
	cam->oldLook = cam->look;
	return;
}

void level::setView(CameraView view)
{
	cameras->camview = view;
	return;
}

/*texture_s* level::addTexture(char *filename, char *ID)
{
	bool success = false;
	texture_s* ptr = NULL;

	success = LoadGLTextures(&alltexture[numTextures++], filename);
	if(success)
		ptr = &alltexture[numTextures-1];

	return ptr;
}

texture_s* level::addTexture(char *filename1, char *filename2, char *ID)
{
	bool success = false;
	texture_s* ptr = NULL;

	success = LoadGLTextures(&alltexture[numTextures], filename1);
	if(success)
		success = LoadGLTextures(&alltexture[numTextures++], filename2);
	if(success)
		ptr = &alltexture[numTextures-1];

	return ptr;
}*/


level3ds::level3ds(char* filename):level()
{
	strcpy(mapFileName,filename);
	//world3ds.Init_3ds(filename);
}

void level3ds::loadmap(GLfloat scale)
{
	world3ds.Init_3ds(mapFileName);
	for(int i=0; i<world3ds.m3DModel.numOfObjects; i++)
	{
		for(int j=0; j<world3ds.m3DModel.pObject[i].numOfVerts; j++)
		{
			//world3ds.m3DModel.pObject[i].pVerts[j] = world3ds.m3DModel.pObject[i].pVerts[j]*scale;
			world3ds.m3DModel.pObject[i].pVerts[j].x = world3ds.m3DModel.pObject[i].pVerts[j].x*scale;
			world3ds.m3DModel.pObject[i].pVerts[j].y = world3ds.m3DModel.pObject[i].pVerts[j].y*scale;
			world3ds.m3DModel.pObject[i].pVerts[j].z = world3ds.m3DModel.pObject[i].pVerts[j].z*scale;
		}
	}

	return;
}

void level3ds::run(GLfloat dt)
{
	char timetext[100];
    QTime clock;

	if(!started)
	{
		started = true;
//		startTime = GetTickCount();
        startTime = clock.msec();
		currentTime = startTime;
	}
	else
	{
        currentTime = clock.msec();
		timer = (currentTime-startTime)/1000;
		sprintf(timetext, "%.2f", timer);
	}

	updateCam();
	run3ds();
	allObj.run(dt);
	world3ds.Render_3ds();
	allObj.draw();
	

	//msgList.display(dt);

	return;
}

void level3ds::run3ds()
{
	/*for (int a = 0; a < allObj.spheres->numOfMasses; ++a)		// We will iterate every mass
	{
		allObj.spheres->objs[a].init();
	}

	detectCollision(&allObj, &world3ds.m3DModel);
	for(int sidx = 0; sidx < allObj.spheres->numOfMasses; sidx++)
	{
		if(allObj.spheres->objs[sidx].isTouching3ds)
			collide(&allObj.spheres->objs[sidx], &world3ds.m3DModel);
		//;
	}*/

	return;
}


gameObj::gameObj()
{
	numPlayers = 0;
	players = NULL;
	planePlayer = NULL;
	numLevels = 0;
	currentLevel = -1;
	numMenus = 0;
	currentMenu = -1;
	gMode = gmMENU;
	numTextures = 0;
}

bool gameObj::addLevel(int index)
{
	bool success = false;

	if(numLevels == 0)
		currentLevel = 0;

	levels[currentLevel].create(index);

	if(numLevels<MAXLEVELS)
	{
		numLevels++;
		success = true;
	} 
	
	return success;
}

bool gameObj::addLevel(char* file, Vector3D initCamPos, Vector3D initLookPos, Vector3D upDir, CameraView view)
{
	bool success = false;
	
	if(numLevels == 0)
		currentLevel = 0;
	if(numLevels<MAXLEVELS)
	{
		strcpy(levels[numLevels].mapFileName,file);
		levels[numLevels].cameras->addPoint(initCamPos,initLookPos,upDir,DEFFOLLOWDIST);
		levels[numLevels].cameras->camview = view;
		levels[numLevels].majAxis = upDir;
		numLevels++;
		
		success = true;
	} 
	
	return success;
}

texture_s* gameObj::addTexture(char *filename, char *ID)
{
	bool success = false;
	texture_s* ptr = NULL;
	string errString;

//	success = LoadGLTextures(&alltexture[numTextures++], filename);
    success = LoadGLTextures(&alltexture[numTextures++].layer[0], filename);
	if(success)
		ptr = &alltexture[numTextures-1];
	else
	{
		errString = "Texture file failed to load "+(string)filename;
//		MessageBox(NULL, errString.c_str() , TEXT("Texture Loading"), MB_ICONERROR | MB_OK);
        qErrnoWarning(errString.c_str());
	}

	return ptr;
}

void gameObj::setPlayerShape(Shape pShape)
{
	playerShape = pShape;
	
	switch(pShape)
	{
		case SPHERE:
			players = new object_sphere[MAXPLAYERS];
			break;
		case PLANE:
			players = new object_plane[MAXPLAYERS];
			break;
		default:
			break;
	}
	
	return;
}

void gameObj::addPlayer(object_plane* plane)
{
	setPlayerShape(PLANE);
	planePlayer = static_cast<object_plane*>(plane);
	

	return;
}


void gameObj::run(Mouse *ms, void (*commandFcn)(gameObj *, Mouse *), GLfloat delta)
{
    QTime clock;
    int timeMs = clock.msec();
    QVector3D pos;
    QVector3D look;

	switch(gMode)
	{
		case gmMENU:
			if(numMenus>0)
				glEnable(GL_LIGHTING);

                pos = QVector3D(sin(timeMs/30000.5f)*2.0f*cos(timeMs/30.5f), 0, 11.0f*cos(sin(timeMs/3000.5f)+5.0f));
                look = QVector3D(0, 0, 0);
                glLookAt(pos, look, Y.toQVector3D());		// This determines where the camera's position and view is
				menus[currentMenu].display();
			if(ms != NULL)
			{
                if(ms->isBtns(Qt::LeftButton))
					gMode = gmPLAY;
			}
            if(isKeys(Qt::Key_Return))
				gMode = gmPLAY;
			break;
        case gmPLAY:
            if(commandFcn!=NULL)
                commandFcn(this, ms);
            levels[currentLevel].run(delta);
            break;
        default:
            break;
	}	
	
	return;
}
	
bool gameObj::addMenu(char* mTitle)
{
	bool success = false;
	
	if(numMenus < MAXMENUS)
	{
		menus[numMenus].ID = mTitle;
//		menus[numMenus].font = &font;
//		menus[numMenus].font3d = &font3d;
		numMenus++;
		
		if(currentMenu == -1)
			currentMenu = 0;
	}
	
	return success;
}

gameObj::~gameObj()
{
	//delete players;
	//delete planePlayer;
}
