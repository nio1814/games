#include "keys.h"

//#include <windows.h>								// Header File For Windows
#include <stdio.h>									// Header File For Standard Input/Output
#include <qhash.h>
#include <Qt>

//bool	keys[512][2] = {false};								// Array Used For The Keyboard Routine
bool	btns[12][2] = {false};
int		controls[2][8];

bool	sp;									// Space Pressed?	

struct KeyState {
	bool down;
	bool held;

	KeyState() : down(false), held(false){};
};

QHash<int,KeyState> keys;

void keyDown(const int keyIn)
{
	KeyState* state = &keys[keyIn];
	state->held = state->down;
	state->down = true;

	/*if(keys[keyIn][DOWN])
		keys[keyIn][HOLD] = true;
	else
		keys[keyIn][DOWN] = true;*/

	return;
}

void keyUp(const int keyIn)
{
	KeyState* state = &keys[keyIn];
	state->down = false;
	state->held = false;

		/*keys[keyIn][HOLD] = false;
		keys[keyIn][DOWN] = false;*/

	return;
}

bool isKeys(const int keyIn)
{
//	bool isDown;
//	isDown = keys[keyIn][DOWN];

	return keys[keyIn].down;
}

bool isHeld(const int keyIn)
{
//	bool isHeld;
//	isHeld = keys[keyIn][HOLD];

	return keys[keyIn].held;
}			

bool canToggle(const int keyIn)
{
	bool ct = false;

//	if (keys[keyIn][DOWN] && !keys[keyIn][HOLD])				// L Key Being Pressed Not Held?
	if (keys[keyIn].down && !keys[keyIn].held)
	{
//		keys[keyIn][HOLD] = true;
		keys[keyIn].held = true;
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
