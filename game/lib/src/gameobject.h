#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <math.h>
#include <stdio.h>										// Header File For Standard Input / Output

#include <camera.h>
#include <3dsGT/3dsLoader.h>
#include <mouse.h>
//#include <text.h>
#include <light.h>

#include <menu.h>
#include <object.h>

#define MAXLEVELS 5
#define MAXMENUS 5
#define MAXLIGHTS 10
#define MAXPLAYERS 4

enum gameMode{gmMENU, gmPLAY};

class level
{
public:
	int levelNum;
	bool started;
	GLfloat startTime, currentTime, timer, delta;
	int numPlayers;
	Vector3D playerStart;		//player starting positions
	Vector3D majAxis;
	bool bGravity;
	GLfloat gravityM;
	Vector3D gravityV;
	//int numTextures;
	//messageList msgList;

	level();
	level(int players);

	void setMajAxis(Vector3D axis);
	virtual void run(GLfloat dt);
	//Vector3D setCam(Object* obj, CameraView view);
	void addCamera(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist);
	Vector3D setCam(Vector3D* pos);
	void updateCam();
	void setView(CameraView view);
	//texture_s* addTexture(char *filename, char *ID);
	//texture_s* addTexture(char *filename1, char *filename2, char *ID);
	
	object_holder allObj;
	//Object *player1, *player2;
	//texture_s *alltexture;
	cameraPoints* cameras;
	light_c* lights;
};

class level3ds : public level
{
public:
	C3dsLoader world3ds;
	char mapFileName[50];

	level3ds():level(){}
	level3ds(char* filename);

	void loadmap(GLfloat scale);
	virtual void run(GLfloat dt);
	void run3ds();

};

class gameObj
{
public:
	int numPlayers;
	void* players;
	object_plane* planePlayer;
	Shape playerShape;
	
	int numLevels;
	int currentLevel;
	level3ds levels[MAXLEVELS];
	
	bool paused;
	gameMode gMode;
	int numMenus;
	
	int currentMenu;
	menuTree menus[MAXMENUS];
	
	font_s font;
	font3d_s font3d;
	
	texture_s alltexture[MAXTEXTURE];
	int numTextures;
	
	gameObj();
	~gameObj();
	
	bool addLevel();
	bool addLevel(char* file, Vector3D initCamPos, Vector3D initLookPos, Vector3D upDir, CameraView view);
	bool loadLevel();
	bool unloadLevel();
	texture_s* addTexture(char *filename, char *ID);
	void setPlayerShape(Shape pShape);
	void addPlayer(object_plane *plane);
	void run(mouse_s* ms, void (*commandFcn)(gameObj* gm, mouse_s* ms), GLfloat delta);
	bool addMenu(char* mTitle);
};

#endif
