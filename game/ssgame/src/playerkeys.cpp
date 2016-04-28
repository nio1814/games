#include "playerkeys.h"

#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>

#include "datastructs.h"

#include "masking.h"
#include "movement.h"
#include "sound.h"
#include "objects.h"
#include "functions.h"
#include "keys.h"

int		controlsK[2][8];	//keyboard controls
int		controlsB[2][8];	//joystick controls

void assignControls()
{
    controlsK[PLAYER1][btnLEFT] = Qt::Key_Left;
	controlsK[PLAYER1][btnRIGHT] = Qt::Key_Right;
	controlsK[PLAYER1][btnUP] = Qt::Key_Up;
	controlsK[PLAYER1][btnDOWN] = Qt::Key_Down;
	controlsK[PLAYER1][btnJUMP] = Qt::Key_A;
	controlsK[PLAYER1][btnATTACK] = Qt::Key_D;
	controlsK[PLAYER1][btnSHOOT] = Qt::Key_F;
	controlsK[PLAYER1][btnDASH] = Qt::Key_S;

	/*controlsB[PLAYER1][btnLEFT] = xbLEFT;
	controlsB[PLAYER1][btnRIGHT] = xbRIGHT;
	controlsB[PLAYER1][btnUP] = xbUP;
	controlsB[PLAYER1][btnDOWN] = xbDOWN;
	controlsB[PLAYER1][btnJUMP] = xbA;
	controlsB[PLAYER1][btnATTACK] = xbX;
	controlsB[PLAYER1][btnSHOOT] = xbB;
	controlsB[PLAYER1][btnDASH] = xbY;

	controlsK[PLAYER2][btnLEFT] = VK_NUMPAD4;
	controlsK[PLAYER2][btnRIGHT] = VK_NUMPAD6;
	controlsK[PLAYER2][btnUP] = VK_NUMPAD8;
	controlsK[PLAYER2][btnDOWN] = VK_NUMPAD5;
	controlsK[PLAYER2][btnJUMP] = VK_NUMPAD8;
	controlsK[PLAYER2][btnATTACK] = VK_NUMPAD0;
	controlsK[PLAYER2][btnSHOOT] = MK_MBUTTON+255;
	controlsK[PLAYER2][btnDASH];
	
	int lb = MK_LBUTTON;
	int rb = MK_RBUTTON;
    int mb = MK_MBUTTON;*/
	
	return;
}

void runKeys(Level* lvl, pointerTree* treeIn)
{
	CameraView view = lvl->cameras.camview;
    CameraPoint* cam = &lvl->cameras.cpoints[lvl->cameras.currentPoint];
//	Object* moveobj = &lvl->players[lvl->playerFocus];
    ObjectPointer moveobj = lvl->getPlayer(lvl->playerFocus);
	static CameraView lastCam = FOLLOW;
	static pointerTree* tP = treeIn;
	
	//variable pointers
	float* floatPtr;
	GLfloat* floatvecPtr[3];

//TOGGLE BUTTONS
	//toggle light
	if (canToggle('L'))				// L Key Being Pressed Not Held?
	{
		light=!light;				// Toggle Light TRUE/FALSE	
		if (!light)				// If Not Light
		{
			glDisable(GL_LIGHTING);		// Disable Lighting
		}
		else					// Otherwise
		{
			glEnable(GL_LIGHTING);		// Enable Lighting
		}
	}
	//change lighting filter
	if (canToggle('F'))				// Is F Key Being Pressed?
	{
		filter = mod(filter++, 3);
	}
	//camera mode	
	if (canToggle('C'))				// Is F Key Being Pressed?
	{
		cameraMode = !cameraMode;
		if (!cameraMode)
		{
			xspeed = yspeed = 0;
			lvl->cameras.camview = lastCam;
		}
		else
		{
			lastCam = lvl->cameras.camview;
			lvl->cameras.camview = CAMERAMODE;
		}
	}
	//toggles music
	if (canToggle('M'))				// Is M Key Being Pressed?
	{
		toggleMusic();
	}
	//debug mode	
//	if (canToggle('G') || canToggleBtn(xbBACK))				// Is J Key Being Pressed?
    if (canToggle('G'))				// Is J Key Being Pressed?
	{
		debugMode = !debugMode;
		if (!debugMode)
		{
			xspeed = yspeed = 0;
			lvl->cameras.camview = lastCam;
		}
		else
		{
			lastCam = lvl->cameras.camview;
			lvl->cameras.camview = DEBUGMODE;
		}
	}
/*
	//update joystick positions
	if(joy->activated)
	{
		//update joystick button presses
		for( int i = 0; i < 12; i++ )
		{
			if ( joy->js.rgbButtons[i] & 0x80 )
				btnDown(i);
			else
				btnUp(i);
		}
		switch(joy->js.rgdwPOV[0])
		{
			case -1:		//middle
				btnUp(xbUP);
				btnUp(xbDOWN);
				btnUp(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = 0;
				joy->DPadY = 0;
				break;
			case 0:			//up
				btnDown(xbUP);
				btnUp(xbDOWN);
				btnUp(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = 0;
				joy->DPadY = 1;
				break;
			case 4500:		//up-right
				btnDown(xbUP);
				btnUp(xbDOWN);
				btnUp(xbLEFT);
				btnDown(xbRIGHT);
				joy->DPadX = 1;
				joy->DPadY = 1;
				break;
			case 9000:		//right
				btnUp(xbUP);
				btnUp(xbDOWN);
				btnUp(xbLEFT);
				btnDown(xbRIGHT);
				joy->DPadX = 1;
				joy->DPadY = 0;
				break;
			case 13500:		//down-right
				btnUp(xbUP);
				btnDown(xbDOWN);
				btnUp(xbLEFT);
				btnDown(xbRIGHT);
				joy->DPadX = 1;
				joy->DPadY = -1;
				break;
			case 18000:		//down
				btnUp(xbUP);
				btnDown(xbDOWN);
				btnUp(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = 0;
				joy->DPadY = -1;
				break;
			case 22500:		//down-left
				btnUp(xbUP);
				btnDown(xbDOWN);
				btnDown(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = -1;
				joy->DPadY = -1;
				break;
			case 27000:		//left
				btnUp(xbUP);
				btnUp(xbDOWN);
				btnDown(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = -1;
				joy->DPadY = 0;
				break;
			case 31500:		//up-left
				btnDown(xbUP);
				btnUp(xbDOWN);
				btnDown(xbLEFT);
				btnUp(xbRIGHT);
				joy->DPadX = -1;
				joy->DPadY = 1;
				break;
			default:
				break;
		}
    }*/

//REPATABLE BUTTONS
    if(cameraMode)
	{
/*		if (keys[VK_PRIOR][DOWN])				// Is Page Up Being Pressed?
		{
			cam->pos.z -= 0.05f;				// If So, Move Into The Screen
		}

		if (keys[VK_NEXT][DOWN])				// Is Page Down Being Pressed?
		{
			cam->pos.z += 0.05f;				// If So, Move Towards The Viewer
		}

		if (keys[VK_UP][DOWN])				// Is Up Arrow Being Pressed?
		{
			xspeed-=0.01f;				// If So, Decrease xspeed
		}

		if (keys[VK_DOWN][DOWN])				// Is Down Arrow Being Pressed?
		{
			xspeed+=0.01f;				// If So, Increase xspeed
		}

		if (keys[VK_RIGHT][DOWN])				// Is Right Arrow Being Pressed?
		{
			yspeed+=0.01f;				// If So, Increase yspeed
		}

		if (keys[VK_LEFT][DOWN])				// Is Left Arrow Being Pressed?
		{
			yspeed-=0.01f;				// If So, Decrease yspeed
        }*/
	}
	else if(debugMode)
	{
        /*if(joy->activated)
		{
			if((canToggleBtn(xbUP) || canToggleBtn(xbDOWN)) && tP->parent != NULL)
			{
				if(tP->parent->numLeaf>0)
				{
					tP->parent->currentLeaf = mod(tP->parent->currentLeaf - joy->DPadY, tP->parent->numLeaf);
					tP = static_cast<pointerTree*>(&tP->parent->ptr[tP->parent->currentLeaf]);
				}
			}
			if(canToggleBtn(xbRIGHT) && (tP->numLeaf >0))
				tP = static_cast<pointerTree*>(&tP->ptr[tP->currentLeaf]);
			if(canToggleBtn(xbLEFT) && (tP->parent != NULL))
				tP = static_cast<pointerTree*>(tP->parent);
			
			//update values
			if(tP->type == tpFLOAT)
			{
				floatPtr = static_cast<float*>(tP->val);
				if((abs(joy->js.lY))>5)
					*floatPtr -= joy->js.lY/AXISMAX*.1f;
				if((abs(joy->js.lRy))>5)
					*floatPtr -= joy->js.lRy/AXISMAX*2.0f;
				if(isBtns(xbA))
					*floatPtr = floor(*floatPtr);
			}
			else if(tP->type == tpINT)
			{
				floatPtr = static_cast<float*>(tP->val);
				if((abs(joy->js.lY))>5)
					*floatPtr -= joy->js.lY/AXISMAX;
				if((abs(joy->js.lRy))>5)
					*floatPtr -= joy->js.lRy/AXISMAX*2.0f;
				if(isBtns(xbA))
					*floatPtr = floor(*floatPtr);
			}

			//display variables in current level
			if(tP->parent != NULL)
			{
				glColor3ub(55,55,55);
				glPrintHead(50,60,tP->parent->ptr[mod(tP->parent->currentLeaf-1,tP->parent->numLeaf)].ID.c_str(), DEFAULT, 10);
				glPrintHead(50,40,tP->parent->ptr[mod(tP->parent->currentLeaf+1,tP->parent->numLeaf)].ID.c_str(), DEFAULT, 10);
			}
			glColor3ub(230,230,230);
			glPrintHead(50,50,tP->ID.c_str(), DEFAULT, 10);

			//display variables in next level
			if(tP->numLeaf >0)
			{
				glColor3ub(170,170,170);
				glPrintHead(150,60,tP->ptr[mod(tP->currentLeaf-1,tP->numLeaf)].ID.c_str(), DEFAULT, 8);
				glPrintHead(150,50,tP->ptr[mod(tP->currentLeaf,tP->numLeaf)].ID.c_str(), DEFAULT, 8);
				glPrintHead(150,40,tP->ptr[mod(tP->currentLeaf+1,tP->numLeaf)].ID.c_str(), DEFAULT, 8);
			}
			
			if(tP->type == tpVECTOR2D)
			{
				floatvecPtr[0] = static_cast<float*>(tP->ptr[mod(tP->currentLeaf-1,tP->numLeaf)].val);
				floatvecPtr[1] = static_cast<float*>(tP->ptr[mod(tP->currentLeaf,tP->numLeaf)].val);
				floatvecPtr[2] = static_cast<float*>(tP->ptr[mod(tP->currentLeaf+1,tP->numLeaf)].val);

				glPrintHead(250,60, *floatvecPtr[0], DEFAULT, 7);
				glPrintHead(250,50, *floatvecPtr[1], DEFAULT, 7);
				glPrintHead(250,40, *floatvecPtr[2], DEFAULT, 7);
			}
			else if(tP->type == tpFLOAT)
			{
				floatPtr = static_cast<float*>(tP->val);
				glPrintHead(150,50, *floatPtr, DEFAULT, 8);
			}
        }*/
	}
	else
	{

	}

	return;
}


int getKey(playerNum numPlayer, Action act)
{
	int key = controlsK[numPlayer][act];
	
	return key;
}

void getKeys(playerNum numPlayer, int pKeys[])
{
	for(int i=0; i<8; i++)
		pKeys[i] = controlsK[numPlayer][i];
	
	return;
}
			
void getBtns(playerNum numPlayer, int pBtns[])
{
	for(int i=0; i<8; i++)
		pBtns[i] = controlsB[numPlayer][i];
	
	return;
}

bool playerPress(playerNum pnum, const int In)
{
	return (isKeys(controlsK[pnum][In]) || isBtns(controlsB[pnum][In]));
}

bool canPlayerToggle(playerNum pnum, const int In)
{
	return (canToggle(controlsK[pnum][In]) || canToggleBtn(controlsB[pnum][In]));
}
