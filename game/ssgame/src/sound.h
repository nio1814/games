/*===============================================================================================
 SIMPLE.EXE
 Copyright (c), Firelight Technologies Pty, Ltd 1999-2004.

 This example demonstrates some fundamental FMOD usage, including device enumeration, output
 mode selection, user file I/O callbacks, loading and playing samples and a music file, and
 calling some runtime manipulation and information functions.
===============================================================================================*/

#ifndef SOUND
#define SOUND

//#include <windows.h>
//#include <fmod\fmod.h>
//#include <fmod\fmod_errors.h>    /* optional */

#include "animation.h"

struct soundData_s
{
	FSOUND_SAMPLE *sounds[50];
	
	character person;
	
	soundData_s()
	{
		for(int i=0; i<50; i++)
			sounds[i] = NULL;
	}
	
};

extern FSOUND_SAMPLE *revcrash;
extern FSOUND_SAMPLE *sngGameOver;
extern FSOUND_SAMPLE *sngEncore;
extern FSOUND_SAMPLE *sngN;

extern soundData_s mmxSounds;
extern soundData_s zeroSounds;
extern soundData_s sonicSounds;
extern soundData_s tailsSounds;

void doSounds();
void playActionSound(const object_c &obj, actions act);
void setMusic(FSOUND_SAMPLE *song);
bool toggleMusic();

#endif



