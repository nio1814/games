#include <vector3d.h>


#include "level.h"
#include "movement.h"
#include "objects.h"
#include "masking.h"
//#include "TGA.h"
#include "math.h"
//#include "text.h"
#include "camera.h"
#include "tga.h"

#include <QTime>

#include <string.h>
#include <stdio.h>

Object *level1[9];
GLuint gestureBlockTexture[1];
GLuint portlandBackTexture[1];
GLuint crystalTexture[1];
GLuint wateraTexture[1];
GLuint waterbTexture[1];
GLuint desertTexture[1];
GLuint underworldTexture[1];

Vector3D majAxis = Vector3D(0,1,0);
GLfloat CAMLOOKSPEED = 50.0f;
GLfloat CAMMOVESPEED = 3.0f;

int level1Objs = 10;

int movingObj[] = {9};
int numMovingObj = 1;

void makeLevel(level_s &level)
{
    LoadGLTextures(gestureBlockTexture, "Data/Gesture.bmp");
	LoadGLTextures(portlandBackTexture, "Data/port.bmp");
	LoadGLTextures(crystalTexture, "Data/Crystal.bmp");
	TGA_Texture(wateraTexture, "Data/img/watera2.tga", 0);
	TGA_Texture(waterbTexture, "Data/img/waterb2.tga", 0);
	LoadGLTextures(desertTexture, "Data/img/background/desert.bmp");
	LoadGLTextures(underworldTexture, "Data/img/ground/marioUnderground.bmp");


	switch(level.levelNum)
	{
		case 1:
			break;
		default:
			break;
			
	}

	return;
}

bool Level::started()
{
    return levelStarted;
}

bool Level::create(int index)
{
    /*loadGLTexture(gestureBlockTexture, ":img/Gesture.bmp");
    loadGLTexture(portlandBackTexture, ":img/port.bmp");
    loadGLTexture(crystalTexture, ":img/Crystal.bmp");
    TGA_Texture(wateraTexture, "Data/img/watera2.tga", 0);
    TGA_Texture(waterbTexture, "Data/img/waterb2.tga", 0);
    LoadGLTextures(desertTexture, "Data/img/background/desert.bmp");
    LoadGLTextures(underworldTexture, "Data/img/ground/marioUnderground.bmp");*/

    bool status = false;
    m_index = index;
    int objectIndex;
    Object obj;
    switch (index) {
        case 0:
            obj = addBlock(500.0f, 2.0f, 0.0f, -2.0f, tpGROUND, BLOCK1);
            obj.wraps.x = 50;
		cameras.addPoint(Vector3D(0,0,5), Vector3D(0,0,0), Vector3D(0,1,0), 6);
            break;
        case 1:
		cameras.addPoint(Vector3D(0,0,5), Vector3D(0,0,0), Vector3D(0,1,0), 6);
            addBlock(7.0f, .75f, 0.0f, -2.0f, tpGROUND, BLOCK1);//0
            addBlock(170.0f, 70.0f, -10.0f, -30.0f, tpGROUND, PORTLAND);//1
            addBlock(8.0f, 1.0f, 0.0f, 0.0f, tpGROUND, BLOCK1);//2
            addBlock(2.0f, 9.0f, -3.0f, 1.0f, tpGROUND, BLOCK1);//3
            addBlock(4.0f, 1.0f, 6.0f, 2.0f, tpGROUND, BLOCK1);
            addBlock(6.0f, 1.0f, 13.0f, 1.0f, tpGROUND, BLOCK1);//4
            addBlock(2.0f, 16.0f, 21.0f, -5.0f, tpGROUND, BLOCK1);//5
            addBlock(6.0f, 1.0f, 17.0f, -5.0f, tpGROUND, BLOCK1);//6
            addBlock(6.0f, 1.0f, 13.0f, -6.0f, tpGROUND, BLOCK1);//7
            addBlock(8.0f, 1.0f, 4.0f, -6.0f, tpGROUND, BLOCK1);//8
            addBlock(7.0f, 1.0f, -4.0f, -8.0f, tpGROUND, BLOCK2);//9
            addBlock(2.0f, 4.0f, 1.0f, -10.0f, tpGROUND, BLOCK1);//10
            addBlock(8.0f, 1.0f, 4.0f, -16.0f, tpGROUND, BLOCK1);//11
            addBlock(10.0f, .50f, 11.0f, -12.0f, tpGROUND, BLOCK1);//12
            addBlock(6.0f, .50f, 9.0f, -6.5f, tpGROUND, BLOCK1);//13
            addBlock(2.0f, 3.0f, 7.0f, -15.0f, tpGROUND, BLOCK1);//14
            addBlock(1.0f, 4.0f, 15.5f, -16.0f, tpGROUND, BLOCK1);//15
            addBlock(12.0f, 1.0f, 22.0f, -16.0f, tpGROUND, BLOCK1);//16
            addBlock(1.0f, 16.0f, 28.5f, -16.0f, tpGROUND, BLOCK1);//17
            addBlock(2.0f, 5.0f, 21.0f, -10.0f, tpGROUND, BLOCK1);//18
            addBlock(3.0f, 1.0f, 23.5f, -10.0f, tpGROUND, BLOCK2);//19
            addBlock(4.0f, 1.0f, 27.0f, -1.0f, tpGROUND, BLOCK1);//20
            addBlock(22.0f, 1.0f, 33.0f, 4.0f, tpGROUND, BLOCK1);//21
            addBlock(1.0f, 26.0f, 43.5f, -22.0f, tpGROUND, BLOCK1);//22
            addBlock(10.0f, 1.0f, 36.0f, -3.0f, tpGROUND, BLOCK2);//23
            addBlock(10.0f, 1.0f, 36.0f, -9.0f, tpGROUND, BLOCK2);//24
            addBlock(10.0f, 1.0f, 36.0f, -15.0f, tpGROUND, BLOCK2);//25
            addBlock(6.0f, 2.0f, 41.0f, -24.0f, tpGROUND, BLOCK1);//26
            addBlock(14.0f, 4.0f, 37.0f, -28.0f, tpGROUND, BLOCK1);//27
            addBlock(10.0f, 1.0f, 35.0f, -25.0f, tpGROUND, BLOCK1);//28
            addBlock(6.0f, 4.0f, 23.0f, -28.0f, tpGROUND, BLOCK1);//29
            addBlock(6.0f, 1.0f, 23.0f, -25.0f, tpGROUND, BLOCK1);//30
            addBlock(8.0f, 4.0f, 12.0f, -28.0f, tpGROUND, BLOCK1);//31
            addBlock(8.0f, 1.0f, 12.0f, -25.0f, tpGROUND, BLOCK1);//32
            addBlock(10.0f, 1.0f, 34.0f, -16.0f, tpGROUND, BLOCK1);//33
            addBlock(4.0f, 1.0f, -6.0f, 0.0f, tpGROUND, BLOCK1);//34
            addBlock(2.0f, 17.0f, -9.0f, -16.0f, tpGROUND, BLOCK1);//35
            addBlock(8.0f, 1.0f, -4.0f, -16.0f, tpGROUND, BLOCK1);//36
            addBlock(4.0f, 12.0f, 0.0f, -28.0f, tpGROUND, BLOCK1);//37
            addBlock(2.0f, 6.0f, 11.0f, -34.0f, tpGROUND, BLOCK1);//38
            addBlock(2.0f, 6.0f, -1.0f, -34.0f, tpGROUND, BLOCK1);//39
            addBlock(6.0f, 1.0f, 11.0f, -35.0f, tpGROUND, BLOCK1);//40
            addBlock(4.0f, 6.0f, 10.0f, -40.0f, tpGROUND, BLOCK1);//41
            addBlock(4.0f, 1.0f, 0.0f, -35.0f, tpGROUND, BLOCK1);//42
            addBlock(4.0f, 16.0f, 0.0f, -50.0f, tpGROUND, BLOCK1);//43
            addBlock(4.0f, 2.0f, 0.0f, -52.0f, tpGROUND, BLOCK1);//44
            addBlock(4.0f, 2.0f, 4.0f, -52.0f, tpGROUND, BLOCK1);//45
            addBlock(4.0f, 2.0f, 8.0f, -52.0f, tpGROUND, BLOCK1);//46
            addBlock(4.0f, 2.0f, 12.0f, -52.0f, tpGROUND, BLOCK1);//47
            addBlock(2.0f, 2.0f, 15.0f, -50.0f, tpGROUND, BLOCK1);//48
            addBlock(2.0f, 4.0f, 17.0f, -50.0f, tpGROUND, BLOCK1);//49
            addBlock(6.0f, 6.0f, 21.0f, -50.0f, tpGROUND, BLOCK1);//50
            addBlock(4.0f, 4.0f, 26.0f, -50.0f, tpGROUND, BLOCK1);//51
            addBlock(4.0f, 2.0f, 26.0f, -36.0f, tpGROUND, BLOCK1);//52
            addBlock(16.0f, 6.0f, 36.0f, -50.0f, tpGROUND, BLOCK1);//53
            addBlock(4.0f, .50f, 38.0f, -44.0f, tpGROUND, BLOCK1);//54
            addBlock(4.0f, 1.0f, 42.0f, -44.0f, tpGROUND, BLOCK1);//55
            addBlock(30.0f, 2.0f, 29.0f, -52.0f, tpGROUND, BLOCK1);//56
            //Object* water1a = new Object(12.0f, .50f, "Data/img/watera.tga", 22.0f, -12.0f, tpWATER);//34
            //Object* water1b = new Object(12.0f, 3.0f, "Data/img/waterb.tga", 22.0f, -15.0f, tpWATER);//35
                        //level.addBlock(12.0f, .50f, 22.0f, -12.0f, tpWATER, WATER1);//57
                        //level.addBlock(12.0f, 3.0f, 22.0f, -15.0f, tpWATER, WATER1);//58

                        /*level.lvlObjects[57] = water1b;
                        level.lvlObjects[57]->texture = waterbTexture;
                            water1b->isSolid = false;
                            water1b->inFront = true;
                            //water1b.
                        level.lvlObjects[58] = water1a;
                        level.lvlObjects[58]->texture = wateraTexture;
                            water1a->isSolid = false;
                            water1a->inFront = true;
                        */

		  //    addEnemy(1.5f, 2.25f,13.0f, 8.0f, MMX);
		  //    addEnemy(1.75f, 2.75f,4.0f, -4.0f, GOKU);
		  //    addEnemy(3.00f, 1.97f, 23.0f, 24.0f, SPIDEY);
		  //    addEnemy(1.00f, 1.5f, 23.0f, 24.0f, TAILS);
		  //    addEnemy(.70f, .70f, 12.0f, -24.0f, GOOMBA);
			 addEnemy(.70f, .70f, 23.0f, -24.0f, GOOMBA);
		  //    addEnemy(.70f, .70f, 34.0f, -24.0f, GOOMBA);

                        player1Start = Vector2D(0.0f, 4.0f);
                        //level.numtgas = 2;
                        //level.numMovingObj = 5;
                        break;
                    case 2:
                        addBlock(170.0f, 70.0f, -10.0f, -30.0f, tpGROUND, PORTLAND);//0
                        addBlock(20.0f, 4.0f, 5.0f, -4.0f, tpGROUND, BLOCK1);
                        addBlock(18.0f, 4.0f, 36.0f, -4.0f, tpGROUND, BLOCK1);
                        addBlock(4.0f, 1.0f, 2.0f, 31.0f, tpGROUND, BLOCK1);
                        addBlock(4.0f, 1.0f, 5.0f, 27.0f, tpGROUND, BLOCK1);
                        addBlock(1.0f, 9.0f, 6.5f, 28.0f, tpGROUND, BLOCK1);
                        addBlock(1.0f, 1.0f, 8.5f, 0.0f, tpGROUND, BLOCK1);
                        addBlock(1.0f, 2.0f, 9.5f, 0.0f, tpGROUND, BLOCK1);
                        addBlock(5.0f, 3.0f, 12.5f, 0.0f, tpGROUND, BLOCK1);
                        addBlock(2.0f, 1.0f, 26.0f, 3.0f, tpGROUND, BLOCK1);
                        addBlock(3.0f, 16.0f, 28.5f, 0.0f, tpGROUND, BLOCK1);
                        addBlock(3.0f, 1.0f, 17.5f, 2.0f, tpGROUND, BLOCK1);
                        addBlock(3.0f, 1.0f, 22.5f, 5.0f, tpGROUND, BLOCK2);

                        /*level.lvlObjects[11] = L2LRBlock;
                            level.movingObjIdx[0] = 11;
                        level.lvlObjects[12] = L2upDownBlock;
                            level.movingObjIdx[1] = 12;*/

//                        numObjects = 13;
                        solidObjIdx = 1;
                        player1Start = Vector2D(1.0f, 33.0f);
                        numtgas = 0;
                        break;
                    case 3:
                        addBlock(22.0f, 15.0f, 11.0f, 1.0f, tpGROUND, BLOCK1);
                        addBlock(22.0f, 2.0f, 11.0f, 0.0f, tpGROUND, BLOCK1);
                        addBlock(22.0f, 2.0f, 11.0f, 14.0f, tpGROUND, BLOCK1);
                        addBlock(2.0f, 12.0f, 1.0f, 2.0f, tpGROUND, BLOCK1);
                        addBlock(2.0f, 12.0f, 21.0f, 2.0f, tpGROUND, BLOCK1);
                        /*level.lvlObjects[0] = L3bground;
                        level.lvlObjects[0]->texture = desertTexture;
                        level.lvlObjects[1] = L3block1;
                        level.lvlObjects[1]->texture = underworldTexture;
                        level.lvlObjects[2] = L3block2;
                        level.lvlObjects[2]->texture = underworldTexture;
                        level.lvlObjects[3] = L3block3;
                        level.lvlObjects[3]->texture = underworldTexture;
                        level.lvlObjects[4] = L3block4;
                        level.lvlObjects[4]->texture = underworldTexture;*/

                        solidObjIdx = 1;
                        player1Start = Vector2D(3.0f, 2.0f);
                        player2Start = Vector2D(16.0f, 2.0f);
                        numtgas = 0;
                        numMovingObj = 0;
                        is3D = false;
                        cameraLock = true;
                        look = Vector3D(11, 8, 0);
                        break;
        default:
            status = true;
            break;
    }

    addPlayer(1.5f, 2.25f,0.0f, 14.0f, MMX);
//    addEnemy(1.5f, 2.25f,13.0f, 8.0f, MMX);
//    addEnemy(1.75f, 2.75f,4.0f, -4.0f, GOKU);
//    addEnemy(3.00f, 1.97f, 23.0f, 24.0f, SPIDEY);
//    addEnemy(1.00f, 1.5f, 23.0f, 24.0f, TAILS);
//    addEnemy(.70f, .70f, 12.0f, -24.0f, GOOMBA);
//    addEnemy(.70f, .70f, 23.0f, -24.0f, GOOMBA);
//    addEnemy(.70f, .70f, 34.0f, -24.0f, GOOMBA);

    return status;
}

void drawLevel(level_s &level)
{
	static bool backDrawn = false;
	int xWraps = level.lvlObjects[0]->wraps.x;		//conversion might fail
	if(!backDrawn)
	{
	//glTranslatef(0.0f,0.0f,-2.0f);	
		glBindTexture(GL_TEXTURE_2D, level.lvlObjects[0]->texture[0]);				// Select A Texture Based On filter
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);						// Draw A Quad
			glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
			glTexCoord2f(0.0f,1.0f);glVertex3f(level.lvlObjects[0]->posMin.x , level.lvlObjects[0]->posMax.y, -4.0f);				// Top Left
			glTexCoord2f(xWraps,1.0f);glVertex3f(level.lvlObjects[0]->posMax.x , level.lvlObjects[0]->posMax.y, -4.0f);				// Top Right
			glTexCoord2f(xWraps,0.0f);glVertex3f(level.lvlObjects[0]->posMax.x , level.lvlObjects[0]->posMin.y, -4.0f);				// Bottom Right
			glTexCoord2f(0.0f,0.0f);glVertex3f(level.lvlObjects[0]->posMin.x , level.lvlObjects[0]->posMin.y, -4.0f);				// Bottom Left
		glEnd();
	//glTranslatef(0.0f,0.0f, 2.0f);
		glDisable(GL_TEXTURE_2D);
		
		if(light)
			glEnable(GL_LIGHTING);
		
		setMovingObj(level.levelNum);
	

		for(int j=0; j < level.numMovingObj; j++)
		{
			level.lvlObjects[level.movingObjIdx[j]]->calcBoundaries();
		}
	}	
	
	//if(level.is3D)
	//{
		glTranslatef(0.0f,0.0f, -depth);
		for(int i=1; i<level.numObjects; i++)
		{
			if( (level.lvlObjects[i]->inFront == backDrawn) && (level.lvlObjects[i]->inFront != true) )
				level.lvlObjects[i]->drawRec();
		}

		glTranslatef(0.0f,0.0f, 2*depth);
	//}
	
	for(int l=1; l<level.numObjects; l++)
	{
		if(level.lvlObjects[l]->inFront == backDrawn)
			level.lvlObjects[l]->drawRec();
	}
	
	//if(level.is3D)
		glTranslatef(0.0f,0.0f, -depth);


	backDrawn = !backDrawn;

	return;
}


void drawLevel3d(level_s &level)
{
	for(int i=1; i<level.numObjects; i++)
	{
			level.lvlObjects[i]->drawCube();
	}

	return;
}

void setMovingObj(int levelNum)
{

	/*switch(levelNum)
	{
	case 1:
		upDownBlock->pos.y = 4.5f * sin(1.5f*GetTickCount()*.001f) - 10.0f;
		water1a->WrapMove.x += .005f;
		if(getObject(0)->isTouchIndex[BSIDE] == touchUpBlock->index)
		{
			touchUpBlock->vel.y +=.0005f;
			touchUpBlock->pos.y += touchUpBlock->vel.y;
			//AllObjects[0]->yOld = AllObjects[0]->y = touchUpBlock.y + touchUpBlock.height;
		}
		else
			touchUpBlock->vel.y = .0f;
		LR1Block->pos.x = 2.0f * sin(1.5f*GetTickCount()*.001f) + 36.0f;
		LR2Block->pos.x = 2.0f * -sin(1.85f*GetTickCount()*.001f+.3) + 36.0f;
		LR3Block->pos.x = 2.0f * cos(2.15f*GetTickCount()*.001f) + 36.0f;

		break;
	case 2:
		L2LRBlock->pos.x = 3.5f*sin(GetTickCount()*.001f) + 21.0f;
		L2upDownBlock->pos.y = 3.0f*cos(GetTickCount()*.001f) + 8.0f;
		break;
	}*/

	return;
}


int debugger_c::addParam(char* ID, GLfloat& value)
{
	params[numParams] = &value;
	strcpy(IDs[numParams], ID);
	
	return numParams++;
}


void debugger_c::decreaseParam(GLfloat inc)
{
	*params[current] -= inc;
	return;
}


void debugger_c::increaseParam(GLfloat inc)
{
	*params[current] += inc;
	return;
}


int debugger_c::cycleParam(int inc)
{
	current += inc;
	
	if(current < 0)
		current += numParams;
	else if(current >= numParams)
		current -= numParams;
	
	return current;
}

Level::Level()
{
    m_index = -1;
	is3D = false;
	cameraLock = false;
	levelStarted = false;

//    cameras = new CameraPoints[MAXCAMERAS];
}

Level::Level(int index)
{
    Level();
    m_index = index;

    create(index);
}



void Level::addPlayer(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter)
{
    int index = m_objects.size();

    m_objects.append(new Object(wid, hei, xStart, yStart, tpPLAYER, cter));
    m_objects[index]->numPlayer = static_cast<playerNum>(numPlayers());

    if(m_playerIdx.size()==0)
        this->playerFocusIndex = 0;
    m_playerIdx.append(index);
	
	return;
}

ObjectPointer Level::getPlayer(int index)
{
    return m_objects[m_playerIdx[index]];
}

ObjectPointer Level::getEnemy(int index)
{
    return m_objects[m_enemyIndices[index]];
}

ObjectPointer Level::getStructure(int index)
{
    return m_objects[m_structureIdx[index]];
}

ObjectList Level::structures()
{
    ObjectList objs;

    ObjectList::iterator o;
    for(o=m_objects.begin(); o!=m_objects.end(); o++)
    {
        if ((*o)->type!=tpENEMY && (*o)->type!=tpPLAYER)
            objs.append(*o);
    }
    return objs;
}

ObjectList Level::players()
{
    ObjectList objs;

    for(int n=0; n<numPlayers(); n++)
    {
        ObjectPointer obj = m_objects[m_playerIdx[n]];
        if (obj->type==tpPLAYER)
            objs.append(obj);
    }
    return objs;
}

ObjectList Level::enemies()
{
    ObjectList objs;

    for(int n=0; n<numEnemies(); n++)
    {
        ObjectPointer obj = m_objects[m_enemyIndices[n]];
        if (obj->type==tpENEMY)
            objs.append(obj);
    }
    return objs;
}

void Level::addEnemy(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter)
{
    int index = m_objects.size();

    m_objects.append(new Object(wid, hei, xStart, yStart, tpENEMY, cter));
    m_enemyIndices.append(index);

	return;
}


Object& Level::addBlock(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, type tp, block blk)
{
    int index = m_objects.size();

    m_objects.append(new Object(wid, hei, xStart, yStart, tp, blk));
//	lvlObjects[numObjects].index = numObjects++;
    m_structureIdx.append(index);
	
    return *m_objects[index];
}

int Level::objectIndex(type objType, int index)
{
    int objectIdx;
    switch(objType)
    {
        case tpPLAYER:
            objectIdx = m_playerIdx[index];
            break;
        case tpENEMY:
            objectIdx = m_enemyIndices[index];
            break;
        default:
            qWarning() << "Invalid object type: " << objType;
    }

	return objectIdx;
}

void Level::setMass(type objType, int index, float mass)
{
    int objIdx = objectIndex(objType,index);
    m_objects[objIdx]->mass = mass;

	return;
}

void Level::setPos(type objType, int index, Vector2D pos)
{
    int objIdx = objectIndex(objType, index);

    m_objects[objIdx]->pos = pos;

	return;
}

void Level::setVel(type objType, int index, Vector2D vel)
{
    int objIdx = objectIndex(objType, index);

    m_objects[objIdx]->vel = vel;

	return;
}
	
void Level::initTextures()
{
    /*for(int lo=0; lo<numObjects; lo++)
	{
		assignTextures(lvlObjects[lo], objectTextures[lvlObjects[lo].blkType]);
	}
	for(int p=0; p<numPlayers; p++)
	{
		assignTextures(players[p], playerTextures[players[p].person]);
	}
	for(int e=0; e<numEnemies; e++)
	{
		assignTextures(enemies[e], playerTextures[enemies[e].person]);
    }*/
	for(int n=0; n<numObjects(); n++)
	{
		ObjectPointer obj = m_objects[n];
		switch (m_objects[n]->type)
		{
			case tpPLAYER:
			case tpENEMY:
				assignTextures(*obj, &playerTextures[obj->person]);
				break;
			default:
				assignTextures(*obj, &objectTextures[obj->blkType]);
		}
	}
	
	return;
}

int Level::numStructures()
{
    return m_structureIdx.size();
}

int Level::numObjects()
{
    return m_objects.size();
}

int Level::numPlayers()
{
    return m_playerIdx.size();
}

int Level::numEnemies()
{
    return m_enemyIndices.size();
}

void Level::draw()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
	//glLoadIdentity();							// Reset The Current Modelview Matrix
	//gluLookAt(-x, -y, -20, -x, -y, 0.0, 0.0, 1.0, 0.0);
    setCam(getPlayer(this->playerFocusIndex), 0);

    for(int s=0; s<numStructures(); s++)
    {
        ObjectPointer structure = getStructure(s);
        if(structure->active)
//            structure->drawRec();
		   structure->drawCube();
	}
    for(int p=0; p<numPlayers(); p++)
    {
        ObjectPointer player = getPlayer(p);
        if(player->active)
		{
            player->drawRec();
            if(player->objshots != NULL)
			{
                for(int s=0; s<player->objshots->numShots; s++)
				{
                    if(player->objshots->slist[s].active);
                        player->objshots->slist[s].drawRec();
				}
			}
		}
	}
    for(int e=0; e<numEnemies(); e++)
	{
        ObjectPointer enemy = getEnemy(e);
        if(enemy->active)
            enemy->drawRec();
	}

	return;
}
	
void Level::runCheckTouch()
{
	int lo=0;
	int p=0;
	int e=0;
	int s=0;

    for(int n=0; n<numObjects(); n++)
	{
        Object* obj = m_objects[n];
        clearTouches(*obj);
        if(obj->type==tpPLAYER && (obj->objshots != NULL))
        {
            for(int s=0; s<obj->objshots->numShots; s++)
                clearTouches(obj->objshots->slist[s]);
        }
	}

    /*for(lo=0; lo<numObjects; lo++)
	{
		//if(lvlObjects[lo].active)
			//checkTouch(lvlObjects[lo]);
    }*/
    for(p=0; p<numPlayers(); p++)
	{
        ObjectPointer player = getPlayer(p);
        if(player->active)
		{
            checkTouch(*player, structures(), numObjects(), -1);
            checkTouch(*player, players(), numPlayers(), p);
            checkTouch(*player, enemies(), numEnemies(), -1);
            if(player->objshots != NULL)
			{
                for(s=0; s<player->objshots->numShots; s++)
                    checkTouch(player->objshots->slist[s], enemies(), numEnemies(), -1);
			}
		}			
	}
    for(e=0; e<numEnemies(); e++)
	{
        ObjectPointer enemy = getEnemy(e);
        if(enemy->active)
		{
            checkTouch(*enemy, structures(), numObjects(), -1);
            checkTouch(*enemy, players(), numPlayers(), -1);
            checkTouch(*enemy, enemies(), numEnemies(), e);
		} 
	}
	
	return;
}


void Level::runMoveWorld(GLfloat dt)
{
    /*for(int lo=0; lo<numObjects; lo++)
	{
		//if(lvlObjects[lo].active)
			//checkTouch(lvlObjects[lo]);
    }*/
    for(int p=0; p<numPlayers(); p++)
	{
        ObjectPointer player = getPlayer(p);
        if(player->active)
		{
            updatePlayerMove(*player, dt);
            if(player->objshots != NULL)
			{
                for(int s=0; s<player->objshots->numShots; s++)
                    updateObjectMove(player->objshots->slist[s], dt);
			}
		}			
	}
  for(int enemyIndex : m_enemyIndices)
	{
        ObjectPointer enemy = m_objects[enemyIndex];
        if(enemy->active)
		{
            updateEnemyMove(*enemy,*getPlayer(0), dt);
		} 
	}
	
	return;
}


void Level::fixSizes()
{
	//need to add assigntexture call for level objects
	/*for(int lo=0; lo<numObjects; lo++)
	{
		if(lvlObjects[lo].active)
			fixSize(lvlObjects[lo]);
	}*/
    ObjectList::iterator o;
    for (o=m_objects.begin(); o!=m_objects.end(); o++)
    {
        if (((*o)->type==tpPLAYER || (*o)->type==tpPLAYER) && (*o)->active)
        {
            fixSize(**o);
        }
    }
    /*for(int p=0; p<numPlayers(); p++)
	{
		if(players[p].active)
		{
			 fixSize(players[p]);
		}			
	}
    for(int e=0; e<numEnemies(); e++)
	{
		if(enemies[e].active)
			fixSize(enemies[e]);
    }*/
}


Vector3D Level::setCam(Object* obj, GLfloat dt)
{
	Vector3D cam2look;
	if(cameras.numPoints())
	{
	    CameraPoint* cam = &cameras.points[cameras.currentIndex];
	    CameraPoint* nextcam;
		Vector3D cam2cam, cam2obj;
		Vector3D pos, look, alongv, movepos;
		Vector3D objpos;
		GLfloat camdist, objvel, camRotate;
		CameraView view = cameras.camview;

		if(cameras.currentIndex == cameras.numPoints()-1)
		{
			nextcam = cam;
		}
		else
			nextcam = &cameras.points[cameras.currentIndex+1];

		objpos = obj->pos;
		objvel = obj->vel.length();
		cam2obj = objpos - cam->pos;

		switch(view)
		{
			case DEBUGMODE:
				glTranslatef(0.0f, 0.0f, -5.1f);
	//			glPrint(3,10,"Debug Mode",1);
				glTranslatef(0.0f, 0.0f,5.1f);
			case FOLLOW:
			  cam->look += (objpos - cam->pos)*CAMLOOKSPEED*dt;
				cam->pos += ((objpos + Vector3D(0,0,cam->followDist)) - cam->pos)*CAMMOVESPEED*dt;	//need to work on z distance
				break;
			case LOCKED:
				cam->look += (objpos - cam->pos)*CAMLOOKSPEED*dt;
				break;
			case CAMERAMODE:
				glTranslatef(0.0f, 0.0f, -5.1f);
	//			glPrint(3,4,"Camera Mode",1);
				glTranslatef(0.0f, 0.0f,5.1f);
				break;
			default:
				break;
		}


		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
	//    glLoadIdentity();												// Reset The Current Modelview Matrix

	//TODO	gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x, cam->up.y, cam->up.z);
	    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());
		cam2look = cam->look - cam->pos;
	}

	return cam2look;
}
	

CameraView Level::cycleCam()
{
	if(cameras.camview >= NUMCAMVIEWS-1)
		cameras.camview = static_cast<CameraView>(0);
	else
		cameras.camview =  static_cast<CameraView>(cameras.camview + 1);
		
	return cameras.camview;
}

void Level::run(GLfloat dt, int numRuns)
{
    QTime clock;
	char timetext[100];
	
	if(!levelStarted)
	{
    levelStarted = true;
        startTime = clock.msec();
		currentTime = startTime;
	}
	else
	{
        currentTime = clock.msec();
		timer = (currentTime-startTime)/1000;
		sprintf(timetext, "%.2f", timer);
	}
	fixSizes();
    setCam(getPlayer(this->playerFocusIndex), dt);

	for(int i=0; i<numRuns; i++)
	{
		if(!cameraMode && !debugMode)
		{
			runCheckTouch();
//			if(i == (numRuns -1))
//                draw();
      runMoveWorld(dt);
		}
//		else
//            draw();
	}

	return;
}

