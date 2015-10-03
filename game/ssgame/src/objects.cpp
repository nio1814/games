//#include <windows.h>
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
//#include <gl\gl.h>							// Header File For The OpenGL32 Library
//#include <gl\glu.h>

#include "vector3d.h"

#include "objects.h"
//#include "text.h"
#include "masking.h"
#include "functions.h"
#include "math.h"
#include "animation.h"
#include "keys.h"
#include "movement.h"

GLfloat DEFMASS = 5.0f;
GLfloat DEFSPEED = 1.0f;
GLfloat DEFJMPSTR = 1.0f;
GLfloat DEFRICTION = 1.0f;

int objectIndex = 0;
objectHolder_c AllObjects;

object_c::object_c()
{
    init();
	
	//AllObjects.setObject(this, index);
}
    
    
object_c::object_c(GLfloat wid, GLfloat hei, type oType, int ident)
{
	init(wid, hei, oType, ident);

	AllObjects.numObjects--;
	AllObjects.setObject(this, index);
}

object_c::object_c(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, type oType, int ident)
{
    init(wid, hei, oType, ident);
   
    posOld = Vector2D(xStart, yStart);
    pos = posOld;

	AllObjects.numObjects--;
	AllObjects.setObject(this, index);
}

void object_c::init()
{
	posOld	= Vector2D(0.0f, 0.0f);
	pos		= Vector2D(0.0f, 0.0f);
    posz	= 0.0f;
    vel		= Vector2D(0.0f, 0.0f);
    velOld	= Vector2D(0.0f, 0.0f);
    accel	= Vector2D(0.0f, 0.0f);
	center	= .5f;
	diag	= 0;
	mass	= DEFMASS;
	xSpeed = DEFSPEED;
	MV = Vector2D(0.0f, 0.0f);
	friction = DEFRICTION;
	rotate = 0.0f;
	jumpStrength = DEFJMPSTR;
	isTouching[0] = false;
	isTouching[1] = false;
	isTouching[2] = false;
	isTouching[3] = false;

	for(int i =0; i<NUMACTIONS; i++)
	{
		frameFloat[i] = 0.0f;
		animationDone[i] = true;
		state[i] = false;
	}

	index = objectIndex++;
	parent = NULL;
	objshots = NULL;

	active	= true;
	isSolid = true;
	projectile = false;
	inFront = false;
	pRight	= true;
	dirSign = 1.0f;
	animFrame = 0;
	animated = false;
	currentAct = 0;
	isAttacking = false;

	texture = new GLuint[20];
	wraps = Vector2D(1,1);
	WrapMove = Vector2D(0.0f, 0.0f);

	/*objType = 0;
	person = 0;
	shotType = 0;*/
	health = 1.0f;

	calcBoundaries();

	return;
}

void object_c::init(GLfloat wid, GLfloat hei, type oType, int ident)
{
	init();

	oDimension = dimension = Vector2D(wid, hei);
	calcBoundaries();
	diag = dist(pos.x, pos.y + .5f*dimension.y, pos.x + .5f*dimension.x, pos.y + dimension.y);
	
	objType = oType;
		
	switch(oType)
	{
		case tpPLAYER:
		case tpENEMY:
			person = static_cast<character>(ident);
			break;
		case tpSHOT:
			shotType = static_cast<shots>(ident);
			break;
		case tpGROUND:
		case tpWATER:
			blkType = static_cast<block>(ident);
			break;
		default:
			break;
	}	

	return;
}
object_c& object_c::operator= (object_c obj)				// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
{
	this->pos = obj.pos;
	this->posOld = obj.posOld;
	this->dimension = obj.dimension;
	this->oDimension = obj.oDimension;
	this->scale = obj.scale;
		//this->hScale = obj.hScale;
		//this->wScale = obj.wScale;
	this->diag		= obj.diag;
	this->texture	= obj.texture;
	this->centers	= obj.centers;
	this->WrapMove	= obj.WrapMove;
	this->posMin	= obj.posMin;
	this->posMax	= obj.posMax;
	this->posMinOld = obj.posMinOld;
	this->posMaxOld = obj.posMaxOld;
	this->vel		= obj.vel;
	this->velOld	= obj.velOld;
	this->xSpeed	= obj.xSpeed;
	this->jumpStrength = obj.jumpStrength;
	this->MV		= obj.MV;
	this->mass		= obj.mass, accel = obj.accel;
	this->rotate	= obj.rotate;
	this->dirSign	= obj.dirSign;
	this->health	= obj.health;
	this->canWallClimb = obj.canWallClimb;
	this->canShoot	= obj.canShoot;
	this->canRoll	= obj.canRoll;

	this->active	= obj.active;
	this->pRight	= obj.pRight;
	this->isSolid	= obj.isSolid;

	for(int j=0; j<4; j++)
	{
		this->isTouching[j] = obj.isTouching[j];
		this->isTouchIndex[j] = obj.isTouchIndex[j];
	}
	
	this->inFront = obj.inFront;


	this->index		= obj.index;
	this->parent	= obj.parent;
	this->objshots == NULL;
	if(obj.objshots != NULL)
	{
		this->objshots = new shotList_c;
		this->objshots->numActive = obj.objshots->numActive;
		this->objshots->numFree = obj.objshots->numFree;
		this->objshots->numShots = obj.objshots->numShots;

		for(int i=0; i<obj.objshots->numShots; i++)
		{
			this->objshots->slist[i] = obj.objshots->slist[i];
		}
	}
	this->animFrame = obj.animFrame;
	this->animated	= obj.animated;
	
	for(int i=0; i<NUMACTIONS; i++)
	{
		this->state[i] = obj.state[i];
		this->frameFloat[i] = obj.state[i];
		this->animationDone[i] = obj.animationDone[i];
		this->actionTime[i].done = obj.actionTime[i].done;
		this->actionTime[i].started = obj.actionTime[i].started;
		this->actionTime[i].startTime = obj.actionTime[i].startTime;
		this->actionTime[i].timeHeld = obj.actionTime[i].timeHeld;
	}
	
	this->person	= obj.person;
	this->objType	= obj.objType;
	this->shotType	= obj.shotType;
	this->blkType	= obj.blkType;
	this->numPlayer = obj.numPlayer;

	this->wraps = obj.wraps;
	//int xWraps, yWraps;

	//char picFile = obj.picFile;
	//char ID = obj.ID;

/*object_c::~object_c()
{
	delete [] texture;
}*/
	return *this;
}

void object_c::drawRec()
{

	glBindTexture(GL_TEXTURE_2D, texture[animFrame]);				// Select A Texture Based On filter
	glEnable(GL_TEXTURE_2D);
	
	calcBoundaries();
	
	glPushMatrix();
	//glMatrixMode(GL_TEXTURE);
	//glTranslatef(.5f*width, .5f*height, 0.0f);

	//glColor3f(.315f*sin(GetTickCount()/10.0f), cos(GetTickCount()/100.0f), .5f*sin(GetTickCount())/3.0f);
	glTranslatef(pos.x, pos.y + .5f*dimension.y, 0.0f);
	glRotatef(rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(-(pos.x), -(pos.y + .5f*dimension.y), 0.0f);
	if(pRight)
	{
		glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f + WrapMove.x,1.0f*wraps.y);glVertex3f(posMin.x , posMax.y, 0.0f);				// Top Left
			glTexCoord2f(1.0f*wraps.x + WrapMove.x,1.0f*wraps.y);glVertex3f(posMax.x , posMax.y, 0.0f);				// Top Right
			glTexCoord2f(1.0f*wraps.x + WrapMove.x,0.0f*wraps.y);glVertex3f(posMax.x , posMin.y, 0.0f);				// Bottom Right
			glTexCoord2f(0.0f + WrapMove.x,0.0f*wraps.y);glVertex3f(posMin.x , posMin.y, 0.0f);				// Bottom Left
		glEnd();

		/*glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f((0.0f+rotate)/xWraps,1.0f/yWraps);glVertex3f(xMin , yMax, 0.0f);				// Top Left
			glTexCoord2f((1.0f+rotate)/xWraps,1.0f/yWraps);glVertex3f(xMax , yMax, 0.0f);				// Top Right
			glTexCoord2f((1.0f+rotate)/xWraps,0.0f/yWraps);glVertex3f(xMax , yMin, 0.0f);				// Bottom Right
			glTexCoord2f((0.0f+rotate)/xWraps,0.0f/yWraps);glVertex3f(xMin , yMin, 0.0f);				// Bottom Left
		glEnd();*/
	}
	else
	{
		glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(1.0f,1.0f);glVertex3f(posMin.x , posMax.y, 0.0f);				// Top Left
			glTexCoord2f(0.0f,1.0f);glVertex3f(posMax.x , posMax.y, 0.0f);				// Top Right
			glTexCoord2f(0.0f,0.0f);glVertex3f(posMax.x , posMin.y, 0.0f);				// Bottom Right
			glTexCoord2f(1.0f,0.0f);glVertex3f(posMin.x , posMin.y, 0.0f);				// Bottom Left
		glEnd();
	}

	//glRotatef(-rotate,0.0f,0.0f,1.0f);
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	return;
}


void object_c::drawCube()
{
	calcBoundaries();

	glBindTexture(GL_TEXTURE_2D, texture[animFrame]);				// Select A Texture Based On filter
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glMatrixMode(GL_TEXTURE);

	//glRotatef(rotate,0.0f,0.0f,1.0f);						// Rotate On The X Axis By xrot
	if(pRight)
	{
		/*glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f,1.0f);glVertex3f(xMin , yMax, 0.0f);				// Top Left
			glTexCoord2f(1.0f,1.0f);glVertex3f(xMax , yMax, 0.0f);				// Top Right
			glTexCoord2f(1.0f,0.0f);glVertex3f(xMax , yMin, 0.0f);				// Bottom Right
			glTexCoord2f(0.0f,0.0f);glVertex3f(xMin , yMin, 0.0f);				// Bottom Left
		glEnd();*/

		glBegin(GL_QUADS);						// Top Quad
			glNormal3f(0.0f, 1.0f, 0.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f+WrapMove.x,1.0f);glVertex3f(posMin.x , posMax.y, -depth);				// Top Left
			glTexCoord2f(1.0f+WrapMove.x,1.0f);glVertex3f(posMax.x , posMax.y, -depth);				// Top Right
			glTexCoord2f(1.0f+WrapMove.x,0.0f);glVertex3f(posMax.x , posMax.y, depth);				// Bottom Right
			glTexCoord2f(0.0f+WrapMove.x,0.0f);glVertex3f(posMin.x , posMax.y, depth);				// Bottom Left
		glEnd();

		glBegin(GL_QUADS);						// Bottom Quad
			glNormal3f(0.0f, -1.0f, 0.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f+WrapMove.x,1.0f);glVertex3f(posMin.x , posMin.y, -depth);				// Top Left
			glTexCoord2f(1.0f+WrapMove.x,1.0f);glVertex3f(posMax.x , posMin.y, -depth);				// Top Right
			glTexCoord2f(1.0f+WrapMove.x,0.0f);glVertex3f(posMax.x , posMin.y, depth);				// Bottom Right
			glTexCoord2f(0.0f+WrapMove.x,0.0f);glVertex3f(posMin.x , posMin.y, depth);				// Bottom Left
		glEnd();

		glBegin(GL_QUADS);						// right Quad
			glNormal3f(1.0f, 0.0f, 0.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f+WrapMove.x,1.0f);glVertex3f(posMax.x , posMax.y, depth);				// Top Left
			glTexCoord2f(1.0f+WrapMove.x,1.0f);glVertex3f(posMax.x , posMax.y, -depth);				// Top Right
			glTexCoord2f(1.0f+WrapMove.x,0.0f);glVertex3f(posMax.x , posMin.y, -depth);				// Bottom Right
			glTexCoord2f(0.0f+WrapMove.x,0.0f);glVertex3f(posMax.x , posMin.y, depth);				// Bottom Left
		glEnd();

		glBegin(GL_QUADS);						// left Quad
			glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f+WrapMove.x,1.0f);glVertex3f(posMin.x , posMax.y, depth);				// Top Left
			glTexCoord2f(1.0f+WrapMove.x,1.0f);glVertex3f(posMin.x , posMax.y, -depth);				// Top Right
			glTexCoord2f(1.0f+WrapMove.x,0.0f);glVertex3f(posMin.x , posMin.y, -depth);				// Bottom Right
			glTexCoord2f(0.0f+WrapMove.x,0.0f);glVertex3f(posMin.x , posMin.y, depth);				// Bottom Left
		glEnd();

	}
	else
	{
		glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(1.0f,1.0f);glVertex3f(posMin.x , posMax.y, 0.0f);				// Top Left
			glTexCoord2f(0.0f,1.0f);glVertex3f(posMax.x , posMax.y, 0.0f);				// Top Right
			glTexCoord2f(0.0f,0.0f);glVertex3f(posMax.x , posMin.y, 0.0f);				// Bottom Right
			glTexCoord2f(1.0f,0.0f);glVertex3f(posMin.x , posMin.y, 0.0f);				// Bottom Left
		glEnd();
	}

	//glRotatef(-rotate,0.0f,0.0f,1.0f);
	//glTranslatef(-.5f*width, -.5f*height, 0.0f);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	return;
}


void object_c::calcBoundaries()
{
	//width = wScale[animFrame]*oWidth;
	//height = hScale[animFrame]*oHeight;
	
	diag = dist(pos.x, pos.y + .5f*dimension.y, pos.x + .5f*dimension.x, pos.y + dimension.y);

	if(animated)
	{
		posMin = Vector2D(-((dirSign-1)/(-2)+dirSign*centers[animFrame])*dimension.x + pos.x, pos.y);
		posMax = Vector2D(((dirSign+1)/2-dirSign*centers[animFrame])*dimension.x + pos.x, dimension.y + pos.y);
			//xMin = -((dirSign-1)/(-2)+dirSign*centers[animFrame])*dimension.x + x;
		//xMax = (1-centers[animFrame])*width + x;
			//xMax = ((dirSign+1)/2-dirSign*centers[animFrame])*dimension.x + x;
			//yMin = y;
			//posMax.y = dimension.y + y;
	}
	else
	{
		posMin = Vector2D(-0.5f*dimension.x + pos.x, pos.y);
		posMax = Vector2D(0.5f*dimension.x + pos.x, dimension.y + pos.y);
	}

	return;
}

bool object_c::addShots(int numS, GLfloat wid, GLfloat hei, shots sType)
{
	bool couldAdd = false;

	if(objshots == NULL)
	{
		objshots = new shotList_c(numS, wid, hei, sType, this);
		couldAdd = true;
	}

	return couldAdd;
}

bool object_c::isTouched()
{
	bool isTouched = false;
	isTouched = isTouching[BSIDE] || isTouching[RSIDE] || isTouching[TSIDE] || isTouching[LSIDE];

	return isTouched;
}

//OBJECT HOLDER
void objectHolder_c::setObject(object_c *obj, int index)
{
	objects[index] = obj;
	numObjects++;
	
	return;
}


void objectHolder_c::setObject(object_c *obj)
{
	objects[numObjects] = obj;
	numObjects++;
	
	return;
}


object_c* objectHolder_c::getObject(int index)
{
	object_c *obj;
	obj = objects[index];
	
	return obj;
}

//SHOTLIST----------
shotList_c::shotList_c()
{
	numShots = 0;
	numActive = 0;
	numFree = 0;
	maxDist = 20.0f;
	slist = NULL;
}

shotList_c::shotList_c(int numS, GLfloat wid, GLfloat hei, shots shotType, object_c *pnt)
{
	numShots = numS;
	numActive = 0;
	numFree = numS;
	maxDist = 20.0f;
	slist = new object_c[numS];
	
	for(int i=0; i<numS; i++)
	{
		slist[i].init(wid, hei, tpSHOT, shotType);
		slist[i].parent = pnt;
		slist[i].active = false;
		assignTextures(slist[i], shotTextures[shotType]);
	}
}

object_c* shotList_c::nextShot()
{
	object_c* nshot = NULL;
	int i=0;

	do{
		if(!slist[i].active)
			nshot = &slist[i];
		i++;
	}while((nshot == NULL) && (i<numShots));

	if(nshot != NULL)
	{
		nshot->active = true;
		numActive++;
		numFree--;
	}

	return nshot;
}

void shotList_c::updateShots()
{
	for(int i=0; i<numShots; i++)
	{
		if(fabs(dist(&slist[i], slist[i].parent)) > maxDist)
		{
			slist[i].active = false;
			numActive--;
			numFree++;
		}
	}

	return;
}

//object_c* shotList_c::currentShot();

object_c* getObject(int index)
{
	object_c *obj;
	obj = AllObjects.getObject(index);
	
	return obj;
}
