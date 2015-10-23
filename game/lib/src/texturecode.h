#ifndef TEXTURECODE
#define TEXTURECODE

//#include	<windows.h>

typedef unsigned char * p_texdata;

typedef struct {
	p_texdata data;
	int width;
	int height;
	int bytes_per_pixel;
	int flags;
} texture_t;


void Tex_Free(p_texdata ptr);
p_texdata Tex_Alloc(int size);
bool TextureLoadBMP(texture_t *tex, char *filename);
//bool TextureLoadBMP(texture_t *tex, char *filename);

#endif

