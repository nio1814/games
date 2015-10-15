#ifndef MOUSE
#define MOUSE

#include <qpoint.h>
#include <qhash.h>

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL WM_MOUSELAST+1 
    // Message ID for IntelliMouse wheel
#endif

#define DEFMOUSETHROTTLEX .07f
#define DEFMOUSETHROTTLEY .12f

struct ButtonState{
    bool down;
    bool held;

    ButtonState() : down(false), held(false) {};
};

class Mouse
{
public:
    Mouse(int width, int height);

    void btnDown(const int btnIn);
    void btnUp(const int btnIn);
    bool isBtns(const int btnIn);
    bool isHeldBtn(const int btnIn);
    bool canToggleBtn(const int btnIn);
    void updatePos(int xnew, int ynew);
    void updatePos(QPoint pos);
    bool checkMouseMove();

    QPoint msPoint;
	int numButtons;
	int x,y,xOld,yOld;
	int wheel, wheelOld;
    QHash<int,ButtonState> m_btns;
	bool movedLastTime;
	int screenWidth, screenHeight;
};

#endif
