#include "simulation.h"

#include "keys.h"

#include <QTime>

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
	if(!paused)
		allObj.run(dt);

	return;
}

void Simulation::draw()
{
    setCam();
    allObj.draw();
}

Vector3D Simulation::setCam()
{
  if(!this->cameraFollowObject)
    return Vector3D();

	Vector3D cam2cam, cam2obj, cam2look;
	Vector3D pos, look;						//final cam position and look positions
	Vector3D alongv, movepos;
	Vector3D objpos;

    Vector3D majAxis = Vector3D(0,0,1);
    GLfloat delta = .05;

  GLfloat camRotate = 0;

  std::shared_ptr<const CameraPoint> nextcam = cameras->currentIndex == cameras->numPoints() - 1 ? this->cameras->current() : this->cameras->points[cameras->currentIndex + 1];

  objpos = this->cameraFollowObject->pos;
  const GLfloat objvel = this->cameraFollowObject->vel.length();
  cam2obj = this->cameraFollowObject->pos - this->cameras->current()->pos;

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
      if(this->cameraFollowObject->moveForce == Vector3D(0,0,0))
        movepos = objpos - cam2obj.unit()*this->cameras->current()->followDist;
			else
        movepos = objpos - (this->cameraFollowObject->moveForce.unit()*this->cameras->current()->followDist + cam2obj.unit()*this->cameras->current()->followDist)/2;
      this->cameras->current()->pos += (movepos - this->cameras->current()->pos)*.2f*delta*objvel;
      this->cameras->current()->look += (objpos - this->cameras->current()->look)*.7f*delta*objvel;

			//look = obj->mass->pos.proj(&nextcam->look, &cam->look);
			
			//gluLookAt(cam->movepos.x, cam->movepos.y, cam->movepos.z, look.x, look.y, look.z, cam->up.x, cam->up.y, cam->up.z);
			break;
		case LOCKED:
//			glPrintHead(3,3,"Locked Cam",15);
      this->cameras->current()->look += (objpos - this->cameras->current()->look)*.7f*delta*objvel;
			break;
		case CAMERAMODE:
//			glPrintHead(3,3,"Camera Mode",15);
      look = this->cameras->current()->look;
      pos = this->cameras->current()->pos;
			break;
		case DEBUGMODE:
//			glPrintHead(3,3,"Debug Mode",15);
			break;
		case FIRST:
//			glPrintHead(3,3,"First Person",15);
      this->cameras->current()->look += (objpos.proj(majAxis) - this->cameras->current()->look.proj(majAxis))*.95f*delta;
      cam2look = this->cameras->current()->look - this->cameras->current()->pos;
      this->cameras->current()->pos = objpos;
			//cam->pos += (objpos - cam->pos)*1.95f*delta;
            if(isKeys(Qt::Key_Left))
				camRotate = 100*delta;
            else if(isKeys(Qt::Key_Right))
				camRotate = -100*delta;
            cam2look = cam2look.rotate3D(majAxis, camRotate);
      this->cameras->current()->look = cam2look + this->cameras->current()->pos;
			break;
		default:
//			glPrintHead(3,3,"No View",15);
			break;
	}

    glLookAt(this->cameras->current()->pos.toQVector3D(), this->cameras->current()->look.toQVector3D(), this->cameras->current()->up.toQVector3D());
  cam2look = this->cameras->current()->look - this->cameras->current()->pos;

	return cam2look;
}

void Simulation::setView(CameraView view)
{
	cameras->camview = view;
	return;
}
