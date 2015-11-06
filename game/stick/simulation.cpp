#include "simulation.h"

#include "keys.h"

Simulation::Simulation()
{
    cameras = new CameraPoints;
	simNum = 0;
    paused = false;
}

Simulation::~Simulation()
{
    delete cameras;
}

void Simulation::run(GLfloat dt)
{
    setCam(allObj.planes.objs[0]);
	if(!paused)
		allObj.run(dt);

	return;
}

void Simulation::draw()
{
    allObj.draw();
}

Vector3D Simulation::setCam(Object* obj)
{
    CameraPoint* cam = &cameras->current();
    CameraPoint* nextcam;
	Vector3D cam2cam, cam2obj, cam2look;
	Vector3D pos, look;						//final cam position and look positions
	Vector3D alongv, movepos;
	Vector3D objpos;
	GLfloat camdist, objvel, camRotate;

    Vector3D majAxis = Vector3D(0,0,1);
    GLfloat delta = .05;

	camRotate = 0;

    if(cameras->currentPoint == cameras->numPoints()-1)
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
	
    QTime clock;
    int ms = clock.msec();
    GLfloat costime = .5f*cos(ms * 0.001f)+.5f;
	glColor3ub(142*costime, 26*costime, 256*costime);
	switch(cameras->camview)
	{
		case FOLLOW:
//			glPrintHead(3,3,"Follow Cam",15);
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
			break;
		case LOCKED:
//			glPrintHead(3,3,"Locked Cam",15);
			cam->look += (objpos - cam->look)*.7f*delta*objvel;
			break;
		case CAMERAMODE:
//			glPrintHead(3,3,"Camera Mode",15);
			look = cam->look;
			pos = cam->pos;
			break;
		case DEBUGMODE:
//			glPrintHead(3,3,"Debug Mode",15);
			break;
		case FIRST:
//			glPrintHead(3,3,"First Person",15);
			cam->look += (objpos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
			cam2look = cam->look - cam->pos;
			cam->pos = objpos;
			//cam->pos += (objpos - cam->pos)*1.95f*delta;
            if(isKeys(Qt::Key_Left))
				camRotate = 100*delta;
            else if(isKeys(Qt::Key_Right))
				camRotate = -100*delta;
            cam2look = cam2look.rotate3D(majAxis, camRotate);
			cam->look = cam2look + cam->pos;
			break;
		default:
//			glPrintHead(3,3,"No View",15);
			break;
	}

    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());
	cam2look = cam->look - cam->pos;

	return cam2look;
}

void Simulation::setView(CameraView view)
{
	cameras->camview = view;
	return;
}
