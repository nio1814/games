//#include <windows.h>								// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
//#include <gl\gl.h>								// Header File For The OpenGL32 Library
//#include <gl\glu.h>
#include <math.h>

#include "movement.h"
#include "objects.h"
#include "playerkeys.h"
#include "functions.h"
#include "level.h"
#include "animation.h"
#include "sound.h"

#include <QTime>

GLfloat	xrot;									// X Rotation
GLfloat	yrot;									// Y Rotation
GLfloat xspeed;									// X Rotation Speed
GLfloat yspeed;									// Y Rotation Speed
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat depth = 2.0f;
GLfloat leftScreen, rightScreen; 
GLfloat bottomScreen = -6.0f;
GLfloat topScreen = 4.5f;
GLfloat acceleration = -9.0f;
GLfloat timeStep = .025f;

GLfloat XSCALE = 35.0f;
GLfloat GROUNDFRIC = 9.0f;
GLfloat WALLFRIC = 4.0f;
GLfloat airFric = 0.0f;
GLfloat COASTFAC = 0.1f;					//continuing xspeed while in air
GLfloat DUCKFRICFACTOR = 2.0f;
GLfloat RUNFRICFACTOR = 0.01f;
GLfloat AIRMOVEFACTOR = .10f;
GLfloat JUMPVEL = 6.0f;
Vector2D WALLJUMPVEL = Vector2D(4.0f, 4.0f);
GLfloat STRONGJUMPFACTOR = 1.3f;
GLfloat duckJumpFactor = 1.5f;
Vector2D wallJump;

GLfloat TOUCHNBHD = .03f;		//distance to be withing to be touching
GLfloat xP;
GLfloat yP;
GLfloat oscillator;

bool cameraMode = false;
bool debugMode = false;

//actual function
void checkTouch(Object &moveObj, const Object &obj2)
{
	GLfloat moveVal;
	GLfloat distance;

	bool inLineX, inLineY;						//some overlap in given direction
	bool isMoreRight, isMoreLeft, isMoreDown, isMoreUp;	//if a maximum point on moveobj is greater than obj2
	bool goneOnce = false;
	bool rTouch, bTouch, lTouch, tTouch;		//bools which tell if a side is touching something
	bool toRight, toUp;
	bool moved;

	Vector2D vecToObj2;
	Vector2D obj2basis;
	Vector2D v;								//vertex of obj closest to obj2

	distance = dist(&moveObj, &obj2);
	if( (distance < 2*(moveObj.diag + obj2.diag)) && obj2.active)
	{
		rTouch = moveObj.isTouching[RSIDE];
		bTouch = moveObj.isTouching[BSIDE];
		lTouch = moveObj.isTouching[LSIDE];
		tTouch = moveObj.isTouching[TSIDE];

		moveVal = 0.05f;

		vecToObj2 = moveObj.pos - obj2.pos;
		if(vecToObj2.x <= 0)
		{
			if(vecToObj2.y <= 0)
				v = Vector2D(moveObj.posMin.x, moveObj.posMin.y);
			else
				v = Vector2D(moveObj.posMin.x, moveObj.posMax.y);
		}
		else
		{
			if(vecToObj2.y <= 0)
				v = Vector2D(moveObj.posMax.x, moveObj.posMin.y);
			else
				v = Vector2D(moveObj.posMax.x, moveObj.posMax.y);
		}

		obj2basis = v - obj2.pos;

		isMoreRight = moveObj.posMax.x > obj2.posMax.x;	//larger xmax
		isMoreLeft = moveObj.posMin.x < obj2.posMin.x;	//smaller xmin
		isMoreDown = moveObj.posMin.y < obj2.posMin.y;	//smaller ymin
		isMoreUp = moveObj.posMax.y > obj2.posMax.y;	//larger ymax

		toRight = moveObj.posMin.x >= obj2.pos.x;		//xmin to right of obj2x
		toUp = moveObj.pos.y >= obj2.posMin.y + .5f*obj2.dimension.y;	//ymin above halfpoint of obj2y

		inLineY = ( !(moveObj.posMaxOld.x < obj2.posMin.x) && !(moveObj.posMinOld.x > obj2.posMax.x));
		inLineX = (	!(moveObj.posMaxOld.y <= obj2.posMin.y) && !(moveObj.posOld.y >= obj2.posMax.y) );

		
		if(touchExists(moveObj, obj2))				//topleft
		{
			if(obj2.objType != tpSHOT)
			{
				//move object to the correct position
				if(inLineY && (moveObj.objType != tpSHOT) && (!lTouch || !rTouch))
				{
					//(bottom)above obj2, and moved down from last instance
					if( (fabs(moveObj.posMin.y - obj2.posMax.y) < TOUCHNBHD) && isMoreUp && toUp && (moveObj.pos.y <= moveObj.posOld.y))
					{
						if(obj2.isSolid)
							moveObj.pos.y = obj2.posMax.y;
						if(!bTouch)
						{
							moveObj.isTouchIndex[BSIDE] = obj2.index;
							moveObj.touchObj[BSIDE] = &obj2;
							bTouch = true;
						}
						collide(moveObj, obj2, BSIDE);
					}
					//(top)below obj2, moved up from last instance
					else if ( (fabs(moveObj.posMax.y - obj2.posMin.y) < TOUCHNBHD) && isMoreDown && (moveObj.pos.y >= moveObj.posOld.y) && !moveObj.state[actATTACK1])
					{
						if(obj2.isSolid)
							moveObj.pos.y = obj2.posMin.y - moveObj.dimension.y;
						if(!tTouch)
						{
							moveObj.isTouchIndex[TSIDE] = obj2.index;
							moveObj.touchObj[TSIDE] = &obj2;
							tTouch = true;
						}
						collide(moveObj, obj2, TSIDE);
					}
				}

				if(inLineX && (moveObj.objType != tpSHOT) )
				{
					//(left)to right of obj2, and moved left from last instance
					if( (fabs(moveObj.posMin.x - obj2.posMax.x) < TOUCHNBHD) && isMoreRight && (moveObj.posMin.x <= moveObj.posMinOld.x))
					{
						if(obj2.isSolid && (obj2.objType == tpGROUND))
							moveObj.pos.x = obj2.posMax.x + .5f*moveObj.dimension.x;
						if(!lTouch)
						{
							moveObj.isTouchIndex[LSIDE] = obj2.index;
							moveObj.touchObj[LSIDE] = &obj2;
							lTouch = true;
						}
						collide(moveObj, obj2, LSIDE);
						/*if(obj2.objType != tpGROUND)
							collide(moveObj, obj2, LSIDE);
						else
							moveObj.pos.x = obj2.posMax.x + ((moveObj.dirSign-1)/(-2)+moveObj.dirSign*moveObj.center)*moveObj.dimension.x;
							*/
					}
					//(right)to left of obj2 and moved right from last instance
					else if( (fabs(moveObj.posMax.x - obj2.posMin.x) < TOUCHNBHD) && isMoreLeft && (moveObj.posMax.x >= moveObj.posMaxOld.x))
					{
						if(obj2.isSolid)
							moveObj.pos.x = obj2.posMin.x - .5f*moveObj.dimension.x;
						if(!rTouch)
						{
							moveObj.isTouchIndex[RSIDE] = obj2.index;
							moveObj.touchObj[RSIDE] = &obj2;
							rTouch = true;
						}
						collide(moveObj, obj2, RSIDE);
						
						/*if(obj2.objType != tpGROUND)
							collide(moveObj, obj2, RSIDE);
						else
							moveObj.pos.x= obj2.posMin.x - ((moveObj.dirSign+1)/2-moveObj.dirSign*moveObj.center)*moveObj.dimension.x;
						*/
					}
				}

				if(moveObj.objType == tpSHOT)
				{
					if( ((obj2.objType == tpPLAYER) && !obj2.state[actATTACK1] && (moveObj.parent->objType == tpENEMY)) ||
						((obj2.objType == tpENEMY) && (moveObj.parent->objType == tpPLAYER)) ||
						(obj2.objType == tpGROUND))
					{
						moveObj.active = false;
					}
				}
			}
			else
			{
				if( ((moveObj.objType == tpPLAYER) && (moveObj.parent->objType == tpENEMY)) ||
					((moveObj.objType == tpENEMY) && (moveObj.parent->objType == tpPLAYER)) )
				{
					collide(moveObj, obj2);
				}
			}

			moveObj.calcBoundaries();

			//slide to right on obj2
			if((moveObj.posMax.x == obj2.posMin.x) && (moveObj.posMin.y == obj2.posMax.y))
			{
				moveObj.pos.x+= .001f;
			}
			//slide to left on obj2
			else if((moveObj.posMin.x == obj2.posMax.x) && (moveObj.posMin.y == obj2.posMax.y))
			{
				moveObj.pos.x-= .001f;
			}

			moveObj.isTouching[BSIDE] = bTouch;
			moveObj.isTouching[TSIDE] = tTouch;
			moveObj.isTouching[LSIDE] = lTouch;
			moveObj.isTouching[RSIDE] = rTouch;
		}
	}

	return;
}


//between player and level
void checkTouch(Object &moveObj, level_s level)
{
	for(int i=level.solidObjIdx; i<level.numObjects; i++)
	{
		checkTouch(moveObj, *level.lvlObjects[i]);
	}

	return;
}


void checkTouch(int mobjects[], int numObjects, const level_s &level)
{
	for(int k=0; k < numObjects; k++)
	{
		clearTouches(*getObject(mobjects[k]));
	}

	for(int i=0; i < numObjects; i++)
	{
		if(getObject(mobjects[i])->active)
		{
		//if((getObject(mobjects[i]]->objType != tpSHOT) && getObject(mobjects[i]]->active)
		//{
			checkTouch(*getObject(mobjects[i]), level);//}
			for(int j=0; j < numObjects; j++)
			{
				if((i!=j) && getObject(mobjects[j])->active)
					checkTouch(*getObject(mobjects[i]), *getObject(mobjects[j]));
			}
		}
	}

	return;
}


void checkTouch(objectHolder_c mobjects, const level_s &level)
{
	for(int k=0; k < mobjects.numObjects; k++)
	{
		clearTouches(*mobjects.getObject(k));
	}

	for(int i=0; i < mobjects.numObjects; i++)
	{
		if(mobjects.getObject(i)->active)
		{
		//if((getObject(mobjects[i]]->objType != tpSHOT) && getObject(mobjects[i]]->active)
		//{
			checkTouch(*mobjects.getObject(i), level);//}
			for(int j=0; j < mobjects.numObjects; j++)
			{
				if((i!=j) && mobjects.getObject(i)->active)
					checkTouch(*mobjects.getObject(i), *mobjects.getObject(j));
			}
		}
	}

	return;
}


void checkTouch(Object &moveObj, ObjectList objs, int nobjs, int nocheck)
{
	if(nocheck==-1)
        nocheck = objs.size()+1;
	
		//if((getObject(mobjects[i]]->objType != tpSHOT) && getObject(mobjects[i]]->active)
		//{
		;//}
    for(int j=0; j < objs.size(); j++)
	{
            checkTouch(moveObj, *objs[j]);
	}

	return;
}


void clearTouches(Object &obj)
{
	obj.isTouching[RSIDE] = false;
	obj.isTouching[BSIDE] = false;
	obj.isTouching[LSIDE] = false;
	obj.isTouching[TSIDE] = false;

	return;
}


void updatePlayerMove(Object &moveObj, GLfloat dt)
{
    QTime clock;
	GLfloat currentTime;
	actions thisAct;
	bool doneAction[20];		//used for loop of actions
	int playerKeys[8];
	int playerBtns[8];

	playerNum numPlayer = moveObj.numPlayer;
	bool couldAnimate = true;
	Object* shot = NULL;

	for(int ac=0; ac<NUMACTIONS; ac++)
		doneAction[ac] = false;
	
	getKeys(numPlayer, playerKeys);
	getBtns(numPlayer, playerBtns);

	//init values
	if(moveObj.isTouching[BSIDE])
	{
		moveObj.velOld.y = moveObj.vel.y;		//change velOld to updated vel
		moveObj.accel.y -= acceleration;
		moveObj.projectile = false;
	}
	if(moveObj.isTouching[LSIDE] || moveObj.isTouching[RSIDE])
	{
		moveObj.velOld.x = moveObj.vel.x;		//change velOld to updated vel
	}

	if(playerPress(numPlayer, btnLEFT))
	{
		moveObj.pRight = false;
		moveObj.dirSign = -1.0f;
	}
	else if(playerPress(numPlayer, btnRIGHT))
	{
		moveObj.pRight = true;
		moveObj.dirSign = 1.0f;
	}
	
	moveObj.mov.x = 0;
	if(playerPress(numPlayer, btnLEFT))
		moveObj.mov.x += -1;
	if(playerPress(numPlayer, btnRIGHT))
		moveObj.mov.x += 1;

	if(canPlayerToggle(numPlayer, btnJUMP))
	{
		if(moveObj.isTouching[BSIDE])
		{
			//thisAct = actJUMP;
			moveObj.projectile = false;
			playActionSound(moveObj, thisAct);
			
			if(moveObj.state[actDUCK]) 
				moveObj.velOld.y += STRONGJUMPFACTOR*JUMPVEL*moveObj.jumpStrength;
			else
				moveObj.velOld.y += JUMPVEL*moveObj.jumpStrength;
		}
		//jumping off the wall
		else if(moveObj.canWallClimb &&
				((moveObj.isTouching[LSIDE] && moveObj.touchObj[LSIDE]->objType == tpGROUND ) 
				||(moveObj.isTouching[RSIDE] && moveObj.touchObj[RSIDE]->objType == tpGROUND ))
				)
		{
			moveObj.projectile = false;
			moveObj.velOld.y += WALLJUMPVEL.y;
			if(moveObj.isTouching[LSIDE])
			{
				moveObj.velOld.x += WALLJUMPVEL.x*moveObj.jumpStrength;		//might be wrong
				moveObj.mov.x = 1;
				moveObj.dirSign = 1.0f;
				moveObj.pRight = true;
			}
			else
			{
				moveObj.velOld.x -= WALLJUMPVEL.x*moveObj.jumpStrength;		//might be wrong
				moveObj.mov.x = -1;
				moveObj.dirSign = -1.0f;
				moveObj.pRight = false;
			}
		}
	}
	
	//Y direction velocity checking------------
	if( (moveObj.isTouching[RSIDE] || moveObj.isTouching[LSIDE]) && moveObj.canWallClimb && moveObj.state[actWALL])
		moveObj.accel.y -= WALLFRIC*moveObj.velOld.y;		//need to add friction of touching object
	
	if(moveObj.MV.y == 0.0f)
		moveObj.vel.y = moveObj.velOld.y + (acceleration + moveObj.accel.y)*dt;
			//moveObj.vel.y = moveObj.vel.y + acceleration*timeStep - moveObj.accel;
	else
		moveObj.vel.y = moveObj.MV.y/moveObj.mass;
	
	//X direction velocity checking---------------------
	if(moveObj.isTouching[LSIDE] && (moveObj.vel.x <=0.0f))
	{
		moveObj.accel.x = 0.0f;
		moveObj.mov.x = moveObj.mov.x*(moveObj.mov.x+1)/2;		//make movx 0 or 1
	}
	else if(moveObj.isTouching[RSIDE] && (moveObj.vel.x >=0.0f) )
	{
		moveObj.accel.x = 0.0f;
		moveObj.mov.x = -moveObj.mov.x*(moveObj.mov.x-1)/2;
	}
	else if(moveObj.state[actDUCK])
	{
		moveObj.accel.x -= DUCKFRICFACTOR*GROUNDFRIC*moveObj.velOld.x;	//need to add friction
	}
	else if(moveObj.isTouching[BSIDE])
	{
		if(!moveObj.state[actRUN])
			moveObj.accel.x = -GROUNDFRIC*moveObj.velOld.x;
		else
			moveObj.accel.x = -RUNFRICFACTOR*GROUNDFRIC*moveObj.velOld.x;
	}
	else if(!moveObj.isTouched())
	{
		if(moveObj.mov.x == 0.0f)
			moveObj.vel.x = moveObj.velOld.x*COASTFAC;
		else
		{
			moveObj.accel.x = moveObj.mov.x*AIRMOVEFACTOR*fabs(moveObj.velOld.x)/moveObj.xSpeed;
		}
	}

	if(moveObj.MV.x != 0.0f)
		moveObj.vel.x = moveObj.MV.x/moveObj.mass;
	//else if(moveObj.projectile || moveObj.isTouching[BSIDE])
		moveObj.vel.x = moveObj.velOld.x + (XSCALE*(moveObj.xSpeed - fabs(moveObj.velOld.x))*moveObj.mov.x + moveObj.accel.x)*dt;
		//moveObj.vel.x += xScale*(moveObj.mov.x - moveObj.posOld.x) + moveObj.accel.x;
	//else
		//moveObj.vel.x = (XSCALE*(moveObj.xSpeed - fabs(moveObj.velOld.x))*moveObj.mov.x)*dt;
	
	//update player positions with throttle
	moveObj.pos.x += moveObj.vel.x*dt;
	moveObj.pos.y += moveObj.vel.y*dt;
	moveObj.calcBoundaries();

	clearStates(moveObj);

	if(moveObj.objshots != NULL)
		moveObj.objshots->updateShots();

    currentTime = clock.currentTime().msec();
	//do all actions
	do
	{
		if(!moveObj.animationDone[moveObj.currentAct] && !doneAction[moveObj.currentAct])
			thisAct = static_cast<actions>(moveObj.currentAct);
		else if( playerPress(numPlayer, btnSHOOT) && (moveObj.objshots != NULL) && !doneAction[actSHOOT] && moveObj.canShoot)
		{
			if(canPlayerToggle(numPlayer, btnSHOOT))
			{
				shot = moveObj.objshots->nextShot();
				if(shot != NULL)
				{
					shot->dirSign = moveObj.dirSign;
					moveShots(shot);
				}
			}
			thisAct = actSHOOT;
		}
		else if( (((playerPress(numPlayer, btnRIGHT) && moveObj.isTouching[RSIDE] && moveObj.touchObj[RSIDE]->objType == tpGROUND) && (moveObj.posMax.y - .25f*moveObj.dimension.y) < moveObj.touchObj[RSIDE]->posMax.y)
				|| ((playerPress(numPlayer, btnLEFT) && moveObj.isTouching[LSIDE]) && moveObj.touchObj[LSIDE]->objType == tpGROUND && (moveObj.posMax.y - .25f*moveObj.dimension.y) < moveObj.touchObj[LSIDE]->posMax.y)
				&& !moveObj.isTouching[BSIDE]) && !doneAction[actWALL] )
			thisAct = actWALL;
		else if( ((playerPress(numPlayer, btnRIGHT) && moveObj.isTouching[RSIDE]) || (playerPress(numPlayer, btnLEFT) && moveObj.isTouching[LSIDE]))
			&& moveObj.isTouching[BSIDE] && !doneAction[actPUSH])
			thisAct = actPUSH;
		else if((playerPress(numPlayer, btnATTACK) && moveObj.isTouching[BSIDE]) && !doneAction[actATTACK1])
		{
			thisAct = actATTACK1;
			moveObj.isAttacking = true;
		}
		else if(playerPress(numPlayer, btnATTACK)  && !moveObj.isTouching[BSIDE] && !doneAction[actJUMPATK])
		{
			thisAct = actJUMPATK;
			moveObj.isAttacking = true;
		}
		else if( (playerPress(numPlayer, btnLEFT) || playerPress(numPlayer, btnRIGHT)) && moveObj.isTouching[BSIDE] && !moveObj.isTouching[RSIDE] && !moveObj.isTouching[LSIDE])
			thisAct = actRUN;
		else if(playerPress(numPlayer, btnDOWN) && moveObj.isTouching[BSIDE] && !doneAction[actDUCK])
		{
			thisAct = actDUCK;
			moveObj.state[actDUCK] = true;
		}
		else
			thisAct = actNONE;

		if(moveObj.animated)
		{
			couldAnimate = sendAnimation(moveObj, thisAct, dt);
			doneAction[thisAct] = true;
			moveObj.currentAct = thisAct;
		}
	}while(!couldAnimate);
	
    currentTime = clock.msec();
	if(!moveObj.actionTime[thisAct].started)
	{
		moveObj.actionTime[thisAct].startTime = currentTime;
	}
	else
		moveObj.actionTime[thisAct].timeHeld = currentTime - moveObj.actionTime[thisAct].startTime;

	for(int dh = 0; dh < NUMACTIONS; dh++)
	{
		if(!doneAction[dh])
			moveObj.actionTime[dh].started = false;
	}

	//play action sound
	if((moveObj.actionTime[thisAct].startTime == currentTime) && moveObj.state[thisAct])
		playActionSound(moveObj, thisAct);

	//cycle character
	static int playerNum = moveObj.person;
//	if(canToggle('P') || canToggleBtn(xbRTRIGGER))
    if(canToggle('P'))
	{
		playerNum = mod(++playerNum, NUMCHARACTERS);
		assignTextures(moveObj, playerTextures[playerNum]);
	}
    /*else if(canToggleBtn(xbLTRIGGER))
	{
		playerNum = mod(--playerNum, NUMCHARACTERS);
		assignTextures(moveObj, playerTextures[playerNum]);
    }*/

	//store old values
	moveObj.posOld = moveObj.pos;
	moveObj.posMinOld = moveObj.posMin;
	moveObj.posMaxOld = moveObj.posMax;
	moveObj.velOld = moveObj.vel;
	moveObj.vel = Vector2D(0.0f,0.0f);
	moveObj.accel = Vector2D(0.0f,0.0f);
	moveObj.MV.x = 0.0f;
	moveObj.MV.y = 0.0f;

	return;
}


void updateEnemyMove(Object &moveObj, const Object &target, GLfloat dt)
{
	actions thisAct = actNONE;
	bool couldAnimate = true;
	bool hurt = false;
	bool doneAction[20];
	GLfloat currentTime;
	GLfloat yMoveTo;
    QTime clock;
	
	for(int ac=0; ac<NUMACTIONS; ac++)
		doneAction[ac] = 0;

	moveObj.calcBoundaries();

	//init values
	if(moveObj.isTouching[BSIDE])
	{
		moveObj.velOld.y = moveObj.vel.y;		//change velOld to updated vel
		moveObj.accel.y -= acceleration;
	}
	if(moveObj.isTouching[LSIDE] || moveObj.isTouching[RSIDE])
	{
		moveObj.velOld.x = moveObj.vel.x;		//change velOld to updated vel
	}

	runEnemyAI(moveObj, target);
	
	if(moveObj.velOld.x < 0.0f)
	{
		moveObj.pRight = false;
		moveObj.dirSign = -1.0f;
	}
	else if(moveObj.velOld.x > 0.0f)
	{
		moveObj.pRight = true;
		moveObj.dirSign = 1.0f;
	}

	//Y direction velocity checking------------
	if(moveObj.MV.y == 0.0f)
		moveObj.vel.y = moveObj.velOld.y + (acceleration + moveObj.accel.y)*dt;
	else
		moveObj.vel.y = moveObj.MV.y/moveObj.mass;

	//X direction velocity checking----------------------
	if(moveObj.isTouching[LSIDE] && moveObj.vel.x <0.0f)
	{
		moveObj.vel.x = 0.0f;
		moveObj.accel.x = 0.0f;
	}
	else if(moveObj.isTouching[RSIDE] && moveObj.vel.x >0.0f)
	{
		moveObj.vel.x = 0.0f;
		moveObj.accel.x = 0.0f;
	}
	else if(moveObj.isTouching[BSIDE])
	{
		//moveObj.accel.x = .04f*moveObj.vel.x;
		if(!moveObj.state[actRUN])
			moveObj.accel.x = -GROUNDFRIC*moveObj.velOld.x;
		else
			moveObj.accel.x = -RUNFRICFACTOR*GROUNDFRIC*moveObj.velOld.x;
	}
	else if(!moveObj.isTouching[BSIDE] && !moveObj.isTouching[TSIDE]
		 && !moveObj.isTouching[LSIDE] && !moveObj.isTouching[RSIDE]
		 && moveObj.mov.x == 0.0f)
	{
		moveObj.vel.x = moveObj.velOld.x*COASTFAC;
	}
	else
	{
		moveObj.accel.x = 0.0f;
	}

	if(moveObj.MV.x == 0.0f)
		moveObj.vel.x = moveObj.velOld.x + (XSCALE*(moveObj.xSpeed - fabs(moveObj.velOld.x))*moveObj.mov.x + moveObj.accel.x)*dt;
		//moveObj.vel.x += (XSCALE*(moveObj.pos.x - moveObj.posOld.x) - moveObj.accel.x)*dt;
	else
		moveObj.vel.x = moveObj.MV.x/moveObj.mass;

	//update enemy positions with throttle
	//moveObj.pos.x += moveObj.vel.x*timeStep*5.0f;
	//moveObj.pos.y = yMoveTo;
	moveObj.pos.x += moveObj.vel.x*dt;
	moveObj.pos.y += moveObj.vel.y*dt;

	moveObj.calcBoundaries();

	hurt = moveObj.state[actHURT];
	clearStates(moveObj);
	if(moveObj.person == GOOMBA)
		moveObj.state[actATTACK1] = true;

	if( (fabs(target.pos.y - moveObj.pos.y) < .5f) && (moveObj.objshots != NULL) && moveObj.canShoot)
	{
		//if(dist(moveObj, *getObject(moveObj.shotIndex]) > 20.0f)
		/*if(!getObject(moveObj.shotIndex)->active)
		{
			getObject(moveObj.shotIndex)->dirSign = moveObj.dirSign;
			moveShots(*getObject(moveObj.shotIndex));
		}*/
		thisAct = actSHOOT;
	}
	
    currentTime = clock.msec();
	int loops = 0;
	do
	{
		if(moveObj.animated)
		{
			if(hurt && !doneAction[actHURT])
				thisAct = actHURT;
			else if((thisAct == actJUMP) && !doneAction[actJUMP])
				;
			else if((thisAct == actSHOOT) && !doneAction[actSHOOT])
				;
			else if((dist(&moveObj, &target) < 4.0f) && moveObj.isTouching[BSIDE] && !doneAction[actATTACK1])
			{
				//moveObj.xVel = moveObj.dirSign*.5f;
				moveObj.actionTime[actATTACK1].timeHeld = currentTime - moveObj.actionTime[actATTACK1].startTime;
				if(moveObj.actionTime[actATTACK1].timeHeld > 1.0f)
					//moveObj.actionTime[actATTACK1][HOLD] = -1;
					moveObj.actionTime[actATTACK1].started = false;
				if(moveObj.actionTime[actATTACK1].timeHeld > 0.4f)
					doneAction[actATTACK1] = true;
				else
				{
					thisAct = actATTACK1;
					moveObj.isAttacking = true;
				}
			}
			else if( (fabs(moveObj.vel.x) > 0.0f) && moveObj.isTouching[BSIDE] && !doneAction[actRUN])
				thisAct = actRUN;
			else
				thisAct = actNONE;
			
			if(moveObj.animated)
			{
				couldAnimate = sendAnimation(moveObj, thisAct, dt);
				doneAction[thisAct] = true;
			}
		}
		loops++;
		if(loops > 500)
			int j = 5+5;
	}while(!couldAnimate);
	
    currentTime = clock.msec();

	if(!moveObj.actionTime[thisAct].started)
	{
		moveObj.actionTime[thisAct].started = currentTime;
		moveObj.actionTime[thisAct].timeHeld = 0.0f;
	}
	else
		moveObj.actionTime[thisAct].timeHeld = currentTime - moveObj.actionTime[actATTACK1].startTime;	//repeat, might need to remove

	for(int dh = 0; dh < NUMACTIONS; dh++)
	{
		if(!doneAction[dh])
			moveObj.actionTime[dh].started = false;
	}

	if(thisAct != actHURT)
		moveObj.state[thisAct] = true;

	if(moveObj.actionTime[thisAct].timeHeld == 0.0f)
		playActionSound(moveObj, thisAct);	

	if(moveObj.health == 0.0f)
		moveObj.active = false;

	//store old values
	moveObj.posOld = moveObj.pos;
	moveObj.posMinOld = moveObj.posMin;
	moveObj.posMaxOld = moveObj.posMax;
	moveObj.velOld = moveObj.vel;
	moveObj.vel = Vector2D(0.0f,0.0f);
	moveObj.accel = Vector2D(0.0f,0.0f);
	moveObj.MV.x = 0.0f;
	moveObj.MV.y = 0.0f;

	return;
}


actions runEnemyAI(Object &thisEnemy, const Object &target)
{
	GLfloat floorLeft, floorRight;
	actions thisAct = actNONE;
	thisEnemy.mov = Vector2D(0,0);
	
	switch(thisEnemy.person)
	{
		case GOOMBA:
			if(thisEnemy.isTouching[BSIDE])
			{
				//floorLeft = getObject(thisEnemy.isTouchIndex[BSIDE])->posMin.x;
				floorLeft = thisEnemy.touchObj[BSIDE]->posMin.x;
				//floorRight = getObject(thisEnemy.isTouchIndex[BSIDE])->posMax.x;
				floorRight = thisEnemy.touchObj[BSIDE]->posMax.x;
			}
			if((floorLeft > thisEnemy.posMin.x) || thisEnemy.isTouching[LSIDE])
				thisEnemy.vel.x = .07f*thisEnemy.xSpeed;
			else if((floorRight < thisEnemy.posMax.x) || thisEnemy.isTouching[RSIDE])
				thisEnemy.vel.x = -.07f*thisEnemy.xSpeed;
			else
				thisEnemy.vel.x += .015*thisEnemy.xSpeed*thisEnemy.dirSign;
			break;
		default:
			if((target.posMax.x < thisEnemy.posMin.x) && !thisEnemy.isTouching[LSIDE])
			{
				//thisEnemy.vel.x -= .007f*thisEnemy.xSpeed;
				thisEnemy.mov.x -= 1;
			}
			else if((target.posMin.x > thisEnemy.posMax.x) && !thisEnemy.isTouching[RSIDE])
			{
				//thisEnemy.x += .007f*thisEnemy.xSpeed;
				//thisEnemy.vel.x += .007f*thisEnemy.xSpeed;
				thisEnemy.mov.x += 1;
			}
			
			if((target.posMin.y > thisEnemy.posMax.y) && thisEnemy.isTouching[BSIDE] && (dist(&thisEnemy, &target) < 8.0f))
			{
				thisEnemy.velOld.y += JUMPVEL*thisEnemy.jumpStrength;
				thisAct = actJUMP;
			}
			break;
	}
	return thisAct;
}


bool touchExists(const Object &moveObj, const Object &obj2)
{
	Vector2D posMin, posMax;
	bool tE;

	posMin.x = Max(moveObj.posMin.x, obj2.posMin.x);
	posMax.x = Min(moveObj.posMax.x, obj2.posMax.x);
	posMin.y = Max(moveObj.posMin.y, obj2.posMin.y);
	posMax.y = Min(moveObj.posMax.y, obj2.posMax.y);

	if((posMax.x < posMin.x) || (posMax.y < posMin.y))
		tE = false;
	else
		tE = true;

	return tE;
}


void updateObjectMove(Object &moveObj, GLfloat dt)
{
	GLfloat resetVal;
	resetVal = 0.05f;
	GLfloat xScale = 0.0f;
	GLfloat xMoveTo, yMoveTo;

	acceleration = -9.0f;
	moveObj.accel = Vector2D(0.0f, 0.0f);
		//moveObj.accel = 0.0f;
	
	moveObj.posOld = moveObj.pos;
	moveObj.velOld = moveObj.vel;

	moveObj.posMinOld = moveObj.posMin;
		//moveObj.xMinOld = moveObj.posMin.x;
	moveObj.posMaxOld = moveObj.posMax;
		//moveObj.xMaxOld = moveObj.posMax.x;
		//moveObj.yMaxOld = moveObj.posMax.y;
	
	if(isKeys('U'))
		moveObj.vel.x = -.5f;
	if(isKeys('I'))
		moveObj.vel.x = .5f;

	if(moveObj.vel.x < 0.0f)
	{
		moveObj.pRight = false;
		moveObj.dirSign = -1.0f;
	}
	else if(moveObj.vel.x > 0.0f)
	{
		moveObj.pRight = true;
		moveObj.dirSign = 1.0f;
	}

	//yMov -= 1.2f*resetVal;
	if((moveObj.isTouching[BSIDE]) || (moveObj.objType == tpSHOT))
		moveObj.accel.y = 0.0f;
	moveObj.vel.y = moveObj.vel.y + moveObj.accel.y*dt;
	yMoveTo = moveObj.pos.y + moveObj.vel.y*dt;
	moveObj.pos.y = yMoveTo;
	moveObj.calcBoundaries();

	/*if(!moveObj.isTouching[LSIDE])
		moveObj.xVel += xMov - moveObj.xOld;*/

	if(moveObj.isTouching[LSIDE] && moveObj.vel.x <0.0f)
	{
		moveObj.vel.x = 0.0f;
		moveObj.accel.x = 0.0f;
	}
	else if(moveObj.isTouching[RSIDE] && moveObj.vel.x >0.0f)
	{
		moveObj.vel.x = 0.0f;
		moveObj.accel.x = 0.0f;
	}
	else if(moveObj.isTouching[BSIDE])
			moveObj.accel.x = -moveObj.dirSign*.04f*moveObj.vel.x;
	else
	{
		moveObj.accel.x = 0.0f;
		xScale = .3f;
	}

	if(moveObj.MV.x == 0.0f)
		moveObj.vel.x += xScale*(moveObj.pos.x- moveObj.posOld.x) + moveObj.accel.x;
	else
		moveObj.vel.x = moveObj.MV.x/moveObj.mass;

	moveObj.pos.x += moveObj.vel.x*dt*5.0f;
	if((moveObj.canRoll) && moveObj.isTouching[BSIDE])
		moveObj.rotate -= moveObj.vel.x*8;
	moveObj.pos.y = yMoveTo;

	if(isKeys('H'))
	{
		moveObj.pos.y = moveObj.posOld.y;
		moveObj.vel.y = 8.0f;
	}
	
	moveObj.calcBoundaries();
	clearStates(moveObj);
	
	//xMov = moveObj.x;

	/*if(moveObj.animated && (moveObj.objType == tpSHOT))
		animate(moveObj);*/

	moveObj.MV.x = 0.0f;
	moveObj.MV.y = 0.0f;
	
	return;
}


void updateMoves(int mobjects[], int numObjects)
{
	/*for(int i=0; i<numObjects; i++)
	{
		if(getObject(mobjects[i])->objType == tpSHOT)
		{
			GLfloat shotDist = dist(*getObject(mobjects[i]), *getObject(getObject(mobjects[i])->parentIndex));
			if(shotDist > 25.0f)
				getObject(mobjects[i])->active = false;
		}
		if(getObject(mobjects[i])->active)
		{
			switch(getObject(mobjects[i])->objType)
			{
				case tpPLAYER:
					updatePlayerMove(*getObject(mobjects[i]));
					break;
				case tpENEMY:
					updateEnemyMove(*getObject(mobjects[i]), *getObject(0));
					break;
				case tpSHOT:
				case tpOBJ:
					updateObjectMove(*getObject(mobjects[i]));
					break;
				default:
					break;
			}

			if(getObject(mobjects[i])->animated)
				fixSize(*getObject(mobjects[i]));
		}
	}*/

	return;
}


void updateMoves(objectHolder_c mobjects)
{
	/*for(int i=0; i<mobjects.numObjects; i++)
	{
		if(mobjects.getObject(i)->objType == tpSHOT)
		{
			GLfloat shotDist = dist(*mobjects.getObject(i), *getObject(mobjects.getObject(i)->parentIndex));
			if(shotDist > 25.0f)
				mobjects.getObject(i)->active = false;
		}
		if(mobjects.getObject(i)->active)
		{
			switch(mobjects.getObject(i)->objType)
			{
				case tpPLAYER:
					updatePlayerMove(*mobjects.getObject(i));
					break;
				case tpENEMY:
					updateEnemyMove(*mobjects.getObject(i), *getObject(0));
					break;
				case tpSHOT:
				case tpOBJ:
					updateObjectMove(*mobjects.getObject(i));
					break;
				default:
					break;
			}

			if(mobjects.getObject(i)->animated)
				fixSize(*mobjects.getObject(i));
		}
	}*/

	return;
}

bool resetPos(Object &Obj, const Object &obj2)
{
	bool didReset = false;
	GLfloat leftSpace, rightSpace, bottomSpace, topSpace, smallSpace;

	smallSpace = .005f;
	rightSpace = obj2.posMin.x - Obj.posMax.x;
	bottomSpace = Obj.posMin.y - obj2.posMax.y;
	leftSpace = Obj.posMin.x - obj2.posMax.x;
	topSpace = obj2.posMin.y - Obj.posMax.y;

	if((rightSpace < 0.0) && Obj.isTouching[RSIDE] && (Obj.isTouchIndex[RSIDE] == obj2.index))
	{
		Obj.pos.x = obj2.posMin.x - .5f*Obj.dimension.x;
		didReset = true;
	}
	if((bottomSpace < 0.0) && Obj.isTouching[BSIDE] && (Obj.isTouchIndex[BSIDE] == obj2.index))
	{
		Obj.pos.y = obj2.posMax.y;
		didReset = true;
	}
	if((leftSpace < 0.0) && Obj.isTouching[LSIDE] && (Obj.isTouchIndex[LSIDE] == obj2.index))
	{
		Obj.pos.x = obj2.posMax.x + .5f*Obj.dimension.x;	
		didReset = true;
	}
	if((topSpace < 0.0f) && Obj.isTouching[TSIDE] && (Obj.isTouchIndex[TSIDE] == obj2.index))
	{
		Obj.pos.y = obj2.posMin.y - Obj.dimension.y;
		didReset = true;
	}
	Obj.calcBoundaries();

	return didReset;
}


void collide(Object &obj1, const Object &obj2, touch side)
{
	GLfloat initHealth = obj1.health;
	Object* obj2ptr = getObject(obj2.index);
	Vector2D v1  = obj1.velOld;
	Vector2D v2;
	bool movingTowardsLR;	//left right
	bool movingTowardsUD;	//up down
    QTime clock;

	movingTowardsLR = ((side == LSIDE) && (obj1.velOld.x < 0.0f)) || ((side == RSIDE) && (obj1.velOld.x > 0.0f));
	movingTowardsUD = ((side == BSIDE) && (obj1.velOld.y < 0.0f)) || ((side == TSIDE) && (obj1.velOld.y > 0.0f));
	
	if((side == LSIDE) || (side == RSIDE))
	{
		if((obj2.objType == tpGROUND))
		{
			if(movingTowardsLR)
			{
				v1.x -= v1.x;		//add elasticity
				obj1.vel.x = v1.x;
			}
			else
				obj1.vel.x = v1.x;	//need to work on
		}
		else if(obj2.isAttacking)
		{
			//need to update hit amounts
			if(side == LSIDE)
				obj1.MV.x += 70.0f/obj1.mass;
			else
				obj1.MV.x -= 70.0f/obj1.mass;

			obj1.health -= fabs(obj1.MV.x)/100;
		}
		else
			obj1.MV.x += obj1.mass*( (obj1.mass-obj2.mass)/(obj1.mass+obj2.mass)*obj1.vel.x + 2*obj2.mass/(obj1.mass+obj2.mass)*obj2.vel.x );
			//obj2.xVel = 2*obj1.mass/(obj1.mass+obj2.mass)*obj1.xVel + (obj2.mass-obj1.mass)/(obj1.mass+obj2.mass)*obj2.xVel;
			//getObject(obj2.index)->xVel = 2*obj1.mass/(obj1.mass+obj2.mass)*obj1.xVel + (obj2.mass-obj1.mass)/(obj1.mass+obj2.mass)*obj2.xVel;
		if(obj1.MV.x != 0.0f)
		{
			if(RSIDE)
				obj1.isTouching[RSIDE] = false;
			else
				obj1.isTouching[LSIDE] = false;
		}

		if(obj2.objType == tpSHOT)
		{
			if(obj1.state[actATTACK1])
			{
				obj2ptr->vel.x = -obj2ptr->vel.x;
                obj2ptr->vel.y = sin(static_cast<GLfloat>(clock.msec()));
				obj1.health -= fabs(obj2.vel.x/80);
			}
			else
				obj1.health -= fabs(obj2.vel.x/20);
		}
	}
	else if((side == BSIDE) || (side == TSIDE))
	{
		if(obj2.objType == tpGROUND)
		{
			if(movingTowardsUD)
			{
				v1.y -= v1.y;		//add elasticity
				obj1.vel.y = v1.y;
			}
			else
				obj1.vel.y = v1.y;	//need to work on
		}
		else if(obj2.state[actATTACK1])
		{
			obj1.MV.y += -obj1.dirSign*70.0f/obj1.mass;
			obj1.health -= fabs(obj1.MV.y)/100;
		}
		else
			obj1.MV.y += obj1.mass*( (obj1.mass-obj2.mass)/(obj1.mass+obj2.mass)*obj1.vel.y + 2*obj2.mass/(obj1.mass+obj2.mass)*obj2.vel.y );
			//obj2.yVel = 2*obj1.mass/(obj1.mass+obj2.mass)*obj1.yVel + (obj2.mass-obj1.mass)/(obj1.mass+obj2.mass)*obj2.yVel;
			//getObject(obj2.index)->yVel = 2*obj1.mass/(obj1.mass+obj2.mass)*obj1.yVel + (obj2.mass-obj1.mass)/(obj1.mass+obj2.mass)*obj2.yVel;
		
		if(obj1.MV.y != 0.0f)
		{
			if(TSIDE)
				obj1.isTouching[TSIDE] = false;
			else
				obj1.isTouching[BSIDE] = false;
		}

		if(obj2.objType == tpSHOT)
		{
			if(obj1.state[actATTACK1])
			{
				obj2ptr->vel.y = -obj2ptr->vel.y;
                obj2ptr->vel.y = sin(static_cast<float>(clock.msec()));
				//obj1.health -= fabs(obj2.yVel/80);
			}
			else
				obj1.health -= fabs(obj2.vel.y/20);
		}
	}
	
	if(obj1.health < initHealth)
	{
		obj1.state[actHURT] = true;
		playActionSound(obj1, actHURT);
	}
	if(obj1.health <= 0.0f)
	{
		obj1.health =0.0f;
		done=true;
	}

	return;
}


void collide(Object &obj1, const Object &obj2)
{
	GLfloat initHealth = obj1.health;
	Object* obj2ptr = getObject(obj2.index);
    QTime clock;
	
	if(obj2.objType == tpSHOT)
	{
		if(obj1.state[actATTACK1])
		{
			obj2ptr->vel.x = -obj2ptr->vel.x;
            obj2ptr->vel.y = sin(static_cast<float>(clock.msec()));
			obj1.health -= fabs(obj2.vel.x/80);
		}
		else
			obj1.health -= fabs(obj2.vel.x/20);
	}
	else if(obj2.state[actATTACK1])
		obj1.MV.x += -obj1.dirSign*100.0f/obj1.mass;
	else
		obj1.MV.x += obj1.mass*( (obj1.mass-obj2.mass)/(obj1.mass+obj2.mass)*obj1.vel.x + 2*obj2.mass/(obj1.mass+obj2.mass)*obj2.vel.x );

	if(obj1.health < initHealth)
		obj1.state[actHURT] = true;
		playActionSound(obj1, actHURT);
	if(obj1.health <= 0.0f)
	{
		obj1.health =0.0f;
		//done=true;
	}

	return;
}


void clearStates(Object &obj)
{
	for(int i=0; i<20; i++)
	{
		obj.state[i] = false;
	}

	return;
}


void oscillate()
{
	static GLfloat xf;
	oscillator = sin(xf);
	xf += .2f;

	return;
}



void moveShots(Object *sh)
{
	Object* parent = sh->parent;

	sh->vel.y = 0.0f;
	sh->velOld.y = 0.0f;

	sh->vel.x = sh->dirSign*3.0f;

	sh->pos.x = parent->pos.x + sh->dirSign*.5f*parent->dimension.x;
	sh->pos.y = parent->pos.y + .25f*parent->dimension.y;

	return;
}
