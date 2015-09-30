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
};



tImageTGA *Load_TGA(const char *filename);
void TGA_Texture(UINT textureArray[], LPSTR strFileName, int textureID);
void TGA_Texture(animData_s *aData, LPSTR strFileName, int ID);
void TGA_Texture(animData_s *aData, LPSTR strFileName, int ID, GLfloat center);



#endif



// www.morrowland.com
// apron@morrowland.com

