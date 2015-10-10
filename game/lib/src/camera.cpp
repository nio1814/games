//#include <windows.h>									// Header File For Windows
//#include <gl\gl.h>										// Header File For The OpenGL32 Library
//#include <gl\glu.h>										// Header File For The GLu32 Library

#include "camera.h"

#include <QtGui>

#include "vector3d.h"


CameraPoint::CameraPoint()
{
	oldPos = Vector3D(0,0,0);
	pos = oldPos;
	oldLook = Vector3D(0,0,0);
	look = oldLook;
	up = Vector3D(0,1,0);							//default up dir is Y
	followDist = 1.0f;
}

CameraPoint::CameraPoint(Vector3D campos, Vector3D lookpos, Vector3D upin, GLfloat dist)
{
	oldPos = campos;
	pos = oldPos;
	oldLook =  lookpos;
	look = oldLook;
	up = upin;
	followDist = dist;
}

CameraPoint& CameraPoint::operator= (CameraPoint cp)
{
	oldPos = cp.oldPos;
	pos = cp.pos;
	oldLook = cp.oldLook;
	look = cp.look;
	up = cp.up;
	followDist = cp.followDist;
	
	return *this;
}

Vector3D CameraPoint::cam2look()
{
	Vector3D vout;
	
	vout = look - pos;
	
	return vout;
}

Vector3D CameraPoint::dir2RSide()
{
	Vector3D toSideDir;
	Vector3D toLook = cam2look();
	
	toSideDir = Cross(&toLook,&up);
	toSideDir.unitize();
	
	return toSideDir;
}



CameraPoints::CameraPoints()
{
//	cpoints = new CameraPoint[DEFNUMCAMS];
//	numPoints = 0;
	currentPoint = 0;
	camview = FOLLOW;
}

CameraPoints::CameraPoints(Vector3D campos, Vector3D lookpos, Vector3D upin, GLfloat dist)
{
	CameraPoints();
	addPoint(campos, lookpos, upin, dist);
}

int CameraPoints::numPoints()
{
	return cpoints.size();
}

void CameraPoints::addPoint(Vector3D campos, Vector3D lookpos, Vector3D up, GLfloat dist)
{	
	return cpoints.append(CameraPoint(campos, lookpos, up, dist));
}

void CameraPoints::cycleView()
{
	int cv = camview;

	if(camview == (NUMCAMVIEWS-1))
		camview = static_cast<CameraView>(0);
	else
	{
		cv++;
		camview = static_cast<CameraView>(cv);
	}

	return;
}

void CameraPoints::setLook(Vector3D newLook)
{
	cpoints[currentPoint].look = newLook;

	return;
}

void setCam(CameraPoints* cameras, Vector3D* objpos, CameraView view)
{
	CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
	CameraPoint* nextcam;
	Vector3D pos, look, cam2cam, cam2obj, alongv;
	GLfloat camdist;

	cameras->camview = view;
	
	int nextCamIdx = qMin(cameras->cpoints.size()-1, cameras->currentPoint+1);

	nextcam = &cameras->cpoints[nextCamIdx];

	if(view == FOLLOW)
	{
		look = objpos->proj(&nextcam->oldLook, &cam->oldLook);
//		gluLookAt(cam->pos.x, cam->pos.y,cam->pos.z, objpos->x, objpos->y, 0, cam->up.x, cam->up.y, cam->up.z);
		QMatrix4x4 camMatrix;
		camMatrix.lookAt(cam->pos.toQVector3D(), objpos->toQVector3D(), cam->up.toQVector3D());
		glMultMatrixf(camMatrix.constData());
	}

	return;
}
