#include <vector3d.h>


#include "world.h"
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

object_c *level1[9];
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


void makeLevel(level_c &level)
{
	switch(level.levelNum)
	{
		case 0:
			level.addBlock(500.0f, 2.0f, 0.0f, -2.0f, tpGROUND, BLOCK1);
			level.lvlObjects[0].wraps.x = 50;
			break;
		case 1:
			level.addBlock(7.0f, .75f, 0.0f, -2.0f, tpGROUND, BLOCK1);//0
			level.addBlock(170.0f, 70.0f, -10.0f, -30.0f, tpGROUND, PORTLAND);//1
			level.addBlock(8.0f, 1.0f, 0.0f, 0.0f, tpGROUND, BLOCK1);//2
			level.addBlock(2.0f, 9.0f, -3.0f, 1.0f, tpGROUND, BLOCK1);//3
			level.addBlock(4.0f, 1.0f, 6.0f, 2.0f, tpGROUND, BLOCK1);
			level.addBlock(6.0f, 1.0f, 13.0f, 1.0f, tpGROUND, BLOCK1);//4
			level.addBlock(2.0f, 16.0f, 21.0f, -5.0f, tpGROUND, BLOCK1);//5
			level.addBlock(6.0f, 1.0f, 17.0f, -5.0f, tpGROUND, BLOCK1);//6
			level.addBlock(6.0f, 1.0f, 13.0f, -6.0f, tpGROUND, BLOCK1);//7
			level.addBlock(8.0f, 1.0f, 4.0f, -6.0f, tpGROUND, BLOCK1);//8
			level.addBlock(7.0f, 1.0f, -4.0f, -8.0f, tpGROUND, BLOCK2);//9
			level.addBlock(2.0f, 4.0f, 1.0f, -10.0f, tpGROUND, BLOCK1);//10
			level.addBlock(8.0f, 1.0f, 4.0f, -16.0f, tpGROUND, BLOCK1);//11
			level.addBlock(10.0f, .50f, 11.0f, -12.0f, tpGROUND, BLOCK1);//12
			level.addBlock(6.0f, .50f, 9.0f, -6.5f, tpGROUND, BLOCK1);//13
			level.addBlock(2.0f, 3.0f, 7.0f, -15.0f, tpGROUND, BLOCK1);//14
			level.addBlock(1.0f, 4.0f, 15.5f, -16.0f, tpGROUND, BLOCK1);//15
			level.addBlock(12.0f, 1.0f, 22.0f, -16.0f, tpGROUND, BLOCK1);//16
			level.addBlock(1.0f, 16.0f, 28.5f, -16.0f, tpGROUND, BLOCK1);//17
			level.addBlock(2.0f, 5.0f, 21.0f, -10.0f, tpGROUND, BLOCK1);//18
			level.addBlock(3.0f, 1.0f, 23.5f, -10.0f, tpGROUND, BLOCK2);//19
			level.addBlock(4.0f, 1.0f, 27.0f, -1.0f, tpGROUND, BLOCK1);//20
			level.addBlock(22.0f, 1.0f, 33.0f, 4.0f, tpGROUND, BLOCK1);//21
			level.addBlock(1.0f, 26.0f, 43.5f, -22.0f, tpGROUND, BLOCK1);//22
			level.addBlock(10.0f, 1.0f, 36.0f, -3.0f, tpGROUND, BLOCK2);//23
			level.addBlock(10.0f, 1.0f, 36.0f, -9.0f, tpGROUND, BLOCK2);//24
			level.addBlock(10.0f, 1.0f, 36.0f, -15.0f, tpGROUND, BLOCK2);//25
			level.addBlock(6.0f, 2.0f, 41.0f, -24.0f, tpGROUND, BLOCK1);//26
			level.addBlock(14.0f, 4.0f, 37.0f, -28.0f, tpGROUND, BLOCK1);//27
			level.addBlock(10.0f, 1.0f, 35.0f, -25.0f, tpGROUND, BLOCK1);//28
			level.addBlock(6.0f, 4.0f, 23.0f, -28.0f, tpGROUND, BLOCK1);//29
			level.addBlock(6.0f, 1.0f, 23.0f, -25.0f, tpGROUND, BLOCK1);//30
			level.addBlock(8.0f, 4.0f, 12.0f, -28.0f, tpGROUND, BLOCK1);//31
			level.addBlock(8.0f, 1.0f, 12.0f, -25.0f, tpGROUND, BLOCK1);//32
			level.addBlock(10.0f, 1.0f, 34.0f, -16.0f, tpGROUND, BLOCK1);//33
			level.addBlock(4.0f, 1.0f, -6.0f, 0.0f, tpGROUND, BLOCK1);//34
			level.addBlock(2.0f, 17.0f, -9.0f, -16.0f, tpGROUND, BLOCK1);//35
			level.addBlock(8.0f, 1.0f, -4.0f, -16.0f, tpGROUND, BLOCK1);//36
			level.addBlock(4.0f, 12.0f, 0.0f, -28.0f, tpGROUND, BLOCK1);//37
			level.addBlock(2.0f, 6.0f, 11.0f, -34.0f, tpGROUND, BLOCK1);//38
			level.addBlock(2.0f, 6.0f, -1.0f, -34.0f, tpGROUND, BLOCK1);//39
			level.addBlock(6.0f, 1.0f, 11.0f, -35.0f, tpGROUND, BLOCK1);//40
			level.addBlock(4.0f, 6.0f, 10.0f, -40.0f, tpGROUND, BLOCK1);//41
			level.addBlock(4.0f, 1.0f, 0.0f, -35.0f, tpGROUND, BLOCK1);//42
			level.addBlock(4.0f, 16.0f, 0.0f, -50.0f, tpGROUND, BLOCK1);//43
			level.addBlock(4.0f, 2.0f, 0.0f, -52.0f, tpGROUND, BLOCK1);//44
			level.addBlock(4.0f, 2.0f, 4.0f, -52.0f, tpGROUND, BLOCK1);//45
			level.addBlock(4.0f, 2.0f, 8.0f, -52.0f, tpGROUND, BLOCK1);//46
			level.addBlock(4.0f, 2.0f, 12.0f, -52.0f, tpGROUND, BLOCK1);//47
			level.addBlock(2.0f, 2.0f, 15.0f, -50.0f, tpGROUND, BLOCK1);//48
			level.addBlock(2.0f, 4.0f, 17.0f, -50.0f, tpGROUND, BLOCK1);//49
			level.addBlock(6.0f, 6.0f, 21.0f, -50.0f, tpGROUND, BLOCK1);//50
			level.addBlock(4.0f, 4.0f, 26.0f, -50.0f, tpGROUND, BLOCK1);//51
			level.addBlock(4.0f, 2.0f, 26.0f, -36.0f, tpGROUND, BLOCK1);//52
			level.addBlock(16.0f, 6.0f, 36.0f, -50.0f, tpGROUND, BLOCK1);//53
			level.addBlock(4.0f, .50f, 38.0f, -44.0f, tpGROUND, BLOCK1);//54
			level.addBlock(4.0f, 1.0f, 42.0f, -44.0f, tpGROUND, BLOCK1);//55
			level.addBlock(30.0f, 2.0f, 29.0f, -52.0f, tpGROUND, BLOCK1);//56

//object_c* water1a = new object_c(12.0f, .50f, "Data/img/watera.tga", 22.0f, -12.0f, tpWATER);//34
//object_c* water1b = new object_c(12.0f, 3.0f, "Data/img/waterb.tga", 22.0f, -15.0f, tpWATER);//35
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

			level.player1Start = Vector2D(0.0f, 4.0f);
			//level.numtgas = 2;
			//level.numMovingObj = 5;
			break;
		case 2:
			level.addBlock(170.0f, 70.0f, -10.0f, -30.0f, tpGROUND, PORTLAND);//0
			level.addBlock(20.0f, 4.0f, 5.0f, -4.0f, tpGROUND, BLOCK1);
			level.addBlock(18.0f, 4.0f, 36.0f, -4.0f, tpGROUND, BLOCK1);
			level.addBlock(4.0f, 1.0f, 2.0f, 31.0f, tpGROUND, BLOCK1);
			level.addBlock(4.0f, 1.0f, 5.0f, 27.0f, tpGROUND, BLOCK1);
			level.addBlock(1.0f, 9.0f, 6.5f, 28.0f, tpGROUND, BLOCK1);
			level.addBlock(1.0f, 1.0f, 8.5f, 0.0f, tpGROUND, BLOCK1);
			level.addBlock(1.0f, 2.0f, 9.5f, 0.0f, tpGROUND, BLOCK1);
			level.addBlock(5.0f, 3.0f, 12.5f, 0.0f, tpGROUND, BLOCK1);
			level.addBlock(2.0f, 1.0f, 26.0f, 3.0f, tpGROUND, BLOCK1);
			level.addBlock(3.0f, 16.0f, 28.5f, 0.0f, tpGROUND, BLOCK1);
			level.addBlock(3.0f, 1.0f, 17.5f, 2.0f, tpGROUND, BLOCK1);
			level.addBlock(3.0f, 1.0f, 22.5f, 5.0f, tpGROUND, BLOCK2);

			/*level.lvlObjects[11] = L2LRBlock;
				level.movingObjIdx[0] = 11;
			level.lvlObjects[12] = L2upDownBlock;
				level.movingObjIdx[1] = 12;*/

			level.numObjects = 13;
			level.solidObjIdx = 1;
			level.player1Start = Vector2D(1.0f, 33.0f);
			level.numtgas = 0;
			break;
		case 3:
			level.addBlock(22.0f, 15.0f, 11.0f, 1.0f, tpGROUND, BLOCK1);
			level.addBlock(22.0f, 2.0f, 11.0f, 0.0f, tpGROUND, BLOCK1);
			level.addBlock(22.0f, 2.0f, 11.0f, 14.0f, tpGROUND, BLOCK1);
			level.addBlock(2.0f, 12.0f, 1.0f, 2.0f, tpGROUND, BLOCK1);
			level.addBlock(2.0f, 12.0f, 21.0f, 2.0f, tpGROUND, BLOCK1);
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
			
			level.solidObjIdx = 1;
			level.player1Start = Vector2D(3.0f, 2.0f);
			level.player2Start = Vector2D(16.0f, 2.0f);
			level.numtgas = 0;
			level.numMovingObj = 0;
			level.is3D = false;
			level.cameraLock = true;
			level.look = Vector3D(11, 8, 0);
			break;
		default:
			break;
			
	}
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

level_c::level_c()
{
	levelNum = 0;
	numPlayers = 0;
	numEnemies = 0;
	is3D = false;
	cameraLock = false;
	playerFocus = 0;
	levelStarted = false;
	
	lvlObjects = new object_c[MAXOBJECTS];
	players = new object_c[MAXPLAYERS];
	enemies = new object_c[MAXENEMIES];
    cameras = new CameraPoints[MAXCAMERAS];
}

level_c::level_c(int lnum)
{
	level_c();
	levelNum = lnum;
}


void level_c::addPlayer(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter)
{
	players[numPlayers] = object_c(wid, hei, xStart, yStart, tpPLAYER, cter);
	players[numPlayers].numPlayer = static_cast<playerNum>(numPlayers++);
	
	return;
}

void level_c::addEnemy(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, character cter)
{
	enemies[numEnemies++] = object_c(wid, hei, xStart, yStart, tpENEMY, cter);
	
	return;
}


void level_c::addBlock(GLfloat wid, GLfloat hei, GLfloat xStart, GLfloat yStart, type tp, block blk)
{
	lvlObjects[numObjects] = object_c(wid, hei, xStart, yStart, tp, blk);
	lvlObjects[numObjects].index = numObjects++;
	
	return;
}

void level_c::setMass(type objType, int index, float mass)
{
	if(objType == tpPLAYER)
		players[index].mass = mass;
	else if(objType == tpENEMY)
		enemies[index].mass = mass;

	return;
}

void level_c::setPos(type objType, int index, Vector2D pos)
{
	if(objType == tpPLAYER)
		players[index].pos = pos;
	else if(objType == tpENEMY)
		enemies[index].pos = pos;

	return;
}

void level_c::setVel(type objType, int index, Vector2D vel)
{
	if(objType == tpPLAYER)
		players[index].vel = vel;
	else if(objType == tpENEMY)
		enemies[index].vel = vel;

	return;
}
	
void level_c::initTextures()
{
	for(int lo=0; lo<numObjects; lo++)
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
	}
	
	return;
}


void level_c::drawWorld()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
	//glLoadIdentity();							// Reset The Current Modelview Matrix
	//gluLookAt(-x, -y, -20, -x, -y, 0.0, 0.0, 1.0, 0.0);
	
	for(int lo=0; lo<numObjects; lo++)
	{
		if(lvlObjects[lo].active)
			lvlObjects[lo].drawRec();
	}
	for(int p=0; p<numPlayers; p++)
	{
		
		if(players[p].active)
		{
			players[p].drawRec();
			if(players[p].objshots != NULL)
			{
				for(int s=0; s<players[p].objshots->numShots; s++)
				{
					if(players[p].objshots->slist[s].active);
						players[p].objshots->slist[s].drawRec();
				}
			}
		}
	}
	for(int e=0; e<numEnemies; e++)
	{
		if(enemies[e].active)
			enemies[e].drawRec();
	}

	return;
}
	
void level_c::runCheckTouch()
{
	int lo=0;
	int p=0;
	int e=0;
	int s=0;

	for(lo=0; lo<numObjects; lo++)
	{
		clearTouches(lvlObjects[lo]);
	}
	for(p=0; p<numPlayers; p++)
	{
		clearTouches(players[p]);
		if(players[p].objshots != NULL)
		{
			for(s=0; s<players[p].objshots->numShots; s++)
				clearTouches(players[p].objshots->slist[s]);
		}
	}
	for(e=0; e<numEnemies; e++)
	{
		clearTouches(enemies[e]);
	}
	for(lo=0; lo<numObjects; lo++)
	{
		//if(lvlObjects[lo].active)
			//checkTouch(lvlObjects[lo]);
	}
	for(p=0; p<numPlayers; p++)
	{
		if(players[p].active)
		{
			checkTouch(players[p], lvlObjects, numObjects, -1);
			checkTouch(players[p], players, numPlayers, p);
			checkTouch(players[p], enemies, numEnemies, -1);
			if(players[p].objshots != NULL)
			{
				for(s=0; s<players[p].objshots->numShots; s++)
					checkTouch(players[p].objshots->slist[s], enemies, numEnemies, -1);
			}
		}			
	}
	for(e=0; e<numEnemies; e++)
	{
		if(enemies[e].active)
		{
			checkTouch(enemies[e], lvlObjects, numObjects, -1);
			checkTouch(enemies[e], players, numPlayers, -1);
			checkTouch(enemies[e], enemies, numEnemies, e);
		} 
	}
	
	return;
}


void level_c::runMoveWorld(GLfloat dt)
{
	for(int lo=0; lo<numObjects; lo++)
	{
		//if(lvlObjects[lo].active)
			//checkTouch(lvlObjects[lo]);
	}
	for(int p=0; p<numPlayers; p++)
	{
		if(players[p].active)
		{
			updatePlayerMove(players[p], dt);
			if(players[p].objshots != NULL)
			{
				for(int s=0; s<players[p].objshots->numShots; s++)
					updateObjectMove(players[p].objshots->slist[s], dt);
			}
		}			
	}
	for(int e=0; e<numEnemies; e++)
	{
		if(enemies[e].active)
		{
			updateEnemyMove(enemies[e],players[0], dt);
		} 
	}
	
	return;
}


void level_c::fixSizes()
{
	//need to add assigntexture call for level objects
	/*for(int lo=0; lo<numObjects; lo++)
	{
		if(lvlObjects[lo].active)
			fixSize(lvlObjects[lo]);
	}*/
	for(int p=0; p<numPlayers; p++)
	{
		if(players[p].active)
		{
			 fixSize(players[p]);
		}			
	}
	for(int e=0; e<numEnemies; e++)
	{
		if(enemies[e].active)
		{
			fixSize(enemies[e]);
		} 
	}
}


Vector3D level_c::setCam(object_c* obj, GLfloat dt)
{
    CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
    CameraPoint* nextcam;
	Vector3D cam2cam, cam2obj, cam2look;
	Vector3D pos, look, alongv, movepos;
	Vector3D objpos;
	GLfloat camdist, objvel, camRotate;
	CameraView view = cameras->camview;

	if(cameras->currentPoint == cameras->numPoints-1)
	{
		nextcam = cam;
	}
	else
		nextcam = &cameras->cpoints[cameras->currentPoint+1];

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
	//glLoadIdentity();												// Reset The Current Modelview Matrix

//TODO	gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x, cam->up.y, cam->up.z);
	cam2look = cam->look - cam->pos;

	return cam2look;
}
	

CameraView level_c::cycleCam()
{
	if(cameras->camview >= NUMCAMVIEWS-1)
		cameras->camview = static_cast<CameraView>(0);
	else
		cameras->camview =  static_cast<CameraView>(cameras->camview + 1);
		
	return cameras->camview;
}
void level_c::run(GLfloat dt, int numRuns)
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
	setCam(&players[playerFocus], dt);

	for(int i=0; i<numRuns; i++)
	{
		if(!cameraMode && !debugMode)
		{
			runCheckTouch();
			if(i == (numRuns -1))
				drawWorld();
			runMoveWorld(dt);
		}
		else
			drawWorld();
	}

	return;
}

game_c::game_c()
{
	numLevels = 0;
	numPlayers = 0;
	currentLevel = NULL;
	players = NULL;
}

game_c::~game_c()
{
	delete currentLevel;
	delete players;
}
