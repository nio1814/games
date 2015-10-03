//#include <windows.h>								// Header File For Windows
#include <stdio.h>									// Header File For Standard Input/Output

#include "keys.h"

bool	keys[512][2] = {false};								// Array Used For The Keyboard Routine
bool	btns[12][2] = {false};
int		controls[2][8];

bool	sp;									// Space Pressed?	

void keyDown(const int keyIn)
{
	if(keys[keyIn][DOWN])
		keys[keyIn][HOLD] = true;
	else
		keys[keyIn][DOWN] = true;

	return;
}

void keyUp(const int keyIn)
{
		keys[keyIn][HOLD] = false;
		keys[keyIn][DOWN] = false;

	return;
}

bool isKeys(const int keyIn)
{
	bool isDown;
	isDown = keys[keyIn][DOWN];

	return isDown;
}

bool isHeld(const int keyIn)
{
	bool isHeld;
	isHeld = keys[keyIn][HOLD];

	return isHeld;
}			

bool canToggle(const int keyIn)
{
	bool ct = false;

	if (keys[keyIn][DOWN] && !keys[keyIn][HOLD])				// L Key Being Pressed Not Held?
	{
		keys[keyIn][HOLD] = true;
		ct = true;
	}

	return ct;
}

void btnDown(const int btnIn)
{
	if(btns[btnIn][DOWN])
		btns[btnIn][HOLD] = true;
	else
		btns[btnIn][DOWN] = true;

	return;
}

void btnUp(const int btnIn)
{
		btns[btnIn][HOLD] = false;
		btns[btnIn][DOWN] = false;

	return;
}

bool isBtns(const int btnIn)
{
	bool isDown;
	isDown = btns[btnIn][DOWN];

	return isDown;
}

bool isHeldBtn(const int btnIn);

bool canToggleBtn(const int btnIn)
{
	bool ct = false;

	if (btns[btnIn][DOWN] && !btns[btnIn][HOLD])				// L Key Being Pressed Not Held?
	{
		btns[btnIn][HOLD] = true;
		ct = true;
	}

	return ct;
}
