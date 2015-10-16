
#ifndef _3DSLOADER_H
#define _3DSLOADER_H

#include "3ds.h"

#define MAXTEXTURE 100

//////////////////////////////////////
//The 3dsLoader Class
//////////////////////////////////////
class C3dsLoader
{
	public:
		CLoad3DS mLoad3ds;						
//		UINT TextureArray3ds[MAXTEXTURE];
                unsigned int TextureArray3ds[MAXTEXTURE];
		t3DModel m3DModel;	

		void Init_3ds(char* filename);
		void Render_3ds();
                void Texture_3ds(unsigned int textureArray[], const char* strFileName, int ID);
		void Unload_3ds();
};


#endif

//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com
