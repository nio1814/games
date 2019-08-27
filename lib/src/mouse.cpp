#include "mouse.h"

Mouse::Mouse(int width, int height)
{
    numButtons = 0;
    x = 0;
    y = 0;
    xOld = 0;
    yOld = 0;
    wheel = 0;
    wheelOld = 0;
    movedLastTime = false;
    screenWidth = width;
    screenHeight = height;
}

void Mouse::btnDown(const int btnIn)
{
    ButtonState* state = &m_btns[btnIn];
    state->held = state->down;
    state->down = true;

    /*if(m_btns[btnIn][bsDOWN])
        m_btns[btnIn][bsHOLD] = true;
	else
        m_btns[btnIn][bsDOWN] = true;*/

	return;
}

void Mouse::btnUp(const int btnIn)
{
    ButtonState* state = &m_btns[btnIn];
    state->held = false;
    state->down = false;

    /*m_btns[btnIn][bsHOLD] = false;
    m_btns[btnIn][bsDOWN] = false;*/

	return;
}

bool Mouse::isBtns(const int btnIn)
{
    /*bool isDown;
    isDown = m_btns[btnIn][bsDOWN];

    return isDown;*/
    return m_btns[btnIn].down;
}

bool Mouse::isHeldBtn(const int btnIn)
{
    /*bool ih = false;
	
    ih = m_btns[btnIn][bsHOLD];
	
    return ih;*/
    return m_btns[btnIn].held;
}

bool Mouse::canToggleBtn(const int btnIn)
{
	bool ct = false;
    ButtonState* state = &m_btns[btnIn];

//    if (m_btns[btnIn][bsDOWN] && !m_btns[btnIn][bsHOLD])				// L Key Being Pressed Not Held?
    if(state->down && !state->held)
	{
//        m_btns[btnIn][bsHOLD] = true;
        state->down = true;
		ct = true;
	}

	return ct;
}

void Mouse::updatePos(int xnew, int ynew)
{
    xOld = x;
    yOld = y;
    x = xnew;
    y = ynew;
	
    movedLastTime = true;
	
	return;
}

void Mouse::updatePos(QPoint pos)
{
    updatePos(pos.x(), pos.y());

    return;
}

bool Mouse::checkMouseMove()
{
    int screenMiddleX = screenWidth  >> 1;				// This is a binary shift to get half the width
    int screenMiddleY = screenHeight >> 1;				// This is a binary shift to get half the height
	
	bool didMove = false;
	
    if(!movedLastTime)
	{
        x = xOld;
        y = yOld;
//		SetCursorPos(screenMiddleX, screenMiddleY);
        xOld = x = screenMiddleX;
        yOld = y = screenMiddleY;
	}
	else
		didMove = true;
	
    movedLastTime = false;
	
	return didMove;
}
	
