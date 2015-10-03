#ifndef WORLD
#define WORLD

#include <QtOpenGL/QtOpenGL>

#include <camera.h>

#include "objects.h"

#define MAXLEVELS 5
#define MAXPLAYERS 4
#define MAXENEMIES 50
#define MAXOBJECTS 100
#define MAXCAMERAS 20

extern GLfloat CAMLOOKSPEED;
extern GLfloat CAMMOVESPEED;

class debugger_c
{
public:

	int numParams;
	int current;
	
	GLfloat *params[10];
	char IDs[10][50];
	
	int addParam(char* ID, GLfloat& value);
	int cycleParam(int inc);
	void decreaseParam(GLfloat inc);
	void increaseParam(GLfloat inc);
};
	
struct level_s
{
	int levelNum;
	int numObjects;
	int solidObjIdx;
	int movingObjIdx[10];
	int numMovingObj;
	int numtgas;
	
	bool is3D;
	bool cameraLock;
	
	object_c *lvlObjects[100];
	GLfloat leftScreen, rightScreen, bottomScreen, topScreen;
	Vector2D player1Start, player2Start;
		//GLfloat playerStartX, playerStartY, player2StartX, player2StartY;
	
	double xLook, yLook, zLook;
	
	level_s()
	{
		is3D = true;
		cameraLock = false;
		
		xLook = 0;
		yLook = 0;
		zLook = 0;
	}
};

class level_c
{
public:
	int levelNum;
	int numObjects;
	int numPlayers;
	int numEnemies;
	int solidObjIdx;
	int movingObjIdx[10];
	int numMovingObj;
	int numtgas;
	int playerFocus;
	
	bool is3D;
	bool cameraLock;
	bool levelStarted;
	
	level_c();
	level_c(int lnum);
	void addPlayer(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter);
	void addEnemy(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter);
	void addBlock(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, type tp, block blk);
	void setMass(type objType, int index, float mass);
	void setPos(type objType, int index, Vector2D pos);
	void setVel(type objType, int index, Vector2D vel);
	
	void initTextures();
	void drawWorld();
	void runCheckTouch();
	void runMoveWorld(GLfloat dt);
	Vector3D setCam(object_c* obj, GLfloat dt);
	CameraView cycleCam();
	void run(GLfloat dt, int numRuns);
	void fixSizes();

	GLfloat startTime, currentTime, timer;
	GLfloat leftScreen, rightScreen, bottomScreen, topScreen;
	Vector2D player1Start, player2Start;
	Vector3D look;
	
	object_c *lvlObjects;
	object_c *players;
	object_c *enemies;
    CameraPoints* cameras;
};

class game_c
{
public:
	int numPlayers;
	int playerFocus;
	int numLevels;
	level_c levels[MAXLEVELS];

	game_c();
	~game_c();

	bool addLevel();
	bool loadLevel();
	bool addPlayer();

	object_c *players;
	level_c *currentLevel;
};

extern object_c *level1[9];
extern object_c *level2[10];
extern int level1Objs;


void makeLevel(level_s &level);
void makeLevel(level_c &level);
void drawLevel(level_s &level);
void drawLevel3d(level_s &level);
void setMovingObj(int levelNum);

#endif
