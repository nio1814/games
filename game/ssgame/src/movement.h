#ifndef	MOVEMENT
#define MOVEMENT

#include "animation.h"
#include "objects.h"
#include "level.h"

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

void checkTouch(Object &moveObj, const Object &obj2);
void checkTouch(Object &moveObj, level_s level);
void checkTouch(int mobjects[], int numObjects, const level_s &level);
void checkTouch(objectHolder_c mobjects, const level_s &level);
void checkTouch(Object &moveObj, ObjectList objs, int nobjs, int nocheck);

bool touchExists(const Object &moveObj, const Object &obj2);
void clearTouches(Object &obj);
void clearStates(Object &obj);

void updatePlayerMove(Object &moveObj, GLfloat dt);
void updateObjectMove(Object &moveObj, GLfloat dt);
void updateEnemyMove(Object &moveObj, const Object &target, GLfloat dt);
Action runEnemyAI(Object &thisEnemy, const Object &target);
void updateMoves(int mobjects[], int numObjects);
void updateMoves(objectHolder_c mobjects);

bool resetPos(Object &Obj, const Object &obj2);
void collide(Object &obj1, const Object &obj2, touch side);
void collide(Object &obj1, const Object &obj2);
void objInteract(Object &obj1, Object &obj2);

void oscillate();

void moveShots(Object  *sh);
#endif
