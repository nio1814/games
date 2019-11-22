#ifndef _TGA_H
#define _TGA_H

#include "qtgl.h"

#define TGA_RGB	2
#define TGA_A		3
#define TGA_RLE	10

struct ImageTGA
{
	int channels = 0;
	int size_x = 0;	
	int size_y = 0;				
	unsigned char *data = nullptr;
};

ImageTGA *loadTGA(QString filename);
void TGA_Texture(GLuint textureArray[], const char* strFileName, int ID);

#endif
