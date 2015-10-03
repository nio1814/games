#ifndef KEYS
#define KEYS

extern bool	keys[512][2];								// Array Used For The Keyboard Routine(down,held)
extern bool	btns[12][2];								// Array Used For The Keyboard Routine
extern int controls[2][8];

extern bool	lp;									// L Pressed?
extern bool	fp;									// F Pressed?
extern bool	mp;									// M Pressed?
extern bool	cp;
extern bool	sp;									// Space Pressed?

enum keyStat{DOWN, HOLD};

void keyDown(const int keyIn);
void keyUp(const int keyIn);
bool isKeys(const int keyIn);
bool isHeld(const int keyIn);
bool canToggle(const int keyIn);

void btnDown(const int btnIn);
void btnUp(const int btnIn);
bool isBtns(const int btnIn);
bool isHeldBtn(const int btnIn);
bool canToggleBtn(const int btnIn);


#endif
