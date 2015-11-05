#ifndef CAMERA
#define CAMERA

//#include <windows.h>									// Header File For Windows
//#include <gl\gl.h>										// Header File For The OpenGL32 Library
//#include <gl\glu.h>										// Header File For The GLu32 Library

#include <qlist.h>

#include <vector3d.h>
#include "qtgl.h"

#define DEFFOLLOWDIST	10
#define DEFNUMCAMS	20
#define NUMCAMVIEWS	5

enum CameraView{FOLLOW, LOCKED, CAMERAMODE, DEBUGMODE, FIRST};

class CameraPoint
{
public:
	Vector3D oldPos, pos;
	Vector3D oldLook, look;				//position looking at
	Vector3D up;						//up direction
	GLfloat followDist;					//default distance from camera to look point

	CameraPoint();
	CameraPoint(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist);
	CameraPoint& operator= (CameraPoint cp);
	Vector3D cam2look();
	Vector3D dir2RSide();
};

class CameraPoints
{
public:
	int numPoints();

	CameraPoints();
	CameraPoints(Vector3D campos, Vector3D lookpos, Vector3D upin, GLfloat dist);

	void addPoint(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist);
	void cycleView();
	void setLook(Vector3D newLook);
    CameraPoint& current();

    QList<CameraPoint> cpoints;
    int currentPoint;
    CameraView camview;
};

void setCam(CameraPoints* cpoints, Vector3D* objpos, CameraView view);

#endif
