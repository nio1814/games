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

#include "object/plane.h"

#include <QString>

enum gameMode{gmMENU, gmPLAY};

class gameObj
{
    int numLevels();

	int numPlayers;
	void* players;
	object_plane* planePlayer;
	Shape playerShape;
	
    int m_currentLevelIndex;
  std::vector<std::shared_ptr<Level>> levels;
	
	bool paused;
	gameMode gMode;
	int numMenus;
	
	int currentMenu;
	menuTree menus[MAXMENUS];
	
//	font_s font;
//	font3d_s font3d;
	
	texture_s alltexture[MAXTEXTURE];
	int numTextures;
	
public:
	gameObj();
	~gameObj();
	
  bool addMenu(char* mTitle);
    void addLevel(std::shared_ptr<Level> level);
//    bool addLevel(char* file, float scale, Vector3D initCamPos, Vector3D initLookPos, Vector3D upDir, CameraView view);
	bool loadLevel();
  std::shared_ptr<Level> currentLevel();
	bool unloadLevel();
  texture_s* addTexture(char *filename);
	void setPlayerShape(Shape pShape);
	void addPlayer(object_plane *plane);
    void run(Mouse* ms, void (*commandFcn)(gameObj* gm, Mouse* ms), GLfloat delta);
  void render();
};

#endif
