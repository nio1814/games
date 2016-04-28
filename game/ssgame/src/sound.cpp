//#include <windows.h>
#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>    /* optional */

#include "sound.h"
#include "animation.h"

FSOUND_SAMPLE *currentSong;
FSOUND_SAMPLE *revcrash;
FSOUND_SAMPLE *sngGameOver;
FSOUND_SAMPLE *sngEncore;
FSOUND_SAMPLE *sngN;

soundData_s mmxSounds;
soundData_s zeroSounds;
soundData_s sonicSounds;
soundData_s tailsSounds;

bool musicPlaying = false;

void doSounds()
{
	/*FSOUND_Update();
	revcrash = FSOUND_Sample_Load(FSOUND_FREE , "Data/revcrash.wav", FSOUND_2D, 0, 0);
	
	sngGameOver = FSOUND_Sample_Load(FSOUND_FREE , "Data/music/gameover.ogg", FSOUND_2D, 0, 0);
	FSOUND_Sample_SetMode(sngGameOver, FSOUND_LOOP_NORMAL);
	
	sngEncore = FSOUND_Sample_Load(FSOUND_FREE , "Data/music/encore.ogg", 0x00002000, 0, 0);
	FSOUND_Sample_SetMode(sngEncore, FSOUND_LOOP_NORMAL);
	
	sngN = FSOUND_Sample_Load(FSOUND_FREE , "Data/music/n2.ogg", 0x00002000, 0, 0);
	FSOUND_Sample_SetMode(sngN, FSOUND_LOOP_NORMAL);
	
	mmxSounds.sounds[actJUMP] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxJump.ogg", FSOUND_2D, 0, 0);
	//mmxSounds.sounds[actLAND] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxLand.ogg", FSOUND_2D, 0, 0);
	mmxSounds.sounds[actSHOOT] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxShot.ogg", FSOUND_2D, 0, 0);
	mmxSounds.sounds[actHURT] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxHurt.ogg", FSOUND_2D, 0, 0);
	//mmxSounds.sounds[actJUMP] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxHealth.ogg", FSOUND_2D, 0, 0);

	zeroSounds.sounds[actJUMP] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxJump.ogg", FSOUND_2D, 0, 0);
	zeroSounds.sounds[actATTACK1] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/zero/zeroSaber.ogg", FSOUND_2D, 0, 0);
	zeroSounds.sounds[actHURT] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/mmx/mmxHurt.ogg", FSOUND_2D, 0, 0);
	zeroSounds.sounds[actJUMPATK] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/zero/zeroSaber.ogg", FSOUND_2D, 0, 0);
	
	sonicSounds.sounds[actJUMP] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/sonic/sonicJump.ogg", FSOUND_2D, 0, 0);
	sonicSounds.sounds[actHURT] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/sonic/sonicHurt.ogg", FSOUND_2D, 0, 0);
	
	tailsSounds.sounds[actJUMP] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/sonic/sonicJump.ogg", FSOUND_2D, 0, 0);
	tailsSounds.sounds[actHURT] = FSOUND_Sample_Load(FSOUND_FREE , "Data/sfx/sonic/sonicHurt.ogg", FSOUND_2D, 0, 0);
	*/
	return;
}


void playActionSound(const Object &obj, Action act)
{
	soundData_s soundData;
	
	if((obj.objType == tpPLAYER) || (obj.objType == tpENEMY))
	{
		switch(obj.person)
		{
			case ZERO:
				soundData = zeroSounds;
				break;
			case MMX:
				soundData = mmxSounds;
				break;
			case SONIC:
				soundData = sonicSounds;
				break;
			case TAILS:
				soundData = tailsSounds;
				break;
			default:
				break;
		}
		
//		if(soundData.sounds[act] != NULL && (act != actNONE))
//			FSOUND_PlaySound(FSOUND_FREE, soundData.sounds[act]);
	}
	else if(obj.objType == tpSHOT)
	{
		switch(obj.shotType)
		{
		case MMXSHOT:
		case GOKUSHOT:
		default:
				break;
		}
	}
	
	return;
}


void setMusic(FSOUND_SAMPLE *song)
{
	currentSong = song;
	FSOUND_StopSound(0);
	musicPlaying = false;
	toggleMusic();
	return;
}


bool toggleMusic()
{
	if(musicPlaying)
	{
		FSOUND_StopSound(0);
		musicPlaying = false;
	}
	else
	{
		FSOUND_PlaySound(0, currentSong);
		musicPlaying = true;
	}
	
	return musicPlaying;
}
