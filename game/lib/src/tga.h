#ifndef _TGA_H
#define _TGA_H

//#include <windows.h>
//#include <gl/gl.h>

#include <qopengl.h>

#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10

struct ImageTGA
{
	int channels;
	int size_x;	
	int size_y;				
	unsigned char *data;
};

ImageTGA *load_TGA(const char *filename);
void TGA_Texture(GLuint textureArray[], const char* strFileName, int ID);

#endif
