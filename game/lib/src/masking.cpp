#include	"masking.h"

#include "qtgl.h"
#include "texture.h"
#include "texturecode.h"

#include <cstring>
#include <QGLWidget>

//GLfloat LightAmbient[]= { 0.9f, 0.9f, 0.9f, 1.0f }; 				// Ambient Light Values ( NEW )
GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 				// Ambient Light Values ( NEW )
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				 // Diffuse Light Values ( NEW )
GLfloat LightPosition[]= { 5.0f, 10.0f, 2.0f, 1.0f };				 // Light Position ( NEW )

bool	light;									// Lighting ON / OFF

GLuint	texture[5];								// Storage for 3 textures
GLuint	filter;	

bool	masking=true;								// Masking On/Off
bool	scene;	

GLuint	loop;									// Generic Loop Variable

GLfloat	roll;									// Rolling Texture

int sss = 5;

bool LoadGLTextures(GLuint *texture, char filePath[])								// Load Bitmaps And Convert To Textures
{
    bool Status = false;							// Status Indicator
	texture_t TextureImage[1];
	//GLuint texture[12];
	
	//AUX_RGBImageRec *TextureImage[5];					// Create Storage Space For The Texture Data

	memset(TextureImage,0,sizeof(texture_t)*1);				// Set The Pointer To NULL

	if (TextureLoadBMP(&TextureImage[0], filePath)) //&&			// First Image
	    //TextureLoadBMP(&TextureImage[3],"Data/FollowMask.bmp")) //&&			// Second Mask
	    //(TextureImage[4]=LoadBMP("Data/image2.bmp")))			// Second Image
	{
        Status=true;							// Set The Status To TRUE
		glGenTextures(1, &texture[0]);					// Create Five Textures
//GL_BGR_EXT
//GL_RGB
		for (loop=0; loop<1; loop++)					// Loop Through All 5 Textures
		{
			//loop = 0;
			{
				glBindTexture(GL_TEXTURE_2D, texture[loop]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//				gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[loop].width, TextureImage[loop].height,
//				 GL_BGR_EXT, GL_UNSIGNED_BYTE, TextureImage[loop].data);
				//glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop].width, TextureImage[loop].height,
				//	0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop].data);

				int e = glGetError();
			}
		}
	}
	for (loop=0; loop<1; loop++)						// Loop Through All 5 Textures
	//loop = 0;
	{
		//if (TextureImage[loop])						// If Texture Exists
		//{
			if (TextureImage[loop].data)				// If Texture Image Exists
			{
				Tex_Free(TextureImage[loop].data);			// Free The Texture Image Memory
			}
			//free(TextureImage[loop]);				// Free The Image Structure
		//}
	}

	return Status;								// Return The Status
}

bool loadGLTexture(GLuint* texture, QString filename)
{
	bool status = false;

//	texture = QGLWidget::bindTexture(QImage(filename), GL_TEXTURE_2D);
	QImage image = QGLWidget::convertToGLFormat(QImage(filename));
    if(image.isNull())
        qErrnoWarning("Failed to open file %s\n", filename.toLatin1().constData());
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
    int textureType;
    if(image.hasAlphaChannel())
        textureType = GL_RGBA;
    else
        textureType = GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, textureType, image.width(), image.height(), 0, textureType, GL_UNSIGNED_BYTE, image.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	/*QGLWidget *qgl;
	*texture = qgl->bindTexture(QImage(filename), GL_TEXTURE_2D);*/

	return status;
}

