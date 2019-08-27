#ifndef PLAYERKEYS
#define PLAYERKEYS

//#include <joystick\joystick.h>
#include <datastructs.h>

#include "objects.h"
#include "animation.h"
#include "level.h"

extern int controlsK[2][8];
extern int controlsB[2][8];	//joystick controls

extern bool	lp;									// L Pressed?
extern bool	fp;									// F Pressed?
extern bool	mp;									// M Pressed?
extern bool	cp;
extern bool	sp;									// Space Pressed?

enum buttons{btnLEFT, btnRIGHT, btnUP, btnDOWN, btnJUMP, btnATTACK, btnSHOOT, btnDASH};

void assignControls();

//void runKeys(Level* lvl, joystick_s *joy, pointerTree* tP);
int getKey(playerNum numPlayer, actions act);
void getKeys(playerNum numPlayer, int pKeys[]);
void getBtns(playerNum numPlayer, int pBtns[]);
bool playerPress(playerNum pnum, const int In);
bool canPlayerToggle(playerNum pnum, const int In);

#endif
