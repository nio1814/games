#ifndef TEXTURE
#define TEXTURE

//#include <windows.h>									// Header File For Windows
//#include <gl\gl.h>										// Header File For The OpenGL32 Library
//#include <gl\glu.h>										// Header File For The GLu32 Library
//#include <gl\glaux.h>									// Header File For The Glaux Library
#include <stdio.h>										// Header File For Standard Input / Output
#include "qtgl.h"

#include "vector3d.h"

struct Texture
{
  Texture() {}
  Texture(const GLuint index);
  Texture(const std::string filename);
  
  bool hasTextures();

	std::vector<GLuint> layer;
	Vector3D color = Vector3D(255, 255, 255);
	std::string ID;
};

extern Texture nullTexture;

//AUX_RGBImageRec *LoadBMP(char *Filename);					// Loads A Bitmap Image
//int LoadGLTextures(texture_s *textures, char *filename);	// Load Bitmaps And Convert To Textures

#endif
