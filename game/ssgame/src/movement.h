#ifndef	MOVEMENT
#define MOVEMENT

//#include	<windows.h>							// Header File For Windows
//#include	<gl\gl.h>							// Header File For The OpenGL32 Library
//#include	<gl\glu.h>							// Header File For The GLu32 Library

#include "animation.h"
#include "objects.h"
#include "world.h"

extern GLfloat xrot;									// X Rotation
extern GLfloat	yrot;									// Y Rotation
extern GLfloat xspeed;									// X Rotation Speed
extern GLfloat yspeed;									// Y Rotation Speed
extern GLfloat	z;								// Depth Into The Screen
extern GLfloat leftScreen, rightScreen, bottomScreen, topScreen;
extern GLfloat x, y;
extern GLfloat depth;
extern GLfloat acceleration;
extern GLfloat timeStep;	//tempoarary

extern GLfloat XSCALE;
extern GLfloat GROUNDFRIC;
extern GLfloat WALLFRIC;
extern GLfloat airFric;
extern GLfloat COASTFAC;				//continuing xspeed while in air
extern GLfloat DUCKFRICFACTOR;			//increased friction from ducking
extern GLfloat RUNFRICFACTOR;			//increased friction from running
extern GLfloat JUMPVEL;					//velocity of jump
extern GLfloat STRONGJUMPFACTOR;
extern Vector2D WALLJUMPVEL;
extern GLfloat duckJumpFactor;			//increased jumping from ducking

extern GLfloat xMov[2];
extern GLfloat yMov[2];
extern GLfloat xP;
extern GLfloat yP;
extern GLfloat oscillator;

extern bool cameraMode;
extern bool debugMode;

void checkTouch(object_c &moveObj, const object_c &obj2);
void checkTouch(object_c &moveObj, level_s level);
void checkTouch(int mobjects[], int numObjects, const level_s &level);
void checkTouch(objectHolder_c mobjects, const level_s &level);
void checkTouch(object_c &moveObj, object_c objs[], int nobjs, int nocheck);

bool touchExists(const object_c &moveObj, const object_c &obj2);
void clearTouches(object_c &obj);
void clearStates(object_c &obj);

void updatePlayerMove(object_c &moveObj, GLfloat dt);
void updateObjectMove(object_c &moveObj, GLfloat dt);
void updateEnemyMove(object_c &moveObj, const object_c &target, GLfloat dt);
actions runEnemyAI(object_c &thisEnemy, const object_c &target);
void updateMoves(int mobjects[], int numObjects);
void updateMoves(objectHolder_c mobjects);

bool resetPos(object_c &Obj, const object_c &obj2);
void collide(object_c &obj1, const object_c &obj2, touch side);
void collide(object_c &obj1, const object_c &obj2);
void objInteract(object_c &obj1, object_c &obj2);

void oscillate();

void moveShots(object_c *sh);
#endif
