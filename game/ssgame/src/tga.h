#ifndef _TGA_H
#define _TGA_H

#include "animation.h"


#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10



struct tImageTGA
{
	int channels;
	int size_x;	
	int size_y;				
	unsigned char *data;

	tImageTGA() : channels(0), size_x(0), size_y(0), data(NULL) {};

	~tImageTGA() {delete data;};
};



tImageTGA *Load_TGA(const char *filename);
tImageTGA loadTGA(QString filename);
void TGA_Texture(unsigned int textureArray[], const char* strFileName, int textureID);
void TGA_Texture(animData_s *aData, const char* strFileName, int ID);
void TGA_Texture(animData_s *aData, const char* strFileName, int ID, GLfloat center);



#endif



// www.morrowland.com
// apron@morrowland.com

