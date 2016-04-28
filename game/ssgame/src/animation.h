#ifndef ANIMATION
#define ANIMATION

//#include <windows.h>								// Header File For Windows
//#include <gl\gl.h>									// Header File For The OpenGL32 Library
//#include <gl\glu.h>

#include <qvector.h>

#include "objects.h"

enum Action{actNONE, actRUN, actATTACK1, actJUMP, actWALL, actFLY, actDUCK, actSHOOT, actBLOCK, actJUMPATK, actJUMPSHOOT, actPUSH, actHURT, actRUNATK};
enum frame{animSTART, numFRAMES, repeatFRAME, animSPEED, lastFRAME, minstopFRAME, canHOLD};

#define DEFFRAMESPEED 10

struct Texture
{
	GLuint ID;
	Vector2D scale;
	GLfloat center;
	GLint size[2];
};

class Animation
{
public:
	Animation();
	Animation(QStringList textureFiles, int mustPassFrame=0, int repeatFrame=0, bool canHold=false, GLfloat speed=DEFFRAMESPEED);

	void setCenters(QVector<GLfloat> centers);

	int numFrames();
	void setSpeed(GLfloat speed);
	void canHold(bool holdable);

private:
	int m_repeatFrame;
	int m_mustPassFrame;
	float m_speed;
	bool m_canHold;

	QVector<Texture> m_textures;
};

#define NUMACTIONS 13
//#define MAXTEXTURES 100
//#define MAXFRAMES


//#define DEFRUNFRAMESPD 17
extern int DEFRUNFRAMESPD;
#define DEFATK1FRAMESPD 120
#define DEFJUMPFRAMESPD 150

#define DEFJUMPSTRENGTH 1.0f
#define DEFMAXSPEED 5.0f

class Animations
{
public:
	Animations();
	int numTextures();
	void setSpeed(Action action, GLfloat speed);
	void setAnimation(Action action, Animation animation);

    QVector<Vector2D> scale;			//scaling factors for texture
	Vector2D pixels;
		//GLfloat hScale[100];
		//int pixelsW;
		//GLfloat wScale[100];
		//int pixelsH;

    QVector<GLuint> textures;
    QVector<GLfloat> centers;			//center coords for texture
	
	int frameData[20][7];			//make sure NUMACTIONS=20
	Animation m_animations[NUMACTIONS];

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
};

extern Animations playerTextures[NUMCHARACTERS];
extern Animations objectTextures[NUMBLOCKTYPES];
extern Animations shotTextures[NUMSHOTTYPES];

void doTextures();
void assignTextures(Object &obj, Animations *animData);
void setDefaults(Animations animData[], int numobjs);	//last frame and minstop frame
bool animate(Object &obj, Action act, const Animations *animData, GLfloat dt);
bool sendAnimation(Object &obj, Action act, GLfloat dt);
void fixSize(Object &animObj);


#endif

