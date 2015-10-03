#ifndef OBJECTS
#define OBJECTS

#include <qglobal.h>

#include "qtgl.h"

#include <vector3d.h>
//#include "text.h"

enum touch{LSIDE, BSIDE, RSIDE, TSIDE};
enum type{tpPLAYER, tpGROUND, tpENEMY, tpOBJ, tpSHOT, tpWATER, tpBACKGROUND, tpMOVGROUND};
enum character{ZERO, MMX, GOKU, SPIDEY, TAILS, MARIONES, SONIC, CAPEMARIO, PETER, DK, GOOMBA, VECTORMAN, MICHAELANGELO, LIUKANG};
enum playerNum{PLAYER1, PLAYER2};
enum shots{MMXSHOT, GOKUSHOT};
enum block{BLOCK1, BLOCK2, PORTLAND, WATER1};

#define NUMCHARACTERS 14
#define NUMSHOTTYPES 2
#define NUMBLOCKTYPES 4

struct actionTiming
{
	bool started;
	bool done;
	GLfloat startTime;
	GLfloat timeHeld;

	actionTiming()
	{
		started = false;
		done = false;
	}
};

class object_c;

class shotList_c
{
public:
	shotList_c();
	shotList_c(int numS, GLfloat wid, GLfloat hei, shots sType, object_c *pnt);

	object_c* nextShot();
	object_c* lastShot();
	void updateShots();

	int numShots;
	int numActive;
	int numFree;
	GLfloat maxDist;
	object_c* slist;
};

class object_c								// Create A Structure For Our Player
{
    public:
	object_c();
    object_c(GLfloat wid, GLfloat hei, type oType, int ident);		//ident is general identifier for the object type
	object_c(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, type oType, int ident);
	object_c& operator= (object_c obj);
	
	void init();
	void init(GLfloat wid, GLfloat hei, type oType, int ident);
	void drawRec();
	void drawCube();
	bool addShots(int numS, GLfloat wid, GLfloat hei, shots sType);
	bool isTouched();
	
	Vector2D pos, posOld;
	GLfloat posz;								//coord in and out of screen
	Vector2D posMin, posMax;
	Vector2D posMinOld, posMaxOld;
	Vector2D vel, velOld;
	Vector2D accel;
	
	//object physical properties
	GLfloat mass;
	GLfloat elas;
	Vector2D MV;
	GLfloat friction;
	Vector2D mov;								//direction to move in
	
	Vector2D dimension, oDimension;				//[width,height]
	GLfloat diag;
	
	//object attributes
	GLfloat health;
	GLfloat xSpeed, jumpStrength;

	bool canWallClimb;
	bool canShoot;
	bool canRoll;
	bool isSolid;
	bool projectile;

	bool active;
	bool pRight;
	GLfloat dirSign;
	bool isTouching[4];
	int isTouchIndex[4];
	const object_c* touchObj[4];
	bool inFront;
	
	int index;
	object_c* parent;
	shotList_c* objshots;			//dynamic(only created if needed)
	int numShots;

	//animation properties
	GLfloat center;
	Vector2D *scale;				//scaling factors for texture
	GLuint *texture;
	GLfloat *centers;				//center coords for texture
	GLfloat rotate;

	bool animated;					//object is animated
	int animFrame;					//current frame
	GLfloat frameFloat[20];
	bool animationDone[20];
	bool state[20];
	int currentAct;					//current action of object
	bool isAttacking;
	actionTiming actionTime[20];

	character person;
	type objType;
	shots shotType;
	block blkType;
	playerNum numPlayer;

	void calcBoundaries();
	Vector2D wraps;
	Vector2D WrapMove;
	
	char picFile[255];			//picture filename
	char ID[255];
	
	//~object_c();
};


class objectHolder_c
{
	public:
		void setObject(object_c *obj, int index);
		void setObject(object_c *obj);
		object_c* getObject(int index);
		int numObjects;
		
	private:
		object_c* objects[100];
};

void setObject(object_c *obj, int index);
void setObject(object_c *obj);
object_c* getObject(int index);

#endif

