//#include <windows.h>					// Header File For Windows
#include <stdio.h>						// Header File For Standard Input/Output
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <math.h>						// Header File For Windows Math Library
//#include <gl\gl.h>						// Header File For The OpenGL32 Library
//#include <gl\glu.h>
#include <string>

#include "vector3d.h"
#include "keys.h"

#include "animation.h"
#include "objects.h"
#include "TGA.h"
#include "masking.h"
#include "movement.h"

extern int DEFRUNFRAMESPD = 17;

animData_s tailsT;

animData_s **playerTextures;
animData_s **objectTextures;
animData_s **shotTextures;

void doTextures()
{		
	playerTextures = new animData_s*[20];
	objectTextures = new animData_s*[20];
	shotTextures = new animData_s*[5];

	//create animdata for each type of object
	for(int i=0; i<NUMCHARACTERS; i++)
	{
		playerTextures[i] = new animData_s;
	}
	for(int i=0; i<NUMSHOTTYPES; i++)
	{
		shotTextures[i] = new animData_s;
	}
	for(int i=0; i<NUMBLOCKTYPES; i++)
	{
		objectTextures[i] = new animData_s;
	}

	//load pics for each animdata
	//ZERO
	playerTextures[ZERO]->person = ZERO;
//	TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zero.tga", 0);

	playerTextures[ZERO]->frameData[actRUN][animSTART] = 1;
	playerTextures[ZERO]->frameData[actRUN][numFRAMES] = 11;
	playerTextures[ZERO]->frameData[actRUN][repeatFRAME] = 2;
	playerTextures[ZERO]->frameData[actRUN][lastFRAME] = 11;
	playerTextures[ZERO]->maxSpeed = 5.0f;
    /*TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun1.tga", 1);		// First Mask
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun2.tga", 2);
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun3.tga", 3);
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun4.tga", 4);
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun5.tga", 5);
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun6.tga", 6);		//up to 6 sized correctly
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun7.tga", 7);
	TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun8.tga", 8);
	TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun9.tga", 9);
	TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun10.tga", 10);
    TGA_Texture(playerTextures[ZERO], "Data/img/characters/zero/zeroRun11.tga", 11);*/

	playerTextures[ZERO]->frameData[actATTACK1][animSTART] = 12;
	playerTextures[ZERO]->frameData[actATTACK1][numFRAMES] = 11;
	playerTextures[ZERO]->frameData[actATTACK1][lastFRAME] = 22;
	playerTextures[ZERO]->frameData[actATTACK1][minstopFRAME] = 22;
    /*TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk1.tga", 12);			// First Mask
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk2.tga", 13, 0.63461f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk3.tga", 14, 0.63461f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk4.tga", 15, 0.6458333f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk5.tga", 16, 0.296875f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk6.tga", 17, 0.225f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk7.tga", 18, 0.225f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk8.tga", 19, 0.225f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk9.tga", 20, 0.23684210f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk10.tga", 21, 0.25714285f);
    TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroAtk11.tga", 22, 0.4f);*/
	
	playerTextures[ZERO]->frameData[actJUMP][animSTART] = 23;
	playerTextures[ZERO]->frameData[actJUMP][numFRAMES] = 7;
	playerTextures[ZERO]->frameData[actJUMP][repeatFRAME] = 27;
	playerTextures[ZERO]->frameData[actJUMP][lastFRAME] = 29;
    /*TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump1.tga", 23);			// First Mask
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump2.tga", 24);	
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump3.tga", 25);	
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump4.tga", 26);	
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump5.tga", 27);	
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump6.tga", 28);
    TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJump7.tga", 29);*/

	playerTextures[ZERO]->frameData[actWALL][animSTART] = 30;
	playerTextures[ZERO]->frameData[actWALL][numFRAMES] = 1;
	playerTextures[ZERO]->frameData[actWALL][lastFRAME] = 30;
	playerTextures[ZERO]->canWallClimb = true;
    /*TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroWall2.tga", 30);
    TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroWall1.tga", 31);*/

	playerTextures[ZERO]->frameData[actDUCK][animSTART] = 32;
	playerTextures[ZERO]->frameData[actDUCK][numFRAMES] = 1;
	playerTextures[ZERO]->frameData[actDUCK][lastFRAME] = 32;
//	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroDuck.tga", 32);

	playerTextures[ZERO]->frameData[actHURT][animSTART] = 33;
	playerTextures[ZERO]->frameData[actHURT][numFRAMES] = 1;
	playerTextures[ZERO]->frameData[actHURT][lastFRAME] = 33;
//	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroHurt1.tga", 33);

	playerTextures[ZERO]->frameData[actJUMPATK][animSTART] = 34;
	playerTextures[ZERO]->frameData[actJUMPATK][numFRAMES] = 12;
	playerTextures[ZERO]->frameData[actJUMPATK][lastFRAME] = 45;
	playerTextures[ZERO]->frameData[actJUMPATK][minstopFRAME] = 45;
    /*TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk1.tga", 34);			// First Mask
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk2.tga", 35, 0.4375f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk3.tga", 36, 0.5588235f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk4.tga", 37, 0.622222f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk5.tga", 38, 0.7045f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk6.tga", 39, 0.333333f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk7.tga", 40, 0.236111111f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk8.tga", 41, 0.222222222f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk9.tga", 42, 0.208333333f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk10.tga", 43, 0.2205882352f);
	TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk11.tga", 44, 0.241935483f);
    TGA_Texture(playerTextures[ZERO],  "Data/img/characters/zero/zeroJumpAtk12.tga", 45, 0.43243243243f);*/

	playerTextures[ZERO]->lastFrame = 45;

	//GOKU
	playerTextures[GOKU]->person = GOKU;
//	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/goku.tga", 0);

	playerTextures[GOKU]->frameData[actRUN][animSTART] = 1;
	playerTextures[GOKU]->frameData[actRUN][numFRAMES] = 3;
	playerTextures[GOKU]->frameData[actRUN][repeatFRAME] = 3;
	playerTextures[GOKU]->frameData[actRUN][animSPEED] = 60;
/*	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuFly1.tga", 1);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuFly2.tga", 2);
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuFly3.tga", 3);*/

	playerTextures[GOKU]->frameData[actATTACK1][animSTART] = 4;
	playerTextures[GOKU]->frameData[actATTACK1][numFRAMES] = 4;
	playerTextures[GOKU]->frameData[actATTACK1][minstopFRAME] = 7;
    /*TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuAttack1.tga", 4);playerTextures[GOKU]->centers[4] = 0.5384615384f;
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuAttack2.tga", 5);playerTextures[GOKU]->centers[5] = 0.45f;
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuAttack3.tga", 6);playerTextures[GOKU]->centers[6] = 0.34375;
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuAttack4.tga", 7);playerTextures[GOKU]->centers[7] = 0.1470588235f;*/
	
	playerTextures[GOKU]->frameData[actJUMP][animSTART] = 8;
	playerTextures[GOKU]->frameData[actJUMP][numFRAMES] = 1;
	playerTextures[GOKU]->frameData[actJUMP][repeatFRAME] = 8;
//	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuJump1.tga", 8);

	playerTextures[GOKU]->frameData[actDUCK][animSTART] = 9;
	playerTextures[GOKU]->frameData[actDUCK][numFRAMES] = 2;
    /*TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuDuck1.tga", 9);
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuDuck2.tga", 10);*/

	playerTextures[GOKU]->frameData[actHURT][animSTART] = 11;
	playerTextures[GOKU]->frameData[actHURT][numFRAMES] = 4;
	playerTextures[GOKU]->frameData[actHURT][minstopFRAME] = 14;
/*	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuHurt1.tga", 11);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuHurt2.tga", 12);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuHurt3.tga", 13);
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuHurt4.tga", 14);*/

	playerTextures[GOKU]->frameData[actSHOOT][animSTART] = 15;
	playerTextures[GOKU]->frameData[actSHOOT][numFRAMES] = 7;
	playerTextures[GOKU]->frameData[actSHOOT][animSPEED] = 130;
	playerTextures[GOKU]->canShoot = true;
/*	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot1.tga", 15);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot2.tga", 16);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot3.tga", 17);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot4.tga", 18);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot5.tga", 19);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot6.tga", 20);
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuShoot7.tga", 21);*/

	playerTextures[GOKU]->frameData[actJUMPATK][animSTART] = 22;
	playerTextures[GOKU]->frameData[actJUMPATK][numFRAMES] = 4;
	//playerTextures[GOKU]->frameData[actJUMPATK][repeatFRAME] = 7;
    /*TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuJumpPunch1.tga", 22);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuJumpPunch2.tga", 23);
	TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuJumpPunch3.tga", 24);
    TGA_Texture(playerTextures[GOKU], "Data/img/characters/goku/gokuJumpPunch4.tga", 25);*/
	
	playerTextures[GOKU]->lastFrame = 25;

	//GOKU SHOT
    /*TGA_Texture(shotTextures[GOKUSHOT], "Data/img/characters/goku/shot/gokuShot1.tga", 0);
    TGA_Texture(shotTextures[GOKUSHOT], "Data/img/characters/goku/shot/gokuShot2.tga", 1);*/

	shotTextures[GOKUSHOT]->lastFrame = 1;

	//MMX
	playerTextures[MMX]->person = MMX;
//	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmx.tga", 0);
	
	playerTextures[MMX]->frameData[actDUCK][animSTART] = 1;
	playerTextures[MMX]->frameData[actDUCK][numFRAMES] = 1;
	playerTextures[MMX]->frameData[actDUCK][lastFRAME] = 1;
//	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxDuck.tga", 1);

	playerTextures[MMX]->frameData[actRUN][animSTART] = 2;
	playerTextures[MMX]->frameData[actRUN][numFRAMES] = 11;
	playerTextures[MMX]->frameData[actRUN][repeatFRAME] = 3;
	playerTextures[MMX]->frameData[actRUN][lastFRAME] = 12;
    /*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun1.tga", 2);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun2.tga", 3);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun3.tga", 4);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun4.tga", 5);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun5.tga", 6);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun6.tga", 7);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun7.tga", 8);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun8.tga", 9);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun9.tga", 10);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun10.tga", 11);
    TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRun11.tga", 12);*/

	playerTextures[MMX]->frameData[actJUMP][animSTART] = 13;
	playerTextures[MMX]->frameData[actJUMP][numFRAMES] = 5;
	playerTextures[MMX]->frameData[actJUMP][repeatFRAME] = 16;
	playerTextures[MMX]->frameData[actJUMP][lastFRAME] = 17;
    /*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJump1.tga", 13);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJump2.tga", 14);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJump3.tga", 15);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJump5.tga", 16);
    TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJump4.tga", 17);*/

	/*playerTextures[MMX]->frameData[actATTACK1][animSTART] = 18;
	playerTextures[MMX]->frameData[actATTACK1][numFRAMES] = 1;
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxAtk1.tga", 18);*/

	playerTextures[MMX]->frameData[actSHOOT][animSTART] = 19;
	playerTextures[MMX]->frameData[actSHOOT][numFRAMES] = 2;
	playerTextures[MMX]->frameData[actSHOOT][lastFRAME] = 20;
    /*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxShoot1.tga", 19);
    TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxShoot2.tga", 20);*/

	playerTextures[MMX]->frameData[actJUMPSHOOT][animSTART] = 21;
	playerTextures[MMX]->frameData[actJUMPSHOOT][numFRAMES] = 5;
	playerTextures[MMX]->frameData[actJUMPSHOOT][repeatFRAME] = 25;
	playerTextures[MMX]->frameData[actJUMPSHOOT][lastFRAME] = 17;
	playerTextures[MMX]->canShoot = true;
	/*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJumpShoot1.tga", 21);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJumpShoot2.tga", 22);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJumpShoot3.tga", 23);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJumpShoot4.tga", 24);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxJumpShoot5.tga", 25);

	playerTextures[MMX]->frameData[actRUNATK][animSTART] = 25;
	playerTextures[MMX]->frameData[actRUNATK][numFRAMES] = 1;
	playerTextures[MMX]->frameData[actRUNATK][lastFRAME] = 31;
	/*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot1.tga", 26);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot1.tga", 27);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot2.tga", 28);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot3.tga", 29);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot4.tga", 30);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxRunShoot5.tga", 31);

	playerTextures[MMX]->frameData[actWALL][animSTART] = 32;
	playerTextures[MMX]->frameData[actWALL][numFRAMES] = 1;
	playerTextures[MMX]->frameData[actWALL][lastFRAME] = 32;
	playerTextures[MMX]->canWallClimb = true;
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxWall1.tga", 32);

	playerTextures[MMX]->frameData[actHURT][animSTART] = 33;
	playerTextures[MMX]->frameData[actHURT][numFRAMES] = 3;
	playerTextures[MMX]->frameData[actHURT][minstopFRAME] = 35;
	/*TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxHurt1.tga", 33);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxHurt2.tga", 34);
	TGA_Texture(playerTextures[MMX], "Data/img/characters/mmx/mmxHurt3.tga", 35);

	playerTextures[MMX]->lastFrame = 35;

	shotTextures[MMXSHOT]->sType = MMXSHOT;
	shotTextures[MMXSHOT]->frameData[actNONE][animSTART] = 0;
	shotTextures[MMXSHOT]->frameData[actNONE][numFRAMES] = 3;
	shotTextures[MMXSHOT]->frameData[actNONE][repeatFRAME] = 0;
    /*TGA_Texture(shotTextures[MMXSHOT], "Data/img/characters/mmx/shot/mmxShot1.tga", 0);
	TGA_Texture(shotTextures[MMXSHOT], "Data/img/characters/mmx/shot/mmxShot2.tga", 1);
    TGA_Texture(shotTextures[MMXSHOT], "Data/img/characters/mmx/shot/mmxShot3.tga", 2);*/

	//SPIDERMAN
	playerTextures[SPIDEY]->person = SPIDEY;
//	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spidey.tga", 0);
	
	playerTextures[SPIDEY]->frameData[actRUN][animSTART] = 1;
	playerTextures[SPIDEY]->frameData[actRUN][numFRAMES] = 9;
	playerTextures[SPIDEY]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[SPIDEY]->maxSpeed = 3.0f;
/*	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun9.tga", 1);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun8.tga", 2);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun7.tga", 3);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun6.tga", 4);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun5.tga", 5);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun4.tga", 6);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun3.tga", 7);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun2.tga", 8);
    TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyRun1.tga", 9);*/

	playerTextures[SPIDEY]->frameData[actJUMP][animSTART] = 10;
	playerTextures[SPIDEY]->frameData[actJUMP][numFRAMES] = 9;
	playerTextures[SPIDEY]->frameData[actJUMP][repeatFRAME] = 16;
	playerTextures[SPIDEY]->frameData[actJUMP][animSPEED] = 90;
	playerTextures[SPIDEY]->jumpStrength = 1.8f;
	/*TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump1.tga", 10);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump2.tga", 11);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump3.tga", 12);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump4.tga", 13);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump5.tga", 14);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump6.tga", 15);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump7.tga", 16);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump8.tga", 17);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyJump9.tga", 18);

	playerTextures[SPIDEY]->frameData[actATTACK1][animSTART] = 19;
	playerTextures[SPIDEY]->frameData[actATTACK1][numFRAMES] = 7;
	playerTextures[SPIDEY]->frameData[actATTACK1][animSPEED] = 130;
	playerTextures[SPIDEY]->frameData[actATTACK1][minstopFRAME] = 25;
	/*TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk1.tga", 19, 0.68f);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk2.tga", 20, 0.5625f);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk3.tga", 21, 0.301470f);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk4.tga", 22, 0.290322f);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk5.tga", 23, 0.42857f);
	TGA_Texture(playerTextures[SPIDEY], "Data/img/characters/spidey/spideyAtk6.tga", 24, 0.276315f);*/

	playerTextures[SPIDEY]->lastFrame = 25;

	//TAILS
	playerTextures[TAILS]->person = TAILS;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails.tga", 0, 0.756097f);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails2.tga", 1);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails3.tga", 2);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails4.tga", 3);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails5.tga", 4);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails6.tga", 5);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails7.tga", 6);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tails8.tga", 7);*/
	
	playerTextures[TAILS]->frameData[actATTACK1][animSTART] = 8;
	playerTextures[TAILS]->frameData[actATTACK1][numFRAMES] = 9;
	playerTextures[TAILS]->frameData[actATTACK1][repeatFRAME] = 8;
	playerTextures[TAILS]->frameData[actATTACK1][minstopFRAME] = 16;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk1.tga", 8);playerTextures[TAILS]->centers[8] = 0.8387096f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk2.tga", 9);playerTextures[TAILS]->centers[9] = 0.5526315f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk3.tga", 10);playerTextures[TAILS]->centers[10] = 0.3823529f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk4.tga", 11);playerTextures[TAILS]->centers[11] = 0.33928571f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk5.tga", 12);playerTextures[TAILS]->centers[12] = 0.2542372f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk6.tga", 13);playerTextures[TAILS]->centers[13] = 0.2666666f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk7.tga", 14);playerTextures[TAILS]->centers[14] = 0.2666666f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk8.tga", 15);playerTextures[TAILS]->centers[15] = 0.2666666f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsAtk9.tga", 16);playerTextures[TAILS]->centers[16] = 0.65625f;*/

	playerTextures[TAILS]->frameData[actJUMP][animSTART] = 17;
	playerTextures[TAILS]->frameData[actJUMP][numFRAMES] = 8;
	playerTextures[TAILS]->frameData[actJUMP][repeatFRAME] = 17;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk1.tga", 17);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk2.tga", 18);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk3.tga", 19);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk4.tga", 20);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk5.tga", 21);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk6.tga", 22);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk7.tga", 23);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsJumpAtk8.tga", 24);*/

	playerTextures[TAILS]->frameData[actDUCK][animSTART] = 25;
	playerTextures[TAILS]->frameData[actDUCK][numFRAMES] = 3;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsDuck1.tga", 25);playerTextures[TAILS]->centers[25] = 0.71875f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsDuck2.tga", 26);playerTextures[TAILS]->centers[26] = 0.67567f;
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsDuck3.tga", 27);playerTextures[TAILS]->centers[27] = 0.69767f;*/

	playerTextures[TAILS]->frameData[actRUN][animSTART] = 28;
	playerTextures[TAILS]->frameData[actRUN][numFRAMES] = 22;
	playerTextures[TAILS]->frameData[actRUN][repeatFRAME] = 39;
	playerTextures[TAILS]->maxSpeed = 6.0f;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun1.tga", 28);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun2.tga", 29);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun3.tga", 30);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun4.tga", 31);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun5.tga", 32);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun6.tga", 33);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun7.tga", 34);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun8.tga", 35);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun9.tga", 36);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun10.tga", 37);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun11.tga", 38);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun12.tga", 39);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun13.tga", 40);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun14.tga", 41);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun15.tga", 42);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun16.tga", 43);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun17.tga", 44);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun18.tga", 45);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun19.tga", 46);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun20.tga", 47);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun21.tga", 48);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsRun22.tga", 49);

	playerTextures[TAILS]->frameData[actPUSH][animSTART] = 50;
	playerTextures[TAILS]->frameData[actPUSH][numFRAMES] = 8;
	playerTextures[TAILS]->frameData[actPUSH][repeatFRAME] = 50;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush1.tga", 50);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush2.tga", 51);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush3.tga", 52);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush4.tga", 53);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush5.tga", 54);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush6.tga", 55);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush7.tga", 56);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsPush8.tga", 57);

	playerTextures[TAILS]->frameData[actHURT][animSTART] = 58;
	playerTextures[TAILS]->frameData[actHURT][numFRAMES] = 5;
	playerTextures[TAILS]->frameData[actHURT][minstopFRAME] = 62;
	/*TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsHurt1.tga", 58, 0.647058823f);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsHurt2.tga", 59, 0.6842105263f);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsHurt3.tga", 60, 0.62857142f);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsHurt4.tga", 61, 0.60606060f);
	TGA_Texture(playerTextures[TAILS], "Data/img/characters/tails/tailsHurt5.tga", 62, 0.56666666f);*/

	playerTextures[TAILS]->lastFrame = 52;

	//TAILS' tails
	tailsT.frameData[actATTACK1][animSTART] = 0;
	tailsT.frameData[actATTACK1][numFRAMES] = 9;
	tailsT.frameData[actATTACK1][repeatFRAME] = 1;
	/*TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail1.tga", 0);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail2.tga", 1);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail3.tga", 2);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail4.tga", 3);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail5.tga", 4);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail6.tga", 5);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail7.tga", 6);
	TGA_Texture(&tailsT, "Data/img/characters/tails/tail/tail8.tga", 7);*/

	tailsT.lastFrame = 7;

	//SONIC
	playerTextures[SONIC]->person = SONIC;
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonic.tga", 0);

	playerTextures[SONIC]->frameData[actRUN][animSTART] = 1;
	playerTextures[SONIC]->frameData[actRUN][numFRAMES] = 11;
	playerTextures[SONIC]->frameData[actRUN][repeatFRAME] = 9;
	playerTextures[SONIC]->frameData[actRUN][animSPEED] = 30;
	playerTextures[SONIC]->maxSpeed = 7.0f;
	/*TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun1.tga", 1);			// First Mask
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun2.tga", 2);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun3.tga", 3);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun4.tga", 4);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun5.tga", 5);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun6.tga", 6);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun7.tga", 7);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun8.tga", 8);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun9.tga", 9);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun10.tga", 10);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicRun11.tga", 11);*/

	playerTextures[SONIC]->frameData[actJUMP][animSTART] = 12;
	playerTextures[SONIC]->frameData[actJUMP][numFRAMES] = 5;
	playerTextures[SONIC]->frameData[actJUMP][repeatFRAME] = 12;
	playerTextures[SONIC]->frameData[actJUMP][animSPEED] = 200;
	playerTextures[SONIC]->jumpStrength = 1.4f;
/*	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicJump1.tga", 12);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicJump2.tga", 13);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicJump3.tga", 14);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicJump4.tga", 15);
    TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicJump5.tga", 16);*/

	playerTextures[SONIC]->frameData[actDUCK][animSTART] = 17;
	playerTextures[SONIC]->frameData[actDUCK][numFRAMES] = 2;
    /*TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicDuck1.tga", 17);
    TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicDuck2.tga", 18);*/

	playerTextures[SONIC]->frameData[actHURT][animSTART] = 19;
	playerTextures[SONIC]->frameData[actHURT][numFRAMES] = 2;
	playerTextures[SONIC]->frameData[actHURT][minstopFRAME] = 20;
	/*TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicHurt1.tga", 19);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicHurt2.tga", 20);*/

	playerTextures[SONIC]->frameData[actPUSH][animSTART] = 21;
	playerTextures[SONIC]->frameData[actPUSH][numFRAMES] = 1;
	playerTextures[SONIC]->frameData[actPUSH][repeatFRAME] = 21;
	/*TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicPush1.tga", 21);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicPush2.tga", 22);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicPush3.tga", 23);
	TGA_Texture(playerTextures[SONIC], "Data/img/characters/sonic/sonicPush4.tga", 24);*/

	playerTextures[SONIC]->lastFrame = 24;
	
	//PETER
	playerTextures[PETER]->person = PETER;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peter3.tga", 0);
	
	playerTextures[PETER]->frameData[actRUN][animSTART] = 1;
	playerTextures[PETER]->frameData[actRUN][numFRAMES] = 9;
	playerTextures[PETER]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[PETER]->frameData[actRUN][animSPEED] = 40;
    /*TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk1.tga", 1);//playerTextures[PETER]->centers[1] = 0.374074074;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk2.tga", 2);//playerTextures[PETER]->centers[2] = 0.4097222;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk3.tga", 3);//playerTextures[PETER]->centers[3] = 0.45192307;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk4.tga", 4);//playerTextures[PETER]->centers[4] = 0.44814814;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk5.tga", 5);//playerTextures[PETER]->centers[5] = 0.43333333;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk6.tga", 6);//playerTextures[PETER]->centers[6] = 0.347222222;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk7.tga", 7);//playerTextures[PETER]->centers[7] = 0.3691588;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk8.tga", 8);//playerTextures[PETER]->centers[8] = 0.4558823;
    TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWalk9.tga", 9);//playerTextures[PETER]->centers[9] = 0.90256410;*/
	
	playerTextures[PETER]->frameData[actJUMP][animSTART] = 10;
	playerTextures[PETER]->frameData[actJUMP][numFRAMES] = 6;
	playerTextures[PETER]->frameData[actJUMP][repeatFRAME] = 14;
    /*TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump1.tga", 10);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump2.tga", 11);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump3.tga", 12);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump4.tga", 13);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump5.tga", 14);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump6.tga", 15);
    TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterJump7.tga", 16);*/
	
	playerTextures[PETER]->frameData[actWALL][animSTART] = 17;
	playerTextures[PETER]->frameData[actWALL][numFRAMES] = 1;
	playerTextures[PETER]->canWallClimb = true;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterWall.tga", 17);
	
	playerTextures[PETER]->frameData[actHURT][animSTART] = 18;
	playerTextures[PETER]->frameData[actHURT][numFRAMES] = 4;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterMatrix1.tga", 18);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterMatrix2.tga", 19);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterMatrix3.tga", 20);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterMatrix4.tga", 21);
	
	playerTextures[PETER]->frameData[actDUCK][animSTART] = 22;
	playerTextures[PETER]->frameData[actDUCK][numFRAMES] = 4;
    /*TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterDuck1.tga", 22);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterDuck2.tga", 23);
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterDuck3.tga", 24);
    TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterDuck4.tga", 25);*/
	
	playerTextures[PETER]->frameData[actATTACK1][animSTART] = 26;
	playerTextures[PETER]->frameData[actATTACK1][numFRAMES] = 5;
	playerTextures[PETER]->frameData[actATTACK1][minstopFRAME] = 30;
/*	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterPaddleAtk1.tga", 26);playerTextures[PETER]->centers[26] = 0.181434599f;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterPaddleAtk2.tga", 27);playerTextures[PETER]->centers[27] = 0.18222222f;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterPaddleAtk3.tga", 28);playerTextures[PETER]->centers[28] = 0.181034482f;
	TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterPaddleAtk4.tga", 29);playerTextures[PETER]->centers[29] = 0.2f;
    TGA_Texture(playerTextures[PETER], "Data/img/characters/peter/peterPaddleAtk5.tga", 30);playerTextures[PETER]->centers[30] = 0.185022026f;*/
	
	playerTextures[PETER]->lastFrame = 30;

	//GOOMBA
	playerTextures[GOOMBA]->person = GOOMBA;
	playerTextures[GOOMBA]->jumpStrength = 0.0f;
//	TGA_Texture(playerTextures[GOOMBA], "Data/img/characters/goomba/goomba1.tga", 0);
	
	playerTextures[GOOMBA]->frameData[actRUN][animSTART] = 1;
	playerTextures[GOOMBA]->frameData[actRUN][numFRAMES] = 2;
	playerTextures[GOOMBA]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[GOOMBA]->frameData[actRUN][animSPEED] = 50;
	playerTextures[GOOMBA]->maxSpeed = 2.0f;
	TGA_Texture(playerTextures[GOOMBA], "Data/img/characters/goomba/goomba2.tga", 1);
	TGA_Texture(playerTextures[GOOMBA], "Data/img/characters/goomba/goomba1.tga", 2);
	
	//DONKEY KONG
	playerTextures[DK]->person = DK;
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dk.tga", 0);
	
	playerTextures[DK]->frameData[actRUN][animSTART] = 1;
	playerTextures[DK]->frameData[actRUN][numFRAMES] = 14;
	playerTextures[DK]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[DK]->frameData[actRUN][animSPEED] = 80;
	playerTextures[DK]->maxSpeed = 3.0f;
    /*TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk1.tga", 1);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk2.tga", 2);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk3.tga", 3);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk4.tga", 4);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk5.tga", 5);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk6.tga", 6);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk7.tga", 7);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk8.tga", 8);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk9.tga", 9);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk10.tga", 10);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk11.tga", 11);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk12.tga", 12);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk13.tga", 13);
    TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkWalk14.tga", 14);*/
	
	playerTextures[DK]->frameData[actDUCK][animSTART] = 15;
	playerTextures[DK]->frameData[actDUCK][numFRAMES] = 8;
	//playerTextures[DK]->frameData[actRUN][animSPEED] = 80;
    /*TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck1.tga", 15);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck2.tga", 16);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck3.tga", 17);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck4.tga", 18);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck5.tga", 19);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck6.tga", 20);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck7.tga", 21);
    TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDuck8.tga", 22);*/
	
	playerTextures[DK]->frameData[actATTACK1][animSTART] = 23;
	playerTextures[DK]->frameData[actATTACK1][numFRAMES] = 11;
	playerTextures[DK]->frameData[actATTACK1][minstopFRAME] = 33;
	//playerTextures[DK]->frameData[actRUN][animSPEED] = 80;
    /*TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll1.tga", 23);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll2.tga", 24);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll3.tga", 25);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll4.tga", 26);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll5.tga", 27);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll6.tga", 28);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll7.tga", 29);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll8.tga", 30);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll9.tga", 31);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll10.tga", 32);
    TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll11.tga", 33);*/
	
	playerTextures[DK]->frameData[actJUMP][animSTART] = 34;
	playerTextures[DK]->frameData[actJUMP][numFRAMES] = 18;
	playerTextures[DK]->frameData[actJUMP][repeatFRAME] = 46;
    /*TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump1.tga", 34);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump2.tga", 35);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump3.tga", 36);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump4.tga", 37);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump5.tga", 38);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump6.tga", 39);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump7.tga", 40);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump8.tga", 41);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump9.tga", 42);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump10.tga", 43);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump11.tga", 44);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkJump12.tga", 45);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop1.tga", 46);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop2.tga", 47);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop3.tga", 48);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop4.tga", 49);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop5.tga", 50);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop6.tga", 51);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop7.tga", 52);
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop8.tga", 53);
    TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkDrop9.tga", 54);*/
	
	//NES MARIO
	playerTextures[MARIONES]->person = MARIONES;
	TGA_Texture(playerTextures[MARIONES], "Data/img/characters/mario1/mario.tga", 0);
	
	playerTextures[MARIONES]->frameData[actRUN][animSTART] = 1;
	playerTextures[MARIONES]->frameData[actRUN][numFRAMES] = 2;
	playerTextures[MARIONES]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[MARIONES]->frameData[actRUN][animSPEED] = 20;
	playerTextures[MARIONES]->maxSpeed = 5.3f;
	/*TGA_Texture(playerTextures[MARIONES], "Data/img/characters/mario1/marioRun1.tga", 1);
	TGA_Texture(playerTextures[MARIONES], "Data/img/characters/mario1/marioRun2.tga", 2);
	
	playerTextures[MARIONES]->frameData[actJUMP][animSTART] = 3;
	playerTextures[MARIONES]->frameData[actJUMP][numFRAMES] = 1;
	playerTextures[MARIONES]->frameData[actJUMP][repeatFRAME] = 3;
	TGA_Texture(playerTextures[MARIONES], "Data/img/characters/mario1/marioJump1.tga", 3);
	
	playerTextures[MARIONES]->frameData[actDUCK][animSTART] = 4;
	playerTextures[MARIONES]->frameData[actDUCK][numFRAMES] = 1;
	TGA_Texture(playerTextures[MARIONES], "Data/img/characters/mario1/marioDuck.tga", 4);

	//CAPE MARIO
	playerTextures[CAPEMARIO]->person = CAPEMARIO;
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariow.tga", 0);
	
	playerTextures[CAPEMARIO]->frameData[actRUN][animSTART] = 1;
	playerTextures[CAPEMARIO]->frameData[actRUN][numFRAMES] = 8;
	playerTextures[CAPEMARIO]->frameData[actRUN][repeatFRAME] = 1;
	//playerTextures[CAPEMARIO]->frameData[actRUN][animSPEED] = 20;
	/*TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun1.tga", 1);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun2.tga", 2);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun3.tga", 3);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun4.tga", 4);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun5.tga", 5);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun6.tga", 6);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun7.tga", 7);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowRun8.tga", 8);*/

	playerTextures[CAPEMARIO]->frameData[actJUMP][animSTART] = 9;
	playerTextures[CAPEMARIO]->frameData[actJUMP][numFRAMES] = 7;
	playerTextures[CAPEMARIO]->frameData[actJUMP][repeatFRAME] = 11;
	/*TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump1.tga", 9);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump2.tga", 10);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump3.tga", 11);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump4.tga", 12);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump5.tga", 13);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump6.tga", 14);
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowJump7.tga", 15);*/

	playerTextures[CAPEMARIO]->frameData[actATTACK1][animSTART] = 16;
	playerTextures[CAPEMARIO]->frameData[actATTACK1][numFRAMES] = 4;
	playerTextures[CAPEMARIO]->frameData[actATTACK1][minstopFRAME] = 19;
	/*TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowAtk1.tga", 16);playerTextures[CAPEMARIO]->centers[16] = 0.692307f;
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowAtk2.tga", 17);playerTextures[CAPEMARIO]->centers[17] = 0.25f;
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowAtk3.tga", 18);playerTextures[CAPEMARIO]->centers[18] = 0.269230f;
	TGA_Texture(playerTextures[CAPEMARIO], "Data/img/characters/cmario/mariowAtk4.tga", 19);playerTextures[CAPEMARIO]->centers[19] = 0.708333f;*/

	//VECTORMAN
	playerTextures[VECTORMAN]->person = VECTORMAN;
    /*TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman1.tga", 0);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman2.tga", 1);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman3.tga", 2);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman4.tga", 3);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman5.tga", 4);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman6.tga", 5);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman7.tga", 6);
    TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectorman8.tga", 7);*/
	
	playerTextures[VECTORMAN]->frameData[actRUN][animSTART] = 8;
	playerTextures[VECTORMAN]->frameData[actRUN][numFRAMES] = 14;
	playerTextures[VECTORMAN]->frameData[actRUN][repeatFRAME] = 8;
	playerTextures[VECTORMAN]->frameData[actRUN][animSPEED] = 35;
	/*TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun1.tga", 8);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun2.tga", 9);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun3.tga", 10);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun4.tga", 11);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun5.tga", 12);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun6.tga", 13);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun7.tga", 14);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun8.tga", 15);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun9.tga", 16);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun10.tga", 17);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun11.tga", 18);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun12.tga", 19);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun13.tga", 20);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanRun14.tga", 21);*/

	playerTextures[VECTORMAN]->frameData[actJUMP][animSTART] = 22;
	playerTextures[VECTORMAN]->frameData[actJUMP][numFRAMES] = 9;
	playerTextures[VECTORMAN]->frameData[actJUMP][repeatFRAME] = 28;
	playerTextures[VECTORMAN]->jumpStrength = 1.5f;
    /*TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump1.tga", 22);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump2.tga", 23);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump3.tga", 24);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump4.tga", 25);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump5.tga", 26);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump6.tga", 27);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump7.tga", 28);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump8.tga", 29);
    TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanJump9.tga", 30);*/

	playerTextures[VECTORMAN]->frameData[actSHOOT][animSTART] = 31;
	playerTextures[VECTORMAN]->frameData[actSHOOT][numFRAMES] = 3;
	//playerTextures[VECTORMAN]->frameData[actJUMP][animSPEED] = 35;
	/*TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanShoot1.tga", 31);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanShoot2.tga", 32);
	TGA_Texture(playerTextures[VECTORMAN], "Data/img/characters/vman/vectormanShoot3.tga", 33);*/


	/*playerTextures[VECTORMAN]->frameData[actJUMP][animSTART] = 1;
	playerTextures[VECTORMAN]->frameData[actJUMP][numFRAMES] = 14;
	playerTextures[VECTORMAN]->frameData[actJUMP][repeatFRAME] = 3;
	TGA_Texture(playerTextures[DK], "Data/img/characters/DK/dkRoll1.tga", 23);*/

	//MICHAELANGELO
	playerTextures[MICHAELANGELO]->person = MICHAELANGELO;
    /*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangelo1.tga", 0);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangelo2.tga", 1);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangelo3.tga", 2);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangelo4.tga", 3);
    TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangelo5.tga", 4);*/
	
	playerTextures[MICHAELANGELO]->frameData[actRUN][animSTART] = 5;
	playerTextures[MICHAELANGELO]->frameData[actRUN][numFRAMES] = 5;
	playerTextures[MICHAELANGELO]->frameData[actRUN][repeatFRAME] = 7;
	playerTextures[MICHAELANGELO]->frameData[actRUN][animSPEED] = 18;
	/*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloRun1.tga", 5);playerTextures[MICHAELANGELO]->centers[5] = 0.32352f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloRun2.tga", 6);playerTextures[MICHAELANGELO]->centers[6] = 0.26666f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloRun3.tga", 7);playerTextures[MICHAELANGELO]->centers[7] = 0.32352f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloRun4.tga", 8);playerTextures[MICHAELANGELO]->centers[8] = 0.26666f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloRun5.tga", 9);playerTextures[MICHAELANGELO]->centers[9] = 0.29268f;*/

	playerTextures[MICHAELANGELO]->frameData[actATTACK1][animSTART] = 10;
	playerTextures[MICHAELANGELO]->frameData[actATTACK1][numFRAMES] = 4;
	playerTextures[MICHAELANGELO]->frameData[actATTACK1][minstopFRAME] = 13;
	playerTextures[MICHAELANGELO]->frameData[actATTACK1][animSPEED] = 70;
	/*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloAtk1.tga", 10);playerTextures[MICHAELANGELO]->centers[10] = 0.450980f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloAtk2.tga", 11);playerTextures[MICHAELANGELO]->centers[11] = 0.2417582f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloAtk3.tga", 12);playerTextures[MICHAELANGELO]->centers[12] = 0.253521f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloAtk4.tga", 13);playerTextures[MICHAELANGELO]->centers[13] = 0.4736842f;

	playerTextures[MICHAELANGELO]->frameData[actJUMPATK][animSTART] = 15;
	playerTextures[MICHAELANGELO]->frameData[actJUMPATK][numFRAMES] = 4;
	/*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJumpAtk1.tga", 15);playerTextures[MICHAELANGELO]->centers[15] = 0.305555f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJumpAtk2.tga", 16);playerTextures[MICHAELANGELO]->centers[16] = 0.375f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJumpAtk3.tga", 17);playerTextures[MICHAELANGELO]->centers[17] = 0.20833f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJumpAtk4.tga", 18);playerTextures[MICHAELANGELO]->centers[18] = 0.20833f;*/

	playerTextures[MICHAELANGELO]->frameData[actJUMP][animSTART] = 19;
	playerTextures[MICHAELANGELO]->frameData[actJUMP][numFRAMES] = 6;
	playerTextures[MICHAELANGELO]->frameData[actJUMP][repeatFRAME] = 23;
	playerTextures[MICHAELANGELO]->frameData[actJUMP][animSPEED] = 70;
	/*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump1.tga", 19, 0.32258f);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump2.tga", 20);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump3.tga", 21);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump4.tga", 22);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump5.tga", 23);
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloJump6.tga", 24);playerTextures[MICHAELANGELO]->centers[24] = 0.38709f;*/

	playerTextures[MICHAELANGELO]->frameData[actHURT][animSTART] = 25;
	playerTextures[MICHAELANGELO]->frameData[actHURT][numFRAMES] = 3;
	playerTextures[MICHAELANGELO]->frameData[actHURT][minstopFRAME] = 27;
    /*TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloHurt1.tga", 25);playerTextures[MICHAELANGELO]->centers[25] = 0.58139f;
	TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloHurt2.tga", 26);playerTextures[MICHAELANGELO]->centers[26] = 0.32258f;
    TGA_Texture(playerTextures[MICHAELANGELO], "Data/img/characters/michaelangelo/michaelangeloHurt3.tga", 27);playerTextures[MICHAELANGELO]->centers[27] = 0.44230f;*/

	//LIU KANG
	playerTextures[LIUKANG]->person = LIUKANG;
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lk1.tga", 0);
	
	playerTextures[LIUKANG]->frameData[actRUN][animSTART] = 1;
	playerTextures[LIUKANG]->frameData[actRUN][numFRAMES] = 8;
	playerTextures[LIUKANG]->frameData[actRUN][repeatFRAME] = 1;
	playerTextures[LIUKANG]->maxSpeed = 2.0f;
	/*TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk1.tga", 1);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk2.tga", 2);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk3.tga", 3);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk4.tga", 4);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk5.tga", 5);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk6.tga", 6);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk7.tga", 7);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkWalk8.tga", 8);*/

	playerTextures[LIUKANG]->frameData[actJUMP][animSTART] = 9;
	playerTextures[LIUKANG]->frameData[actJUMP][numFRAMES] = 4;
	playerTextures[LIUKANG]->frameData[actJUMP][repeatFRAME] = 11;
    /*TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkJump1.tga", 9);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkJump2.tga", 10);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkJump3.tga", 11);
    TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkJump4.tga", 12);*/

	playerTextures[LIUKANG]->frameData[actDUCK][animSTART] = 13;
	playerTextures[LIUKANG]->frameData[actDUCK][numFRAMES] = 5;
	/*TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkDuck1.tga", 13);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkDuck2.tga", 14);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkDuck3.tga", 15);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkDuck4.tga", 16);
	TGA_Texture(playerTextures[LIUKANG], "Data/img/characters/liukang/lkDuck5.tga", 17);*/
	
	objectTextures[BLOCK1]->blk = BLOCK1;
	LoadGLTextures(objectTextures[BLOCK1], "Data/Gesture.bmp", 0);
	
	objectTextures[BLOCK2]->blk = BLOCK2;
	LoadGLTextures(objectTextures[BLOCK2], "Data/Crystal.bmp", 0);
	
	objectTextures[PORTLAND]->blk = PORTLAND;
	objectTextures[PORTLAND]->isSolid = false;
	LoadGLTextures(objectTextures[PORTLAND], "Data/port.bmp", 0);
		
	objectTextures[WATER1]->blk = WATER1;
	objectTextures[WATER1]->isSolid = false;
    /*TGA_Texture(objectTextures[WATER1], "Data/img/watera2.tga", 0);
    TGA_Texture(objectTextures[WATER1], "Data/img/waterb2.tga", 1);*/

	setDefaults(playerTextures, NUMCHARACTERS);
	setDefaults(shotTextures, NUMSHOTTYPES);
	
	return;
}

void assignTextures(object_c &obj, animData_s *animData)
{
	for(int i=0; i<NUMACTIONS; i++)
	{
		obj.frameFloat[i]		= animData->frameData[i][animSTART];
	}

	obj.animated = animData->animates;
	obj.texture = animData->textures;
	obj.centers = animData->centers;
	
	obj.scale = animData->scale;
		//obj.wScale = animData->wScale;
		//obj.hScale = animData->hScale;
	//obj.oWidth = (animData->wScale[0]/animData->hScale[0])*obj.oHeight;
	//obj.oWidth = (animData->pixelsW*1.0/animData->pixelsH)*obj.oHeight;
	obj.person			= animData->person;
	obj.canWallClimb	= animData->canWallClimb;
	obj.canShoot		= animData->canShoot;
	obj.isSolid			= animData->isSolid;
	obj.jumpStrength	= animData->jumpStrength;
	obj.xSpeed			= animData->maxSpeed;

	return;
}

bool sendAnimation(object_c &obj, actions act, GLfloat dt)
{
	bool didAnimation;

	switch(obj.person)
	{
		case ZERO:
			break;
		case MMX:
			break;
		case GOKU:
			break;
		case SPIDEY:
			break;
		case TAILS:
			obj.rotate = 0.0f;	
			break;
		case SONIC:		
			break;
		case MARIONES:
			break;
		case CAPEMARIO:	
			break;
		case PETER:
			break;
		case GOOMBA:
			break;	
		case DK:
			break;
		default:
			break;
	}

	didAnimation = animate(obj, act, playerTextures[obj.person], dt);

	return didAnimation;
}
bool animate(object_c &obj, actions act, const animData_s *animData, GLfloat dt)
{
	int frame;
	GLfloat rx, ry;
	int rotateSign;

	bool didAnimation = true;
	
	GLfloat currentTime = GetTickCount();

	switch(act)
	{
		//-1 when frames dont exist
		case actRUN:
			if(animData->frameData[actRUN][animSTART] != -1)
			{
				obj.frameFloat[actRUN] += fabs(obj.vel.x)*animData->frameData[actRUN][animSPEED]/DEFFRAMESPEED*dt;
				
				//if gone passed last frame repeat
				if(obj.frameFloat[actRUN] > (animData->frameData[actRUN][lastFRAME]+1))
					obj.frameFloat[actRUN] = animData->frameData[actRUN][repeatFRAME];
				
				frame = static_cast<int>(floor(obj.frameFloat[actRUN]));
				obj.animFrame = frame;

				if(obj.vel.x == 0)
					obj.animFrame = 0;
			}
			else
				didAnimation = false;
			break;
		case actATTACK1:
		case actWALL:
		case actSHOOT:
		case actDUCK:
		case actJUMPATK:
		case actHURT:
			if((animData->frameData[act][animSTART] != -1))
			{
				obj.frameFloat[act] += animData->frameData[act][animSPEED]/DEFFRAMESPEED*dt;

				frame = static_cast<int>(floor(obj.frameFloat[act]));

				obj.animFrame = frame;
			}
			else
				didAnimation = false;
			break;
		case actPUSH:
			if(animData->frameData[actPUSH][animSTART] != -1)
			{
				if(obj.frameFloat[actPUSH] > (animData->frameData[actPUSH][lastFRAME]+1))
					obj.frameFloat[actPUSH] = animData->frameData[actPUSH][repeatFRAME];
				else
					obj.frameFloat[actPUSH] += animData->frameData[actPUSH][animSPEED]/DEFFRAMESPEED*dt;
				frame = static_cast<int>(floor(obj.frameFloat[actPUSH]));
				obj.animFrame = frame;
			}
			else
				didAnimation = false;
			break;
		default:
			obj.animFrame = 0;
			obj.frameFloat[actRUN] = animData->frameData[actRUN][animSTART];
			obj.frameFloat[actDUCK] = animData->frameData[actDUCK][animSTART];
			obj.frameFloat[actSHOOT] = animData->frameData[actSHOOT][animSTART];
			obj.frameFloat[actHURT] = animData->frameData[actHURT][animSTART];
	}

	if(obj.isTouching[BSIDE])
	{
		obj.frameFloat[actJUMP] = animData->frameData[actJUMP][animSTART];
		obj.frameFloat[actJUMPSHOOT] = animData->frameData[actJUMPSHOOT][animSTART];
	}
	else if((act != actWALL) && (animData->frameData[actJUMP][animSTART] != -1) && (act != actJUMPATK) && (act != actHURT))
	{	
		if((obj.person == TAILS) || (obj.person == SONIC))
			obj.state[actATTACK1] = true;
		if(obj.frameFloat[actJUMP] >= animData->frameData[actJUMP][repeatFRAME] && (obj.vel.y >= 0.0f) && (obj.person != TAILS) && (obj.person != SONIC))
		{
			obj.frameFloat[actJUMP] = animData->frameData[actJUMP][repeatFRAME];
			obj.frameFloat[actJUMPSHOOT] = animData->frameData[actJUMPSHOOT][repeatFRAME];
		}
		else if(obj.frameFloat[actJUMP] > animData->frameData[actJUMP][lastFRAME])
		{
			obj.frameFloat[actJUMP] = animData->frameData[actJUMP][lastFRAME];
			obj.frameFloat[actJUMPSHOOT] = animData->frameData[actJUMPSHOOT][lastFRAME];;
			if((obj.person == TAILS) || (obj.person == SONIC))
			{
				obj.frameFloat[actJUMP] = animData->frameData[actJUMP][repeatFRAME];
				obj.frameFloat[actJUMPSHOOT] = animData->frameData[actJUMPSHOOT][repeatFRAME];
			}
		}
		else
		{
			//need to look at
			obj.frameFloat[actJUMP] += animData->frameData[actJUMP][animSPEED]/DEFFRAMESPEED*dt;
			obj.frameFloat[actJUMPSHOOT] += animData->frameData[actJUMPSHOOT][animSPEED]/DEFFRAMESPEED*dt;
		}

		switch(act)
		{
			case actSHOOT:
				if(animData->frameData[actJUMPSHOOT][animSTART] != -1)
					frame = static_cast<int>(floor(obj.frameFloat[actJUMPSHOOT]));
				break;
			default:
				frame = static_cast<int>(floor(obj.frameFloat[actJUMP]));
				break;
		}

		obj.animFrame = frame;

		if(obj.person == TAILS)
		{
			rx = obj.vel.x;
			ry = obj.vel.y;
			if(fabs(rx) < .1f)
			{
				if(rx > 0)
					rx = .1f;
				else
					rx = .1f;
			}
			if(obj.vel.x >=0)
				rotateSign = 1;
			else
				rotateSign = -1;
			double temprote = ((180/3.1419125)*atan(obj.vel.y/obj.vel.x));
			obj.rotate = ((180/3.1419125)*atan(obj.vel.y/obj.vel.x)) + rotateSign*90;
			temprote = temprote;
		}
	}


	if(act != actATTACK1)
		obj.frameFloat[actATTACK1] = animData->frameData[actATTACK1][animSTART];
	if(act != actJUMPATK)
		obj.frameFloat[actJUMPATK] = animData->frameData[actJUMPATK][animSTART];
	
	if(obj.animFrame < (animData->frameData[act][minstopFRAME]+1))
		obj.animationDone[act] = false;
	else
		obj.animationDone[act] = true;

	if(animData->frameData[act][animSTART] != -1)
	{
		if(obj.animFrame > animData->frameData[act][lastFRAME])
			if(animData->frameData[act][canHOLD])
				obj.animFrame = animData->frameData[act][lastFRAME];
			else
				didAnimation = false;
	}

	return didAnimation;
}

void setDefaults(animData_s **animData, int numobjs)
{
	for(int i=0; i<numobjs; i++)
	{
		for(int j=0; j<NUMACTIONS; j++)
		{
			animData[i]->frameData[j][lastFRAME] = animData[i]->frameData[j][animSTART] + animData[i]->frameData[j][numFRAMES] - 1;
			if(animData[i]->frameData[j][minstopFRAME] == -1)
				animData[i]->frameData[j][minstopFRAME] = animData[i]->frameData[j][animSTART];
		}
		if(animData[i]->frameData[actSHOOT][animSTART] != -1)
			animData[i]->canShoot = true;
		//if(animData[actWALL] != -1)
			//animData[i]->canShoot = true;
	}

	return;
}


void fixSize(object_c &animObj)
{
	Vector2D minOld = Vector2D(animObj.posMin.x, animObj.posMin.y);
	Vector2D maxOld = Vector2D(animObj.posMax.x, animObj.posMax.y);

	animObj.dimension = animObj.scale[animObj.animFrame].mult(animObj.oDimension);
	animObj.center = animObj.centers[animObj.animFrame];
	
	if(animObj.isTouching[LSIDE])
	{
		
		animObj.pos.x = minOld.x + .5f*animObj.dimension.x;
	}
	if(animObj.isTouching[RSIDE])
	{
		animObj.pos.x = maxOld.x - ((animObj.dirSign+1)/2-animObj.dirSign*animObj.center)*animObj.dimension.x;

	}

	animObj.calcBoundaries();

	return;
}
