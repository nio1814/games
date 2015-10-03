//#include <windows.h>								// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <math.h>								// Header File For Windows Math Library
//#include <gl\gl.h>								// Header File For The OpenGL32 Library
//#include <gl\glu.h>
//#include <gl\glaux.h>
//#include <GL/glu.h>
//#include <fmod\fmod.h>
#include <string.h>

//#include <joystick\joystick.h>

#include "objects.h"
#include "world.h"
#include "masking.h"
#include "screen.h"
#include "tga.h"
#include "playerkeys.h"
//#include "sound.h"
#include "movement.h"
//#include "text.h"
#include "globalvar.h"
#include "datastructs.h"
#include "animation.h"
#include "functions.h"
//#include "Texture Code.h"

#include <QTime>

GLfloat fps;
GLfloat MAXDELTA = .003f;
GLfloat THROTTLE = 1;

game_c game;

extern objectHolder_c movingObjects2;
objectHolder_c movingObjects2;

object_c* player = new object_c(1.5f, 2.25f,0.0f, 4.0f, tpPLAYER, ZERO);
object_c* player2 = new object_c(1.5f, 2.25f,3.0f, 4.0f, tpPLAYER, ZERO);
//object_c* gokuShot = new object_c (1.0f, 1.0f, tpSHOT, GOKUSHOT, player);
//object_c shot = object_c (1.0f, 1.0f, "Data/img/star2.tga", tpSHOT, player);							// Player Information
object_c* ball = new object_c(1.0f, 1.0f, 2.0f, 5.0f, tpOBJ, ZERO);
object_c* enemy = new object_c(1.5f, 2.25f,13.0f, 8.0f, tpENEMY, MMX);
//object_c* mShot = new object_c (1.0f, 1.0f, tpSHOT, MMXSHOT, enemy);
object_c* enemy2 = new object_c(1.75f, 2.75f,4.0f, -4.0f, tpENEMY, GOKU);
object_c* spid = new object_c(3.00f, 1.97f, 23.0f, 24.0f, tpENEMY, SPIDEY);
object_c* tails = new object_c(1.00f, 1.5f, 23.0f, 24.0f, tpENEMY, TAILS);
object_c* goomba1 = new object_c(.70f, .70f, 12.0f, -24.0f, tpENEMY, GOOMBA);
object_c* goomba2 = new object_c(.70f, .70f, 23.0f, -24.0f, tpENEMY, GOOMBA);
object_c* goomba3 = new object_c(.70f, .70f, 34.0f, -24.0f, tpENEMY, GOOMBA);

level_s level1s;
level_s level2s;
level_s level3s;
level_s *currentLevel;
level_c *nowLevel;
level_c level1c(1);
level_c level0c(0);
int curLevelNum;

//joystick_s *joystick;
pointerTree debug;

/*struct			 							// Create A Structure For The Timer Information
{
  __int64       frequency;							// Timer Frequency
  float         resolution;							// Timer Resolution
  unsigned long mm_timer_start;							// Multimedia Timer Start Value
  unsigned long mm_timer_elapsed;						// Multimedia Timer Elapsed Time
  bool		performance_timer;						// Using The Performance Timer?
  __int64       performance_timer_start;					// Performance Timer Start Value
  __int64       performance_timer_elapsed;					// Performance Timer Elapsed Time
} timer;									// Structure Is Named timer
*/
int		steps[6]={ 1, 2, 4, 5, 10, 20 };				// Stepping Values For Slow Video Adjustment


float CalculateFrameRate();
void doLevel();
void setupObjects();
void updateObjects();
void gamepadlogic();

void doLevel()
{
	curLevelNum = 0;
	
	level1s.levelNum = 1;
	level2s.levelNum = 2;
	level3s.levelNum = 3;

	makeLevel(level2s);
	//makeLevel(level2s);
	//makeLevel(level3s);
	currentLevel = &level1s;
	
	//makeLevel(level1c);
	//makeLevel(level0c);
	
	//nowLevel = &level1c;
	nowLevel = &game.levels[0];
	nowLevel->levelNum = 2;
	makeLevel(*nowLevel);
	nowLevel->cameras->cpoints[0].followDist = 15.0f;
	
//	joystick = new joystick_s;

	//set debug parameters
	debug.addLeaf(NULL, tpBOOL, "Movement");
	debug.ptr[0].addLeaf(&THROTTLE, tpFLOAT, "throttle");
	debug.ptr[0].addLeaf(&XSCALE, tpFLOAT, "X Scale");
	debug.ptr[0].addLeaf(&GROUNDFRIC, tpFLOAT, "Ground Friction");
	debug.ptr[0].addLeaf(&RUNFRICFACTOR, tpFLOAT, "Run Friction");
	debug.ptr[0].addLeaf(&DEFRUNFRAMESPD, tpINT, "Run Frame Speed");
	debug.ptr[0].addLeaf(&CAMLOOKSPEED, tpFLOAT, "Camera Look Speed");
	debug.ptr[0].addLeaf(&CAMMOVESPEED, tpFLOAT, "Camera Move Speed");
	debug.ptr[0].addLeaf(&WALLFRIC, tpFLOAT, "Wall Friction");
	
	return;
}


void setupObjects()
{
	nowLevel->addPlayer(1.5f, 2.25f,0.0f, 14.0f, MMX);
	//nowLevel->addPlayer(1.5f, 2.25f,3.0f, 4.0f, ZERO);
	//object_c* gokuShot = new object_c(1.0f, 1.0f, tpSHOT, GOKUSHOT, 's', *player);
	//object_c shot = object_c (1.0f, 1.0f, "Data/img/star2.tga", tpSHOT, player);							// Player Information
	//object_c* ball = new object_c(1.0f, 1.0f, 2.0f, 5.0f, tpOBJ, ZERO, 'b');
	nowLevel->addEnemy(1.5f, 2.25f,13.0f, 8.0f, MMX);
	//object_c* mShot = new object_c (1.0f, 1.0f, tpSHOT, MMXSHOT, 's', *enemy);
	nowLevel->addEnemy(1.75f, 2.75f,4.0f, -4.0f, GOKU);
	nowLevel->addEnemy(3.00f, 1.97f, 23.0f, 24.0f, SPIDEY);
	nowLevel->addEnemy(1.00f, 1.5f, 23.0f, 24.0f, TAILS);
	nowLevel->addEnemy(.70f, .70f, 12.0f, -24.0f, GOOMBA);
	nowLevel->addEnemy(.70f, .70f, 23.0f, -24.0f, GOOMBA);
	nowLevel->addEnemy(.70f, .70f, 34.0f, -24.0f, GOOMBA);
	
	doTextures();
	nowLevel->initTextures();

	nowLevel->players[0].addShots(3, 1, 1, MMXSHOT);
	//nowLevel->enemies[0].addShots(1, 1, 1, MMXSHOT);
	
	debug.ptr[0].addLeaf(&nowLevel->players[0].vel.x, tpFLOAT, "Player Speed");
	
	/*strcpy(player->ID, "player");
	strcpy(player2->ID, "player2");
	strcpy(ball->ID, "ball");
	strcpy(enemy->ID, "enemy");
	strcpy(enemy2->ID, "goku");
	strcpy(spid->ID, "spidey");

	movingObjects[0] = player->index;
	player->numPlayer = PLAYER1;
	movingObjects[1] = player2->index;
	player2->numPlayer = PLAYER2;
	movingObjects[2] = ball->index;
	movingObjects[3] = enemy->index;
	movingObjects[4] = mShot->index;
	movingObjects[5] = enemy2->index;
	movingObjects[6] = spid->index;
	movingObjects[7] = gokuShot->index;
	movingObjects[8] = goomba1->index;
	movingObjects[9] = goomba2->index;
	movingObjects[10] = goomba3->index;
	numMovingObjects = 2;
	
	movingObjects2.setObject(player);
	movingObjects2.setObject(gokuShot);
	movingObjects2.setObject(player2);
	movingObjects2.setObject(ball);
	movingObjects2.setObject(enemy);
	movingObjects2.setObject(mShot);
	movingObjects2.setObject(enemy2);
	movingObjects2.setObject(spid);
	movingObjects2.setObject(goomba1);
	movingObjects2.setObject(goomba2);
	movingObjects2.setObject(goomba3);
	//movingObjects2.numObjects = 3;
	//player2.active = false;*/
	
	//mShot->vel.x = 9.0f;
	//mShot->mass = .0250f;
	
	ball->canRoll = true;

	enemy2->xSpeed = 2.0f;
	player->xSpeed = .5f;
	
	//"Data/img/nonAnimated/ball.tga"
	//LoadGLTextures(ball.texture, ball.picFile);
//	TGA_Texture(ball->texture, "Data/img/objects/ball.tga" , 0);
	//TGA_Texture(shot.texture, shot.picFile , 0);
	//TGA_Texture(mShot->texture, mShot->picFile , 0);
	//TGA_Texture(mShot->texture, "Data/img/characters/mmx/mmxShot1.tga" , 0);

	return;
}





void drawObjects(int mobjects[], int numObjects)
{
	for(int i=0; i<numObjects; i++)
	{
		if(getObject(mobjects[i])->active)
			getObject(mobjects[i])->drawRec();
	}

	return;
}


void drawObjects(objectHolder_c mobjects)
{
	for(int i=0; i<mobjects.numObjects; i++)
	{
		if(mobjects.getObject(i)->active)
			mobjects.getObject(i)->drawRec();
	}

	return;
}

void runObjects()
{	
	/*//updateMoves(movingObjects, numMovingObjects);
	//checkTouch(movingObjects, numMovingObjects, level);
	updateMoves(movingObjects2);
	checkTouch(movingObjects2, level);
	drawLevel(level);
					//if(level.is3D)
		drawLevel3d(level);
						//drawObjects(movingObjects);
	drawObjects(movingObjects2);
					//if(level.is3D)
		drawLevel(level);*/
	
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-2.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();*/											// Done Drawing The Quad
	
	GLfloat delta;
	static GLfloat lastNonZeroDelta = MAXDELTA;		//used in case delta = 0
	int numOfIterations = 1;
    QTime time;
    GLfloat cTime = time.elapsed();
    GLfloat lTime = cTime;


	delta = CalculateFrameRate();

	//find time inbetween runs
	if(nowLevel->levelStarted)
	{
//		cTime = GetTickCount();
        cTime = time.elapsed();
		delta = (cTime - lTime) / 1000.0f;
		
		if(delta == 0.0f)
			delta = lastNonZeroDelta;
		else
			lastNonZeroDelta = delta;
		
		numOfIterations = (int)(delta / MAXDELTA) + 1;					// Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
		if (numOfIterations != 0)												// Avoid Division By Zero
		delta = delta / numOfIterations;											// dt Should Be Updated According To numOfIterations

		lTime = cTime;
	}
	else
	{
		delta = 0;
//		cTime = lTime = GetTickCount();
        cTime = lTime = time.msec();
	}

	nowLevel->run(delta*THROTTLE, numOfIterations);
	//nowLevel->run(.002);
//	runKeys(nowLevel, joysOpetick, &debug);
	
	return;
}

	
void initSound()
{
	int musicChannel = 0;
	
    /*FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
	FSOUND_Init(44100, 16, FSOUND_INIT_GLOBALFOCUS);

	doSounds();
	setMusic(sngEncore);
	FSOUND_SetVolume(FSOUND_ALL, 100);
	//musicChannel = FSOUND_PlaySound(FSOUND_FREE, bkgSong);
	FSOUND_SetVolume(musicChannel, 90);
	
	//revcrash = FSOUND_Sample_Load(FSOUND_FREE , "Data/revcrash.wav", 0x00002000, 0, 0);
	//FSOUND_Sample_SetMode(revcrash, FSOUND_2D);
    */
	return;
}

int DrawGLScene()								// Here's Where We Do All The Drawing
{
    QTime clock;
	static GLfloat lastTime = 0.0f;
//	GLfloat thisTime = GetTickCount();
    GLfloat thisTime = clock.elapsed();
	bool longEnough = (thisTime - lastTime) > 100.0f;
	static bool hasDied = false;
		
	//if(longEnough)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
		glLoadIdentity();							// Reset The Current Modelview Matrix

			//if(!currentLevel->cameraLock)
				//moveScreen(*player);
			//gluLookAt(-x, -y, -z, -x, -y, 0.0, 0.0, 1.0, 0.0);
		//gluLookAt(goomba1->x, goomba1->y, -z, goomba1->x, goomba1->y, 0.0, 0.0, 1.0, 0.0);
		//glTranslatef(x,y,z);						// Translate Into/Out Of The Screen By z

		glRotatef(xrot,1.0f,0.0f,0.0f);						// Rotate On The X Axis By xrot
		glRotatef(yrot,0.0f,1.0f,0.0f);						// Rotate On The Y Axis By yrot
		
		runObjects();
		
//		lastTime = GetTickCount();
        lastTime = clock.elapsed();
	}
	
	if(player->health == 0.0f)
	{
		player->active = false;
		if(!hasDied)
		{
//			setMusic(sngGameOver);
//			FSOUND_PlaySound(FSOUND_FREE, revcrash);
			//FSOUND_SetVolume(FSOUND_ALL, 200);
		}
			
		hasDied = true;
//		glPrint(200,240,"Game Over. Press Esc to end.",1);
//		glPrint(200,210,"Press 'R' to restart.",1);
		if(isKeys('R') && hasDied)
		{
				/*xMov[PLAYER1] = player->pos.x = player->posOld.x = currentLevel->playerStartX;
				yMov[PLAYER1] = player->pos.y = player->posOld.y = currentLevel->playerStartY;*/
			player->active = true;
			player->health = 1.0f;
//			setMusic(sngN);
			hasDied = false;
		}
	}
	
	//updateObjectMove(shot);//
	
	//updateMoves(movingObjects, numMovingObjects);//

	/*updateObjectMove(ball);
	updatePlayerMove(player);
	updateEnemyMove(enemy, player);
	updateEnemyMove(enemy2, player);
	updateObjectMove(mShot);
	updateEnemyMove(spid, player);

	fixSize(player);
	fixSize(enemy2);
	fixSize(enemy);
	fixSize(spid);*/

	//checkTouch(movingObjects, numMovingObjects, *currentLevel);//

	/*clearTouches(player);
	clearTouches(ball);
	clearTouches(enemy);
	clearTouches(enemy2);

	checkTouch(player, *currentLevel);
	checkTouch(ball, *currentLevel);
	checkTouch(enemy, *currentLevel);
	checkTouch(enemy2, *currentLevel);

	checkTouch(player, ball);
	checkTouch(ball, player);
	checkTouch(ball, enemy);
	checkTouch(player, enemy);
	checkTouch(enemy, player);
	checkTouch(ball, enemy2);
	checkTouch(player, enemy2);
	checkTouch(enemy2, player);
	checkTouch(enemy, enemy2);
	checkTouch(player, mShot);*/

	//checkTouch(player, ground);
	//checkTouch(ball, ground);
	//checkTouch(player, block);
	//checkTouch(ball, block);


	//glTranslatef(0.0f,0.0f,-10.0f);					// Move Left 1.5 Units And Into The Screen 6.0
	

	/*glBindTexture(GL_TEXTURE_2D, texture[0]);				// Select A Texture Based On filter
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);						// Draw A Quad
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f, 1.0f, 0.0f);				// Top Left
		glTexCoord2f(1.0f,1.0f);glVertex3f( 1.0f, 1.0f, 0.0f);				// Top Right
		glTexCoord2f(1.0f,0.0f);glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
	glEnd();
	glDisable(GL_TEXTURE_2D);*/

	/*shot.yVel = 0.0f;
	shot.yVelOld = 0.0f;
	if(isKeys('F'))
	{
		shot.xVel = .5f;
		shot.rotate += 1.10f;
		shot.drawRec();
	}
	else
	{
		shot.x = player->x;
		shot.y = player->y;
		shot.xVel = 0.0f;
	}*/
	
	/*drawLevel(*currentLevel);
	drawLevel3d(*currentLevel);
	drawObjects(movingObjects, numMovingObjects);

	drawLevel(*currentLevel);*/
	
	/*player->drawRec();
	ball.drawRec();
	enemy.drawRec();
	mShot.drawRec();
	enemy2.drawRec();
	spid.drawRec();*/

	/*glBegin(GL_LINES);						// Draw A Quad
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glVertex3f(-10.0f - x, 3.0f - y, 0.0f);				// Top Left
		glVertex3f(-10.0f - x, -3.0f - y, 0.0f);				// Top Right
	glEnd();
	
	glBegin(GL_LINES);						// Draw A Quad
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glVertex3f( 10.0f - x, 3.0f - y, 0.0f);				// Top Left
		glVertex3f( 10.0f - x, -3.0f - y, 0.0f);				// Top Right
	glEnd();

	glBegin(GL_LINES);						// Draw A Quad
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glVertex3f(-3.0f - x,  7.5f - y, 0.0f);				// Top Left
		glVertex3f( 3.0f - x,  7.5f - y, 0.0f);				// Top Right
	glEnd();
	
	glBegin(GL_LINES);						// Draw A Quad
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glVertex3f(-3.0f - x, -7.5f - y, 0.0f);				// Top Left
		glVertex3f( 3.0f - x, -7.5f - y, 0.0f);				// Top Right
	glEnd();*/

	// tried replacing in world.cpp
/*	if(cameraMode)
		glPrint(3,4,"Camera Mode",1);
	else if(debugMode)
	{
		glPrint(3,20,"Debug Mode",1);
    }*/
		
	printScreen(player->health);

	xrot+=xspeed;								// Add xspeed To xrot
	yrot+=yspeed;								// Add yspeed To yrot

	if(!currentLevel->cameraLock)
	{
		xrot += (player->pos.x -player->posOld.x)/2.4;
		yrot += (player->pos.y-player->posOld.y)/2.4;
		if(yrot < -35.0f)
			yrot += .1f;
		else if(yrot > 35.0f)
			yrot -= .1f;

		if(xrot < -15.0f)
			xrot += .1f;
		else if(xrot > 15.0f)
			xrot -= .1f;
	}

    return true;								// Everything Went OK
}

/*GLvoid KillGLWindow()							// Properly Kill The Window
{
	if (fullscreen)								// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);						// Show Mouse Pointer
	}

	if (hRC)								// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))					// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;							// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;							// Set DC To NULL
	}
	
	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;							// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))				// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;							// Set hInstance To NULL
	}

	KillFont();						// Destroy The Font
}


BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;						// Holds The Results After Searching For A Match
	WNDCLASS	wc;							// Windows Class Structure
	DWORD		dwExStyle;						// Window Extended Style
	DWORD		dwStyle;						// Window Style

	RECT WindowRect;							// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;						// Set Left Value To 0
	WindowRect.right=(long)width;						// Set Right Value To Requested Width
	WindowRect.top=(long)0;							// Set Top Value To 0
	WindowRect.bottom=(long)height;						// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;						// Set The Global Fullscreen Flag

	hInstance		= GetModuleHandle(NULL);			// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc Handles Messages
	wc.cbClsExtra		= 0;						// No Extra Window Data
	wc.cbWndExtra		= 0;						// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;						// No Background Required For GL
	wc.lpszMenuName		= NULL;						// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";					// Set The Class Name

	if (!RegisterClass(&wc))						// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Exit And Return FALSE
	}

	if (fullscreen)								// Attempt Fullscreen Mode?
	{

		DEVMODE dmScreenSettings;					// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;			// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;				// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		
		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;				// Select Windowed Mode (Fullscreen=FALSE)
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;					// Exit And Return FALSE
			}
		}
	}
	
	if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
					"OpenGL",				// Class Name
					title,					// Window Title
					WS_CLIPSIBLINGS |			// Required Window Style
					WS_CLIPCHILDREN |			// Required Window Style
					dwStyle,				// Selected Window Style
					0, 0,					// Window Position
					WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
					WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
					NULL,					// No Parent Window
					NULL,					// No Menu
					hInstance,				// Instance
					NULL)))					// Don't Pass Anything To WM_CREATE
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,						// Must Support Double Buffering
		PFD_TYPE_RGBA,							// Request An RGBA Format
		bits,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,						// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		16,								// 16Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,							// Main Drawing Layer
		0,								// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);								// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);						// Set Up Our Perspective GL Screen

	if (!InitGL())								// Initialize Our Newly Created GL Window
	{
		KillGLWindow();							// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	initSound();

	//Initialize DirectInput
	if( FAILED( InitDirectInput( hWnd ) ) )
	{
		MessageBox( NULL, TEXT("Error Initializing DirectInput"), 
			TEXT("DirectInput Sample"), MB_ICONERROR | MB_OK );
	}
	SetTimer( hWnd, 0, 1000 / 30, NULL );

	return TRUE;								// Success
}


LRESULT CALLBACK WndProc(	HWND	hWnd,					// Handle For This Window
				UINT	uMsg,					// Message For This Window
				WPARAM	wParam,					// Additional Message Information
				LPARAM	lParam)					// Additional Message Information
{

	switch (uMsg)								// Check For Windows Messages
	{
	case WM_INITDIALOG:
        if( FAILED( InitDirectInput( hWnd ) ) )
        {
            MessageBox( NULL, TEXT("Error Initializing DirectInput"), 
                        TEXT("DirectInput Sample"), MB_ICONERROR | MB_OK );
            EndDialog( hWnd, 0 );
        }

        // Set a timer to go off 30 times a second. At every timer message
        // the input device will be read
        SetTimer( hWnd, 0, 1000 / 30, NULL );
		return 0;	
	case WM_TIMER:
        // Update the input device every timer message
        if( FAILED( UpdateInputState( hWnd , joystick) ) )
        {
            KillTimer( hWnd, 0 );    
            MessageBox( NULL, TEXT("Error Reading Input State. ") \
                        TEXT("The sample will now exit."), TEXT("DirectInput Sample"), 
                        MB_ICONERROR | MB_OK );
            EndDialog( hWnd, TRUE ); 
        }
        return 0;
	case WM_ACTIVATE:						// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;					// Program Is Active
			}
			else
			{
				active=FALSE;					// Program Is No Longer Active
			}
			if( WA_INACTIVE != wParam && g_pJoystick )
			{
            // Make sure the device is acquired, if we are gaining focus.
            g_pJoystick->Acquire();
			}

			return 0;						// Return To The Message Loop
		}
		case WM_SYSCOMMAND:						// Intercept System Commands
		{
			switch (wParam)						// Check System Calls
			{
				case SC_SCREENSAVE:				// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;					// Prevent From Happening
			}
			break;							// Exit
		}

		case WM_CLOSE:							// Did We Receive A Close Message?
		{
			PostQuitMessage(0);					// Send A Quit Message
			return 0;						// Jump Back
		}

		case WM_KEYDOWN:						// Is A Key Being Held Down?
		{
			keyDown(wParam);					// If So, Mark It As TRUE
			return 0;						// Jump Back
		}

		case WM_KEYUP:							// Has A Key Been Released?
		{
			keyUp(wParam);					// If So, Mark It As FALSE
			return 0;						// Jump Back
		}
		
		case WM_LBUTTONDOWN:
		{
			keyDown(MK_LBUTTON+255);
			return 0;
		}
		
		case WM_LBUTTONUP:
		{
			keyUp(MK_LBUTTON+255);
			return 0;
		}
		
		case WM_MBUTTONDOWN:
		{
			keyDown(MK_MBUTTON+255);
			return 0;
		}
		
		case WM_MBUTTONUP:
		{
			keyUp(MK_MBUTTON+255);
			return 0;
		}
		
		case WM_RBUTTONDOWN:
		{
			keyDown(MK_RBUTTON+255);
			return 0;
		}
		
		case WM_RBUTTONUP:
		{
			keyUp(MK_RBUTTON+255);
			return 0;
		}
		
		case WM_SIZE:							// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));		// LoWord=Width, HiWord=Height
			return 0;						// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


int WINAPI WinMain(	HINSTANCE	hInstance,				// Instance
			HINSTANCE	hPrevInstance,				// Previous Instance
			LPSTR		lpCmdLine,				// Command Line Parameters
			int		nCmdShow)				// Window Show State
{

	MSG	msg;								// Windows Message Structure
	BOOL	done=FALSE;							// Bool Variable To Exit Loop

    // Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;						// Windowed Mode
    }

	fullscreen = false;

	// Create Our OpenGL Window
	if (!CreateGLWindow("Okai OpenGL Framework",WindowSizeX, WindowSizeY,16,fullscreen))
	{
		return 0;							// Quit If Window Was Not Created
	}
	
	assignControls();

	while(!done)								// Loop That Runs Until done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;					// If So done=TRUE
			}
			else							// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else								// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || isKeys(VK_ESCAPE))	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
				//runKeys(nowLevel, joystick, &debug);
			}

			if (isKeys(VK_F1))						// Is F1 Being Pressed?
			{
				keyUp(VK_F1);					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's First Polygon Tutorial",WindowSizeX,WindowSizeY,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}


	// Shutdown
	KillGLWindow();								    // Kill The Window
	return (msg.wParam);							// Exit The Program
}*/


float CalculateFrameRate()
{
	// Below we create a bunch of static variables because we want to keep the information
	// in these variables after the function quits.  We could make these global but that would
	// be somewhat messy and superfluous.  Note, that normally you don't want to display this to
	// the window title bar.  This is because it's slow and doesn't work in full screen.
	// Try using the 3D/2D font's.  You can check out the tutorials at www.gametutorials.com.

	static int framesPerSecond    = 0;							// This will store our fps
    static float currentTime		= 0.0f;
    static float lastTime			= 0.0f;							// This will hold the time from the last frame						
	static char strFrameRate[50] = {0};								// We will store the string here for the window title
    QTime clock;

	// Here we get the current tick count and multiply it by 0.001 to convert it from milliseconds to seconds.
	// GetTickCount() returns milliseconds (1000 ms = 1 second) so we want something more intuitive to work with.
//    currentTime = GetTickCount() * 0.001f;
    currentTime = clock.msecsSinceStartOfDay() * 0.001f;

	// Increase the frame counter
    ++framesPerSecond;

	// Now we want to subtract the current time by the last time that was stored.  If it is greater than 1
	// that means a second has passed and we need to display the new frame rate.  Of course, the first time
	// will always be greater than 1 because lastTime = 0.  The first second will NOT be true, but the remaining
	// ones will.  The 1.0 represents 1 second.  Let's say we got 12031 (12.031) from GetTickCount for the currentTime,
	// and the lastTime had 11230 (11.230).  Well, 12.031 - 11.230 = 0.801, which is NOT a full second.  So we try again
	// the next frame.  Once the currentTime - lastTime comes out to be greater than a second (> 1), we calculate the
	// frames for this last second.
    if( currentTime - lastTime > 1.0f )
    {		
		// Copy the frames per second into a string to display in the window title bar
		sprintf(strFrameRate, "Current Frames Per Second: %d", int(framesPerSecond));

		// Set the window title bar to our string
//		SetWindowText(hWnd, strFrameRate);

		// Reset the frames per second
        framesPerSecond = 0;

		// Here we set the lastTime to the currentTime.  This will be used as the starting point for the next second.
		// This is because GetTickCount() counts up, so we need to create a delta that subtract the current time from.
        lastTime = clock.msecsSinceStartOfDay() * 0.001f;;
    }
    
    fps = framesPerSecond;
    
    return currentTime - lastTime;
}




/*
//MASKING
AUX_RGBImageRec *LoadBMP(char *Filename)					// Loads A Bitmap Image
{
	FILE *File=NULL;							// File Handle

	if (!Filename)								// Make Sure A Filename Was Given
	{
		return NULL;							// If Not Return NULL
	}

	File=fopen(Filename,"r");						// Check To See If The File Exists

	if (File)								// Does The File Exist?
	{
		fclose(File);							// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;								// If Load Failed Return NULL
}
*/


