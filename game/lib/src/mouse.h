#ifndef MOUSE
#define MOUSE

#include <windows.h>

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL WM_MOUSELAST+1 
    // Message ID for IntelliMouse wheel
#endif

#define DEFMOUSETHROTTLEX .07f
#define DEFMOUSETHROTTLEY .12f

enum btnStat{bsDOWN, bsHOLD};
enum mouseBtns{mbLBTN, mbRBTN, mbMBTN};

struct mouse_s
{
	POINT msPoint;
	int numButtons;
	int x,y,xOld,yOld;
	int wheel, wheelOld;
	bool btns[3][2];
	bool movedLastTime;
	int screenWidth, screenHeight;
	
	mouse_s(int width, int height)
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
};

void btnDownM(const int btnIn, mouse_s* ms);
void btnUpM(const int btnIn, mouse_s* ms);
bool isBtnsM(const int btnIn, mouse_s* ms);
bool isHeldBtnM(const int btnIn, mouse_s* ms);
bool canToggleBtnM(const int btnIn, mouse_s* ms);
void updatePosM(int xnew, int ynew, mouse_s* ms);
bool checkMouseMove(mouse_s* ms);

#endif