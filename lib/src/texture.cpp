//#include <windows.h>									// Header File For Windows
//#include <gl\gl.h>										// Header File For The OpenGL32 Library
//#include <gl\glu.h>										// Header File For The GLu32 Library

#include "texture.h"

#include <cstring>

/*AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}*/


int LoadGLTextures(Texture* textureholder, char *filename)                                    // Load Bitmaps And Convert To Textures
{
    int Status=false;									// Status Indicator
#if 0
//    AUX_RGBImageRec *TextureImage[1];						// Create Storage Space For The Textures
    int loop=0;

	memset(TextureImage,0,sizeof(void *)*1);			// Set The Pointer To NULL
    if (*TextureImage=LoadBMP(filename))/* &&// Load The Floor Texture
        (TextureImage[1]=LoadBMP("Data/Ball.bmp")) &&	// Load the Light Texture
        (TextureImage[2]=LoadBMP("Data/EnvRoll.bmp")))	// Load the Wall Texture*/
	{   
        Status=true;									// Set The Status To TRUE
    GLuint textureIndex;
    //glGenTextures(1, &textureholder->layer[textIdx]);					// Create The Texture
    glGenTextures(1, &textureIndex);
    textureholder->layer.push_back(textureIndex);
		//for (int loop=0; loop<3; loop++)				// Loop Through 5 Textures
		//{
			glBindTexture(GL_TEXTURE_2D, textureholder->layer[textIdx]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//}
		//for (loop=0; loop<3; loop++)					// Loop Through 5 Textures
		//{
		
		if (TextureImage[0])						// If Texture Exists
			{
				if (TextureImage[0]->data)			// If Texture Image Exists
				{
					free(TextureImage[0]->data);		// Free The Texture Image Memory
				}
				free(TextureImage[0]);				// Free The Image Structure 
			}
		textureholder->numLayers++;
	}
	
#endif
	return Status;										// Return The Status
}


/*
int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    int Status=FALSE;									// Status Indicator
    AUX_RGBImageRec *TextureImage[3];					// Create Storage Space For The Textures
    memset(TextureImage,0,sizeof(void *)*3);			// Set The Pointer To NULL
    if ((TextureImage[0]=LoadBMP("Data/EnvWall.bmp")) &&// Load The Floor Texture
        (TextureImage[1]=LoadBMP("Data/Ball.bmp")) &&	// Load the Light Texture
        (TextureImage[2]=LoadBMP("Data/EnvRoll.bmp")))	// Load the Wall Texture
	{   
		Status=TRUE;									// Set The Status To TRUE
		glGenTextures(3, &texture[0]);					// Create The Texture
		for (int loop=0; loop<3; loop++)				// Loop Through 5 Textures
		{
			glBindTexture(GL_TEXTURE_2D, texture[loop]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		for (loop=0; loop<3; loop++)					// Loop Through 5 Textures
		{
			if (TextureImage[loop])						// If Texture Exists
			{
				if (TextureImage[loop]->data)			// If Texture Image Exists
				{
					free(TextureImage[loop]->data);		// Free The Texture Image Memory
				}
				free(TextureImage[loop]);				// Free The Image Structure 
			}
		}
	}

	return Status;										// Return The Status
}
*/

Texture::Texture(const GLuint index)
{
  this->layer.push_back(index);
}

bool Texture::hasTextures()
{
  return !this->layer.empty();
}
