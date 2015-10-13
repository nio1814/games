#ifndef MASKING
#define MASKING

//#include	<windows.h>							// Header File For Windows
//#include	<gl\gl.h>							// Header File For The OpenGL32 Library
//#include	<gl\glu.h>							// Header File For The GLu32 Library

#include	"texturecode.h"
#include "animation.h"

extern GLfloat LightAmbient[]; 				// Ambient Light Values ( NEW )
extern GLfloat LightDiffuse[];				 // Diffuse Light Values ( NEW )
extern GLfloat LightPosition[];				 // Light Position ( NEW )

extern bool	light;									// Lighting ON / OFF

//extern GLuint	texture[5];								// Storage for 3 textures
extern GLuint	filter;	

extern bool	masking;								// Masking On/Off
extern bool	scene;	

extern GLuint	loop;									// Generic Loop Variable

extern GLfloat	roll;									// Rolling Texture
extern int sss;

//AUX_RGBImageRec *LoadBMP(char *Filename);					// Loads A Bitmap Image
int LoadGLTextures(GLuint *texture, char filePath[]);
int LoadGLTextures(Animation *aData, char filePath[], int ID);
//int LoadGLTextures();								// Load Bitmaps And Convert To Textures
bool loadGLTexture(GLuint* texture, QString filename);

#endif
