#ifndef KEYS
#define KEYS

//#include <joystick\joystick.h>
#include <datastructs.h>

#include "objects.h"
#include "animation.h"
#include "world.h"

extern bool	keys[512][2];								// Array Used For The Keyboard Routine
extern bool	btns[12][2];								// Array Used For The Keyboard Routine
extern int controlsK[2][8];
extern int controlsB[2][8];	//joystick controls

extern bool	lp;									// L Pressed?
extern bool	fp;									// F Pressed?
extern bool	mp;									// M Pressed?
extern bool	cp;
extern bool	sp;									// Space Pressed?

enum keyStat{DOWN, HOLD};
enum buttons{btnLEFT, btnRIGHT, btnUP, btnDOWN, btnJUMP, btnATTACK, btnSHOOT, btnDASH};

void assignControls();

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

//void runKeys(level_c* lvl, joystick_s *joy, pointerTree* tP);
int getKey(playerNum numPlayer, actions act);
void getKeys(playerNum numPlayer, int pKeys[]);
void getBtns(playerNum numPlayer, int pBtns[]);
bool playerPress(playerNum pnum, const int In);
bool canPlayerToggle(playerNum pnum, const int In);

#endif
