#ifndef ANIMATION
#define ANIMATION

//#include <windows.h>								// Header File For Windows
//#include <gl\gl.h>									// Header File For The OpenGL32 Library
//#include <gl\glu.h>

#include "objects.h"

enum actions{actNONE, actRUN, actATTACK1, actJUMP, actWALL, actFLY, actDUCK, actSHOOT, actBLOCK, actJUMPATK, actJUMPSHOOT, actPUSH, actHURT, actRUNATK};
enum frame{animSTART, numFRAMES, repeatFRAME, animSPEED, lastFRAME, minstopFRAME, canHOLD};

#define NUMACTIONS 13
#define MAXTEXTURES 100
//#define MAXFRAMES

#define DEFFRAMESPEED 10
//#define DEFRUNFRAMESPD 17
extern int DEFRUNFRAMESPD;
#define DEFATK1FRAMESPD 120
#define DEFJUMPFRAMESPD 150

#define DEFJUMPSTRENGTH 1.0f
#define DEFMAXSPEED 5.0f

struct Animation
{
	Vector2D scale[100];			//scaling factors for texture
	Vector2D pixels;
		//GLfloat hScale[100];
		//int pixelsW;
		//GLfloat wScale[100];
		//int pixelsH;

	int numTextures;				//number of textures in the object
	GLuint textures[100];
	GLfloat centers[100];			//center coords for texture
	
	int frameData[20][7];			//make sure NUMACTIONS=20

	int lastFrame;
	
	character person;
	block blk;
	shots sType;

	//attributes of object with animdata
	bool canWallClimb;
	bool canGrabWall;
	bool canShoot;
	bool canRoll;
	bool animates;
	bool isSolid;

	GLfloat jumpStrength;
	GLfloat maxSpeed;

    Animation()
	{
		for(int i=0; i<NUMACTIONS; i++)
		{
			frameData[i][animSTART] =  -1;
			frameData[i][animSPEED] = 10*DEFFRAMESPEED;
			frameData[i][minstopFRAME] = -1;
			frameData[i][canHOLD] = 0;
		}

		frameData[actRUN][animSPEED] = DEFRUNFRAMESPD;
		frameData[actATTACK1][animSPEED] = DEFATK1FRAMESPD;
		frameData[actJUMP][animSPEED] = DEFJUMPFRAMESPD;

		frameData[actDUCK][canHOLD] = 1;
		frameData[actWALL][canHOLD] = 1;
		frameData[actSHOOT][canHOLD] = 1;
		
		for(int i=0; i<MAXTEXTURES; i++)
			centers[i] = .5f;
		
		numTextures = 0;

		canWallClimb = false;
		canGrabWall = false;
		canShoot = false;
		canRoll = false;
		animates = false;
		isSolid = true;
		
		jumpStrength = DEFJUMPSTRENGTH;	//make into defaults
		maxSpeed = DEFMAXSPEED;
	}

};

extern QList<Animation> playerTextures;
extern QList<Animation> objectTextures;
extern QList<Animation> shotTextures;

void doTextures();
void assignTextures(Object &obj, Animation *animData);
void setDefaults(QList<Animation> animData, int numobjs);	//last frame and minstop frame
bool animate(Object &obj, actions act, const Animation *animData, GLfloat dt);
bool sendAnimation(Object &obj, actions act, GLfloat dt);
void fixSize(Object &animObj);


#endif

