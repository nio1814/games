#include "mouse.h"

void btnDownM(const int btnIn, mouse_s* ms)
{
	if(ms->btns[btnIn][bsDOWN])
		ms->btns[btnIn][bsHOLD] = true;
	else
		ms->btns[btnIn][bsDOWN] = true;

	return;
}

void btnUpM(const int btnIn, mouse_s* ms)
{
		ms->btns[btnIn][bsHOLD] = false;
		ms->btns[btnIn][bsDOWN] = false;

	return;
}

bool isBtnsM(const int btnIn, mouse_s* ms)
{
	bool isDown;
	isDown = ms->btns[btnIn][bsDOWN];

	return isDown;
}

bool isHeldBtnM(const int btnIn, mouse_s* ms)
{
	bool ih = false;
	
	ih = ms->btns[btnIn][bsHOLD];
	
	return ih;
}

bool canToggleBtnM(const int btnIn, mouse_s* ms)
{
	bool ct = false;

	if (ms->btns[btnIn][bsDOWN] && !ms->btns[btnIn][bsHOLD])				// L Key Being Pressed Not Held?
	{
		ms->btns[btnIn][bsHOLD] = true;
		ct = true;
	}

	return ct;
}

void updatePosM(int xnew, int ynew, mouse_s* ms)
{
	ms->xOld = ms->x;
	ms->yOld = ms->y;
	ms->x = xnew;
	ms->y = ynew;
	
	ms->movedLastTime = true;
	
	return;
}

bool checkMouseMove(mouse_s* ms)
{
	int screenMiddleX = ms->screenWidth  >> 1;				// This is a binary shift to get half the width
	int screenMiddleY = ms->screenHeight >> 1;				// This is a binary shift to get half the height
	
	bool didMove = false;
	
	if(!ms->movedLastTime)
	{
		ms->x = ms->xOld;
		ms->y = ms->yOld;
		SetCursorPos(screenMiddleX, screenMiddleY);
		ms->xOld = ms->x = screenMiddleX;
		ms->yOld = ms->y = screenMiddleY;
	}
	else
		didMove = true;
	
	ms->movedLastTime = false;	
	
	return didMove;
}
	