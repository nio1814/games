#ifndef TEXTURE
#define TEXTURE

//#include <windows.h>									// Header File For Windows
//#include <gl\gl.h>										// Header File For The OpenGL32 Library
//#include <gl\glu.h>										// Header File For The GLu32 Library
//#include <gl\glaux.h>									// Header File For The Glaux Library
#include <stdio.h>										// Header File For Standard Input / Output
#include <qopengl.h>

#include "vector3d.h"

struct texture_s
{
	GLuint layer[3];
	int numLayers;
	Vector3D color;
	char* ID;

	texture_s(){numLayers = 0;color = Vector3D(255,255,255);}
};

extern texture_s nullTexture;

//AUX_RGBImageRec *LoadBMP(char *Filename);					// Loads A Bitmap Image
//int LoadGLTextures(texture_s *textures, char *filename);	// Load Bitmaps And Convert To Textures

#endif
