#ifndef GAMEOBJECT
#define GAMEOBJECT

//#include <text.h>
#include <light.h>

#include <menu.h>
#include "level.h"
#include "mouse.h"

#define MAXLEVELS 5
#define MAXMENUS 5
#define MAXLIGHTS 10
#define MAXPLAYERS 4

#include <QString>

enum gameMode{gmMENU, gmPLAY};

class gameObj
{
public:
    int numLevels();
    Level& currentLevel();
    void render();

	int numPlayers;
	void* players;
	object_plane* planePlayer;
	Shape playerShape;
	
    int m_currentLevelIndex;
    QList<Level> levels;
	
	bool paused;
	gameMode gMode;
	int numMenus;
	
	int currentMenu;
	menuTree menus[MAXMENUS];
	
//	font_s font;
//	font3d_s font3d;
	
	texture_s alltexture[MAXTEXTURE];
	int numTextures;
	
	gameObj();
	~gameObj();
	
    bool addLevel(int index);
//    bool addLevel(char* file, float scale, Vector3D initCamPos, Vector3D initLookPos, Vector3D upDir, CameraView view);
	bool loadLevel();
	bool unloadLevel();
  texture_s* addTexture(char *filename);
	void setPlayerShape(Shape pShape);
	void addPlayer(object_plane *plane);
    void run(Mouse* ms, void (*commandFcn)(gameObj* gm, Mouse* ms), GLfloat delta);
	bool addMenu(char* mTitle);
};

#endif
