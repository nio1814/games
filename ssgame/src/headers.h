#ifndef L7
#define L7

#include	<windows.h>							// Header File For Windows
#include	<gl\gl.h>							// Header File For The OpenGL32 Library
#include	<gl\glu.h>							// Header File For The GLu32 Library
#include    <gl\glaux.h>

//MASKING
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 				// Ambient Light Values ( NEW )
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				 // Diffuse Light Values ( NEW )
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };				 // Light Position ( NEW )

BOOL	light;									// Lighting ON / OFF

GLuint	texture[5];								// Storage for 3 textures
GLuint	filter;									// Which Filter To Use
GLuint	loop;									// Generic Loop Variable

GLfloat	roll;									// Rolling Texture

bool	masking=TRUE;								// Masking On/Off

bool	scene;	


//AUX_RGBImageRec *LoadBMP(char *Filename);					// Loads A Bitmap Image
int LoadGLTextures();								// Load Bitmaps And Convert To Textures


//MOVEMENT
GLfloat	xrot;									// X Rotation
GLfloat	yrot;									// Y Rotation
GLfloat xspeed;									// X Rotation Speed
GLfloat yspeed;									// Y Rotation Speed
GLfloat	z=-5.0f;								// Depth Into The Screen

GLfloat xMov;
GLfloat yMov;

//KEYS.H
bool	keys[256];								// Array Used For The Keyboard Routine

BOOL	lp;									// L Pressed?
BOOL	fp;									// F Pressed?
bool	mp;									// M Pressed?
bool	sp;									// Space Pressed?


#endif
