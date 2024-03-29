#include "cubewindow.h"

#include "camera.h"
#include "mouse.h"
#include "keys.h"
#include "constants.h"

#define CAMOVESPEED 2.0f

CubeWindow::CubeWindow(QWidget *parent) :
	GLWidget(parent)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				//rcube.cubes[i][j][k] = cube_c(CORNER, static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1));
				rcube.cubes[i][j][k] = cube_c(CORNER, YELLOW, WHITE, RED, ORANGE, GREEN, BLUE);
			}
		}
	}

	char axes[] = "XYZ";
	int directions[] = {-1,1};
	for (int n=0; n<20; n++)
	{
		rcube.rotationAxis = axes[qrand()%3];
		rcube.rotationIndex = qrand()%3;
		rcube.rotationDirection = directions[qrand()%2];
		rcube.moveCubes();
	}
	rcube.rotationAxis = '\0';
}

void CubeWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	if(lightActive)
	{
		glEnable(GL_LIGHTING);
//        light.enable();
	}
	else
		glDisable(GL_LIGHTING);

//	runControls();
//	gluLookAt(cam->pos.x, cam->pos.y+.001f, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x,cam->up.y,cam->up.z);
	glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());

	static int tan = 0;
	/*switch(tan)
	{
	case 0:
		rcube.rotateCube('Y', 0, 1);
		break;
	case 1:
		rcube.rotateCube('X', 1, -1);
		break;
	case 2:
		rcube.rotateCube('Z', 2, 1);
		break;
	case 3:
		//rcube.rotateCube('Y', 2, -1);
		break;
	case 4:
		rcube.rotateCube('X', 2, 1);
		break;
	default:
		break;
	}*/

	rcube.drawCube();

	glColor3ub(255, 255, 205);		// Set Color To White
	glPushMatrix();
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex3f(.9f*cam->pos.x, .9f*cam->pos.y, .9f*cam->pos.z); // origin of the line
		glVertex3f(moslook.x,moslook.y , moslook.z); // ending point of the line
	glEnd( );

	glPopMatrix();

	rcube.updateCube();

	/*if(!rcube.isRotating)
		tan++;*/
}

void CubeWindow::animate()
{
	if(!rcube.isRotating)
		disconnect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));

	runUpdate();

	return;
}

void CubeWindow::runMouse()
{
	Vector3D cam2look = cam->cam2look();
	Vector3D toSideDir = cam->dir2RSide();
	Vector3D look2cam = -cam2look;
	Vector3D camposOld;
	Vector3D mouseMove;
	bool wasRotating = rcube.isRotating;

	if(mos->isBtns(Qt::LeftButton) && !isKeys(Qt::Key_Control))
	{
		mouseMove = Vector3D(mos->x-mos->xOld, mos->yOld-mos->y, 0);	//find movement in screen coords
		GLfloat len = mouseMove.length();
		if(mouseMove.length() > 2.0f)
		{
			mouseMove.unitize();
			mouseMove = cam->up*mouseMove.y + cam->dir2RSide()*mouseMove.x;
			rcube.twistCube(cam->pos, moslook, mouseMove);
		}
	}
	else if(mos->isBtns(Qt::RightButton) || mos->isBtns(Qt::LeftButton))
	{
		if(mos->y != mos->yOld)
		{
			look2cam = look2cam.rotate3D(toSideDir,(mos->yOld-mos->y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			cam->up = cam->up.rotate3D(toSideDir,(mos->yOld-mos->y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			camposOld = cam->pos;
			cam->pos = cam->look + look2cam;
		}

		cam2look = cam->cam2look();
		toSideDir = cam->dir2RSide();
		if(mos->x != mos->xOld)
		{
			look2cam = look2cam.rotate3D(cam->up,-(mos->x-mos->xOld)*DEFMOUSETHROTTLEX*1.3f*CAMOVESPEED);
			camposOld = cam->pos;
			cam->pos = cam->look + look2cam;
		}
	}

	static GLfloat origFollowDist = cam->followDist;
	cam->followDist = origFollowDist*exp(-mos->wheel*.0007f);
	cam->pos = cam->look + look2cam.unit()*cam->followDist;

	Vector2D screenDimGL;
	screenDimGL.x = 2*cam->followDist*tan(fovAngle.x*DEG2RAD/2.0f);
	screenDimGL.y = 2*cam->followDist*tan(fovAngle.y*DEG2RAD/2.0f);

	Vector2D mousePtInSpace;
	mousePtInSpace.x = ((mos->x-m_windowSizeX/2)/(float)m_windowSizeX)*screenDimGL.x;
	mousePtInSpace.y = ((m_windowSizeY/2-mos->y)/(float)m_windowSizeY)*screenDimGL.y;
	moslook = cam->dir2RSide()*mousePtInSpace.x+cam->up*mousePtInSpace.y;

	if(!wasRotating && rcube.isRotating)
	{
		connect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));
		m_timer->start(30);
	}

	return;
}


void CubeWindow::rotateLR(GLfloat angle)
{
	Vector3D look2cam = -cam->cam2look();

	look2cam = look2cam.rotate3D(cam->up,-angle);
//	camposOld = cam->pos;
	cam->pos = cam->look + look2cam;

	emit animate();
}

void CubeWindow::rotateUD(GLfloat angle)
{
	Vector3D look2cam = -cam->cam2look();
	Vector3D toSideDir = cam->dir2RSide();

	look2cam = look2cam.rotate3D(toSideDir, angle);
	cam->up = cam->up.rotate3D(toSideDir, angle);
//	camposOld = cam->pos;
	cam->pos = cam->look + look2cam;

	emit animate();
}

void CubeWindow::runKeys()
{
	bool wasRotating = rcube.isRotating;

	GLfloat rotateAngle = 5;
	if(isKeys(Qt::Key_Left))
		rotateLR(-rotateAngle);
	else if(isKeys(Qt::Key_Right))
		rotateLR(rotateAngle);

	if(isKeys(Qt::Key_Up))
		rotateUD(-rotateAngle);
	else if(isKeys(Qt::Key_Down))
		rotateUD(rotateAngle);

	if(canToggle(Qt::Key_L))
	{
		lightActive = !lightActive;
		emit animate();
	}
	if(canToggle(Qt::Key_P))
		int pause = 5;

	if(!rcube.isRotating)
	{
		if(canToggle(Qt::Key_Y))
			rcube.rotateCube(cam->up, 2, 1);
		else if(canToggle(Qt::Key_W))
			rcube.rotateCube(cam->up, 2, -1);
		else if(canToggle(Qt::Key_G))
			rcube.rotateCube(cam->up, 1, 1);
		else if(canToggle(Qt::Key_D))
			rcube.rotateCube(cam->up, 1, -1);
		else if(canToggle(Qt::Key_N))
			rcube.rotateCube(cam->up, 0, 1);
		else if(canToggle(Qt::Key_X))
			rcube.rotateCube(cam->up, 0, -1);
		else if(canToggle(Qt::Key_T))
			rcube.rotateCube(cam->dir2RSide(), 2, -1);
	}

	if(!wasRotating && rcube.isRotating)
	{
		connect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));
		m_timer->start(30);
	}

//	emit animate();
}
