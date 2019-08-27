#include<qglobal.h>

#ifdef Q_OS_WIN32
#include	<windows.h>							// Header File For Windows
#include	<stdio.h>							// Header File For Standard Input/Output ( ADD )
#include	<gl\gl.h>							// Header File For The OpenGL32 Library
#include	<gl\glu.h>							// Header File For The GLu32 Library
#include	<gl\glaux.h>

//MASKING
AUX_RGBImageRec *LoadBMP(char *Filename)					// Loads A Bitmap Image
{
	FILE *File=NULL;							// File Handle

	if (!Filename)								// Make Sure A Filename Was Given
	{
		return NULL;							// If Not Return NULL
	}

	File=fopen(Filename,"r");						// Check To See If The File Exists

	if (File)								// Does The File Exist?
	{
		fclose(File);							// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;								// If Load Failed Return NULL
}

int LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;							// Status Indicator
	AUX_RGBImageRec *TextureImage[5];					// Create Storage Space For The Texture Data
	memset(TextureImage,0,sizeof(void *)*5);				// Set The Pointer To NULL

	if ((TextureImage[0]=LoadBMP("Data/logo.bmp")) &&			// Logo Texture
	    (TextureImage[1]=LoadBMP("Data/mask1.bmp")) &&			// First Mask
	    (TextureImage[2]=LoadBMP("Data/image1.bmp")) &&			// First Image
	    (TextureImage[3]=LoadBMP("Data/mask2.bmp")) &&			// Second Mask
	    (TextureImage[4]=LoadBMP("Data/image2.bmp")))			// Second Image
	{
		Status=TRUE;							// Set The Status To TRUE
		glGenTextures(5, &texture[0]);					// Create Five Textures

		for (loop=0; loop<5; loop++)					// Loop Through All 5 Textures
		{
			glBindTexture(GL_TEXTURE_2D, texture[loop]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
		}
	}
	for (loop=0; loop<5; loop++)						// Loop Through All 5 Textures
	{
		if (TextureImage[loop])						// If Texture Exists
		{
			if (TextureImage[loop]->data)				// If Texture Image Exists
			{
				free(TextureImage[loop]->data);			// Free The Texture Image Memory
			}
			free(TextureImage[loop]);				// Free The Image Structure
		}
	}
	return Status;								// Return The Status
}






/*
int LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;							// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);				// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP("Data/Gesture.bmp"))
	{
		Status=TRUE;							// Set The Status To TRUE

		glGenTextures(3, &texture[0]);					// Create Three Textures
		
        // Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // ( NEW )
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // ( NEW )
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);


		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // ( NEW )

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); // ( NEW )
	}

	if (TextureImage[0])							// If Texture Exists
	{
		if (TextureImage[0]->data)					// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);						// Free The Image Structure
	}

	return Status;								// Return The Status
}
*/

//KEYS
void runKeys(bool keyStatus[])
{
	if (keyStatus['L'] && !lp)				// L Key Being Pressed Not Held?
	{
		lp=TRUE;				// lp Becomes TRUE
		light=!light;				// Toggle Light TRUE/FALSE
		
		if (!light)				// If Not Light
		{
			glDisable(GL_LIGHTING);		// Disable Lighting
		}
		else					// Otherwise
		{
			glEnable(GL_LIGHTING);		// Enable Lighting
		}
	}
		
	if (!keyStatus['L'])					// Has L Key Been Released?
	{
		lp=FALSE;				// If So, lp Becomes FALSE
	}

	if (keyStatus['F'] && !fp)				// Is F Key Being Pressed?
	{
		fp=TRUE;				// fp Becomes TRUE
		filter+=1;				// filter Value Increases By One
		if (filter>2)				// Is Value Greater Than 2?
		{
			filter=0;			// If So, Set filter To 0
		}
	}

	if (!keyStatus['F'])					// Has F Key Been Released?
	{
		fp=FALSE;				// If So, fp Becomes FALSE
	}
		
	if (keyStatus[VK_PRIOR])				// Is Page Up Being Pressed?
	{
		z-=0.02f;				// If So, Move Into The Screen
	}

	if (keyStatus[VK_NEXT])				// Is Page Down Being Pressed?
	{
		z+=0.02f;				// If So, Move Towards The Viewer
	}

	if (keyStatus[VK_UP])				// Is Up Arrow Being Pressed?
	{
		xspeed-=0.01f;				// If So, Decrease xspeed
	}

	if (keyStatus[VK_DOWN])				// Is Down Arrow Being Pressed?
	{
		xspeed+=0.01f;				// If So, Increase xspeed
	}

	if (keyStatus[VK_RIGHT])				// Is Right Arrow Being Pressed?
	{
		yspeed+=0.01f;				// If So, Increase yspeed
	}

	if (keyStatus[VK_LEFT])				// Is Left Arrow Being Pressed?
	{
		yspeed-=0.01f;				// If So, Decrease yspeed
	}

	return;
}
#endif
