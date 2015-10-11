#include "tga.h"

#include "qtgl.h"
#include <stdio.h>
#include <stdlib.h>

#include "animation.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
//										TGA TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////
void TGA_Texture(GLuint textureArray[], const char* strFileName, int ID)
{
	if(!strFileName)
		return;

	tImageTGA *pBitMap = Load_TGA(strFileName);

	if(pBitMap == NULL)	exit(0);

	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	int textureType = GL_RGB;
	if(pBitMap->channels == 4)
		textureType = GL_RGBA;
	//gluBuild2DMipmaps(GL_TEXTURE_2D, pBitMap->channels, pBitMap->size_x, pBitMap->size_y, textureType, GL_UNSIGNED_BYTE, pBitMap->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	
	
	if (pBitMap)									
	{
		if (pBitMap->data)						
			free(pBitMap->data);
		free(pBitMap);							
	}
}


void TGA_Texture(animData_s *aData, const char* strFileName, int ID)
{
	if(!strFileName)	return;

	tImageTGA *pBitMap = Load_TGA(strFileName);

	if(pBitMap == NULL)	exit(0);

	glGenTextures(1, &aData->textures[ID]);
	glBindTexture(GL_TEXTURE_2D, aData->textures[ID]);
	int textureType = GL_RGB;
	if(pBitMap->channels == 4)	textureType = GL_RGBA;
//	gluBuild2DMipmaps(GL_TEXTURE_2D, pBitMap->channels, pBitMap->size_x, pBitMap->size_y, textureType, GL_UNSIGNED_BYTE, pBitMap->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	
	if(ID ==0)
	{
		aData->scale[ID] = Vector2D(1.0f,1.0f);
			//aData->hScale[ID] = 1.0f;
			//aData->wScale[ID] = 1.0f;
		aData->pixels = Vector2D(pBitMap->size_x, pBitMap->size_y);
			//aData->pixelsW = pBitMap->size_x;
			//aData->pixelsH = pBitMap->size_y;
	}
	else
	{
		aData->scale[ID] = Vector2D(pBitMap->size_x / static_cast<GLfloat>(aData->pixels.x), pBitMap->size_y / static_cast<GLfloat>(aData->pixels.y));
			//aData->hScale[ID] = pBitMap->size_y / static_cast<GLfloat>(aData->pixelsH);
			//aData->wScale[ID] = pBitMap->size_x / static_cast<GLfloat>(aData->pixelsW);
	}

	if (pBitMap)									
	{
		if (pBitMap->data)						
		{
			free(pBitMap->data);	
		}
		free(pBitMap);							
	}
	
	aData->numTextures++;
	if(aData->numTextures>1)
		aData->animates = true;					//need more than one frame to animate
}

void TGA_Texture(animData_s *aData, const char* strFileName, int ID, GLfloat center)
{
	TGA_Texture(aData, strFileName, ID);
	aData->centers[19] = center;

	return;
}

tImageTGA *Load_TGA(const char *strfilename)
{
	tImageTGA *pImgData	= NULL;		
	FILE *pFile			= NULL;
	short width			= 0;
	short height			= 0;
	quint8 length			= 0;
	quint8 imgType		= 0;	    
	quint8 bits			= 0;
	int channels		= 0;	    
	int stride			= 0;
	int i				= 0;
	static int timecalled=0;
	char angletext[100];
	sprintf(angletext, "%i", timecalled++);
	/*if(timecalled>280)
	{
		MessageBox(NULL, strfilename, "ERROR", 0);
		MessageBox(NULL, angletext, "ERROR", 0);
	}*/
		
	if((pFile = fopen(strfilename, "rb")) == NULL) 
	{
//		MessageBox(NULL, "Error loading tga file.", "ERROR", MB_OK);
//		MessageBox(NULL, angletext, "ERROR", MB_OK);
		return NULL;
	}

	pImgData = (tImageTGA*)malloc(sizeof(tImageTGA));
	
	fread(&length, sizeof(quint8), 1, pFile);
	
	fseek(pFile,1,SEEK_CUR); 
	
	fread(&imgType, sizeof(quint8), 1, pFile);
	
	fseek(pFile, 9, SEEK_CUR); 
	
	fread(&width,  sizeof(short), 1, pFile);
	fread(&height, sizeof(short), 1, pFile);
	fread(&bits,   sizeof(quint8), 1, pFile);
	
	fseek(pFile, length + 1, SEEK_CUR); 
	
	if(imgType != TGA_RLE)
	{
		// Check for 24 or 32 Bit
		if(bits == 24 || bits == 32)
		{
			
			channels = bits / 8;
			stride = channels * width;
			pImgData->data = new unsigned char[stride * height];
			
			for(int y = 0; y < height; y++)
			{
				unsigned char *pLine = &(pImgData->data[stride * y]);
				
				fread(pLine, stride, 1, pFile);
				
				for(i = 0; i < stride; i += channels)
				{
					int temp     = pLine[i];
					pLine[i]     = pLine[i + 2];
					pLine[i + 2] = temp;
				}
			}
		}
				
		// Check for 16 Bit
		else if(bits == 16)
		{
			unsigned short pixels = 0;
			int r=0, g=0, b=0;
			
			channels = 3;
			stride = channels * width;
			pImgData->data = new unsigned char[stride * height];
			
			for(int i = 0; i < width*height; i++)
			{
				fread(&pixels, sizeof(unsigned short), 1, pFile);
				
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;
				
				pImgData->data[i * 3 + 0] = r;
				pImgData->data[i * 3 + 1] = g;
				pImgData->data[i * 3 + 2] = b;
			}
		}	
		
		else
			return NULL;
	}
	
	else
	{
		
		quint8 rleID = 0;
		int colorsRead = 0;
		channels = bits / 8;
		stride = channels * width;
		
		pImgData->data = new unsigned char[stride * height];
		quint8 *pColors = new quint8 [channels];
		
		while(i < width*height)
		{
			
			fread(&rleID, sizeof(quint8), 1, pFile);
			
			
			if(rleID < 128)
			{
				rleID++;
				
				while(rleID)
				{
					fread(pColors, sizeof(quint8) * channels, 1, pFile);
					
					pImgData->data[colorsRead + 0] = pColors[2];
					pImgData->data[colorsRead + 1] = pColors[1];
					pImgData->data[colorsRead + 2] = pColors[0];
					
					if(bits == 32)	pImgData->data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += channels;
				}
			}
			
			else
			{
				rleID -= 127;
				
				fread(pColors, sizeof(quint8) * channels, 1, pFile);
				
				while(rleID)
				{
					pImgData->data[colorsRead + 0] = pColors[2];
					pImgData->data[colorsRead + 1] = pColors[1];
					pImgData->data[colorsRead + 2] = pColors[0];
					
					if(bits == 32)	pImgData->data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += channels;
				}
			}
		}
	}
	
	fclose(pFile);
	
	
	pImgData->channels  = channels;
	pImgData->size_x    = width;
	pImgData->size_y    = height;
	
	return pImgData;
}

tImageTGA loadTGA(QString filename)
{
	tImageTGA pImgData;
	FILE* pFile;
	short width			= 0;
	short height			= 0;
	quint8 length			= 0;
	quint8 imgType		= 0;
	quint8 bits			= 0;
	int channels		= 0;
	int stride			= 0;
	int i				= 0;

	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		qErrnoWarning("Error loading tga file %s\n", filename.toLatin1().data());
//		MessageBox(NULL, angletext, "ERROR", MB_OK);
	}
	else
	{
		QDataStream fileData(&file);

		fileData >> length;
//		fread(&length, sizeof(quint8), 1, pFile);

//		fseek(pFile,1,SEEK_CUR);
		fileData.skipRawData(1);

//		fread(&imgType, sizeof(quint8), 1, pFile);
		fileData >> imgType;

//		fseek(pFile, 9, SEEK_CUR);
		fileData.skipRawData(9);

		fread(&width,  sizeof(short), 1, pFile);
		fread(&height, sizeof(short), 1, pFile);
		fread(&bits,   sizeof(quint8), 1, pFile);

		fileData >> width >> height >> bits;

//		fseek(pFile, length + 1, SEEK_CUR);
		fileData.skipRawData(length+1);

		if(imgType != TGA_RLE)
		{
			// Check for 24 or 32 Bit
			if(bits == 24 || bits == 32)
			{

				channels = bits / 8;
				stride = channels * width;
				pImgData.data = new unsigned char[stride * height];

				for(int y = 0; y < height; y++)
				{
					unsigned char *pLine = &(pImgData.data[stride * y]);

//					fread(pLine, stride, 1, pFile);
					fileData.readRawData((char*)pLine, stride);

					for(i = 0; i < stride; i += channels)
					{
						int temp     = pLine[i];
						pLine[i]     = pLine[i + 2];
						pLine[i + 2] = temp;
					}
				}
			}

			// Check for 16 Bit
			else if(bits == 16)
			{
				unsigned short pixels = 0;
				int r=0, g=0, b=0;

				channels = 3;
				stride = channels * width;
				pImgData.data = new unsigned char[stride * height];

				for(int i = 0; i < width*height; i++)
				{
//					fread(&pixels, sizeof(unsigned short), 1, pFile);
					fileData >> pixels;

					b = (pixels & 0x1f) << 3;
					g = ((pixels >> 5) & 0x1f) << 3;
					r = ((pixels >> 10) & 0x1f) << 3;

					pImgData.data[i * 3 + 0] = r;
					pImgData.data[i * 3 + 1] = g;
					pImgData.data[i * 3 + 2] = b;
				}
			}
//			else
//				return NULL;
		}
		else
		{

			quint8 rleID = 0;
			int colorsRead = 0;
			channels = bits / 8;
			stride = channels * width;

			pImgData.data = new unsigned char[stride * height];
			quint8 *pColors = new quint8 [channels];

			while(i < width*height)
			{

//				fread(&rleID, sizeof(quint8), 1, pFile);
				fileData >> rleID;


				if(rleID < 128)
				{
					rleID++;

					while(rleID)
					{
//						fread(pColors, sizeof(quint8) * channels, 1, pFile);
						fileData.readRawData((char*)pColors, sizeof(quint8)*channels);

						pImgData.data[colorsRead + 0] = pColors[2];
						pImgData.data[colorsRead + 1] = pColors[1];
						pImgData.data[colorsRead + 2] = pColors[0];

						if(bits == 32)
							pImgData.data[colorsRead + 3] = pColors[3];

						i++;
						rleID--;
						colorsRead += channels;
					}
				}

				else
				{
					rleID -= 127;

//					fread(pColors, sizeof(quint8) * channels, 1, pFile);
					fileData.readRawData((char*)pColors, sizeof(quint8)*channels);

					while(rleID)
					{
						pImgData.data[colorsRead + 0] = pColors[2];
						pImgData.data[colorsRead + 1] = pColors[1];
						pImgData.data[colorsRead + 2] = pColors[0];

						if(bits == 32)	pImgData.data[colorsRead + 3] = pColors[3];

						i++;
						rleID--;
						colorsRead += channels;
					}
				}
			}
			delete[] pColors;
		}

		fclose(pFile);


		pImgData.channels  = channels;
		pImgData.size_x    = width;
		pImgData.size_y    = height;
	}

	return pImgData;
}


//Ronny André Reierstad
//www.morrowland.com
//apron@morrowland.com

