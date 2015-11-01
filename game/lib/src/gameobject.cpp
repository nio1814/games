#include "gameobject.h"

#include <math.h>
#include <string.h>

#include <keys.h>
#include <3dsGT/3ds.h>
#include <3dsGT/3dsLoader.h>
#include <mouse.h>
#include <constants.h>
#include "texture.h"
#include "masking.h"
#include "level.h"

#include <QTime>

//#include "commands.h"

gameObj::gameObj()
{
	numPlayers = 0;
	players = NULL;
	planePlayer = NULL;
	numMenus = 0;
	currentMenu = -1;
	gMode = gmMENU;
	numTextures = 0;
}

int gameObj::numLevels()
{
    return levels.size();
}

Level &gameObj::currentLevel()
{
    return levels[m_currentLevelIndex];
}

bool gameObj::addLevel(int index)
{
	bool success = false;

    if(numLevels() == 0)
        m_currentLevelIndex = 0;

    Level level;
    if(level.create(index))
//	levels[currentLevel].create(index);
        levels.append(level);

    success = true;
	
	return success;
}

/*bool gameObj::addLevel(char* file, float scale, Vector3D initCamPos, Vector3D initLookPos, Vector3D upDir, CameraView view)
{
	bool success = false;
	
    if(numLevels() == 0)
        m_currentLevelIndex = 0;

    Level level;
    level.mapFileName = file;
    level.cameras->addPoint(initCamPos,initLookPos,upDir,DEFFOLLOWDIST);
    level.cameras->camview = view;
    level.majAxis = upDir;
    level.loadmap(scale);

    levels.append(level);

    success = true;
	
	return success;
}*/

texture_s* gameObj::addTexture(char *filename, char *ID)
{
	bool success = false;
	texture_s* ptr = NULL;
	string errString;

//	success = LoadGLTextures(&alltexture[numTextures++], filename);
//    success = LoadGLTextures(&alltexture[numTextures++].layer[0], filename);
    success = loadGLTexture(&alltexture[numTextures++].layer[0], filename);
	if(success)
		ptr = &alltexture[numTextures-1];
	else
	{
		errString = "Texture file failed to load "+(string)filename;
//		MessageBox(NULL, errString.c_str() , TEXT("Texture Loading"), MB_ICONERROR | MB_OK);
        qErrnoWarning(errString.c_str());
	}

	return ptr;
}

void gameObj::setPlayerShape(Shape pShape)
{
	playerShape = pShape;
	
	switch(pShape)
	{
		case SPHERE:
			players = new object_sphere[MAXPLAYERS];
			break;
		case PLANE:
			players = new object_plane[MAXPLAYERS];
			break;
		default:
			break;
	}
	
	return;
}

void gameObj::addPlayer(object_plane* plane)
{
	setPlayerShape(PLANE);
	planePlayer = static_cast<object_plane*>(plane);
	

	return;
}


void gameObj::run(Mouse *ms, void (*commandFcn)(gameObj *, Mouse *), GLfloat delta)
{
    QTime clock;
    int timeMs = clock.msec();
    QVector3D pos;
    QVector3D look;

	switch(gMode)
	{
		case gmMENU:
			if(numMenus>0)
				glEnable(GL_LIGHTING);

                pos = QVector3D(sin(timeMs/30000.5f)*2.0f*cos(timeMs/30.5f), 0, 11.0f*cos(sin(timeMs/3000.5f)+5.0f));
                look = QVector3D(0, 0, 0);
                glLookAt(pos, look, Y.toQVector3D());		// This determines where the camera's position and view is
//				menus[currentMenu].display();
			if(ms != NULL)
			{
                if(ms->isBtns(Qt::LeftButton))
					gMode = gmPLAY;
			}
            if(isKeys(Qt::Key_Return))
				gMode = gmPLAY;
			break;
        case gmPLAY:
            if(commandFcn!=NULL)
                commandFcn(this, ms);
//            levels[currentLevel].run(delta);
            currentLevel().run(delta);
            break;
        default:
            break;
	}	
	
	return;
}

void gameObj::render()
{
    switch (gMode) {
        case gmMENU:
            menus[currentMenu].display();
            break;
        case gmPLAY:
            currentLevel().draw();
            break;
        default:
            break;
    }
    currentLevel().draw();
}
	
bool gameObj::addMenu(char* mTitle)
{
	bool success = false;
	
	if(numMenus < MAXMENUS)
	{
		menus[numMenus].ID = mTitle;
//		menus[numMenus].font = &font;
//		menus[numMenus].font3d = &font3d;
		numMenus++;
		
		if(currentMenu == -1)
			currentMenu = 0;
	}
	
	return success;
}

gameObj::~gameObj()
{
	//delete players;
	//delete planePlayer;
}
