/************************************************************
*	APRON TUTORIAL PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
************************************************************/
#include "3dsLoader.h"

#include "qtgl.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//										 INIT 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Init_3ds(char* filename)
{
	mLoad3ds.Import3DS(&m3DModel, filename);						
	
	//add texture stuff later
	for(int i = 0; i < m3DModel.numOfMaterials; i++)				
	{
		if(strlen(m3DModel.pMaterials[i].strFile) > 0)				
		{
			//Texture_3ds(TextureArray3ds, m3DModel.pMaterials[i].strFile, i);			
			CreateTexture(TextureArray3ds, m3DModel.pMaterials[i].strFile, i);			
		}
		
		m3DModel.pMaterials[i].texureId = i;						
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										RENDER 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Render_3ds()
{
	
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	
	for(int i = 0; i < m3DModel.numOfObjects; i++)
	{
		//i=0;
		if(m3DModel.pObject.size() <= 0) break;						
		
		t3DObject *pObject = &m3DModel.pObject[i];					
		
		if(pObject->bHasTexture)									
		{									
			glEnable(GL_TEXTURE_2D);								
			
			glColor3ub(255, 255, 255);								
			
			glBindTexture(GL_TEXTURE_2D, TextureArray3ds[pObject->materialID]); 
		} 
		else 
		{
			glDisable(GL_TEXTURE_2D);								
			
			glColor3ub(155, 255, 255);								
		}
		
		glBegin(GL_TRIANGLES);										
		
		for(int j = 0; j < pObject->numOfFaces; j++)
		{
			//j=0;
			for(int whichVertex = 0; whichVertex < 3; whichVertex++)
			{
				int index = pObject->pFaces[j].vertIndex[whichVertex];
				
				glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
				if(pObject->bHasTexture) {
					
					if(pObject->pTexVerts) {
						glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
					}
				} else {
					int msize = m3DModel.pMaterials.size();
					//if(m3DModel.pMaterials.size() < pObject->materialID) 
					//if(msize < pObject->materialID) 
					//{
                        unsigned char *pColor = m3DModel.pMaterials[pObject->materialID].color;
						
						glColor3ub(pColor[0], pColor[1], pColor[2]);
					//}
				}
				
				glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
			}
		}
		
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
	glDisable(GL_LIGHTING);

}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										TEXTURE 3DS			jpeg or bmp
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Texture_3ds(unsigned int textureArray[], const char* strFileName, int ID)
{
//	AUX_RGBImageRec *pBitMap = NULL;
	FILE *pFile = NULL;									
	unsigned char *pJpeg = NULL;
	unsigned long width, height; 
	int type;
	//CJPEGFile jpeg;
	char tempstring[5] = {0};
	
	strncpy(tempstring, strFileName + strlen(strFileName)-4, 4);
	
	char FilePath[200];
	
	sprintf(FilePath, "data/texture/%s", strFileName);
	
	
	if(!strFileName) return;
	
	if(!strcmp(tempstring, ".BMP") || !strcmp(tempstring, ".bmp"))
	{
		pFile = fopen(FilePath,"r");					
		
		if(pFile)										
		{
//			pBitMap = auxDIBImageLoad(FilePath);
			type = 1;
		}
		else											
		{											
//			MessageBox(NULL, FilePath /*"couldn't find texture!"*/, "Error!", MB_OK);
            qErrnoWarning("couldn't find texture!");
			exit(0);
		}
	} 
	else if(!strcmp(tempstring, ".JPG") || !strcmp(tempstring, "JPEG")) 
	{
		/*jpeg.GetSize(FilePath, width, height);
		pJpeg = new unsigned char[width*height*3];
		jpeg.Load(FilePath, 24, pJpeg);
		type = 2;*/
		;
	}
	
	
	glGenTextures(1, &textureArray[ID]);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	
    /*if(type==1)
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitMap->sizeX, pBitMap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitMap->data);
    if(type==2)
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pJpeg);*/
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
    /*if (pBitMap)
	{
		if (pBitMap->data)						
		{
			free(pBitMap->data);				
		}
		free(pBitMap);							
    }*/
	
	if (pJpeg) delete [] pJpeg;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//										UNLOAD 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Unload_3ds()
{
	for(int i = 0; i < m3DModel.numOfObjects; i++)	
	{
		delete [] m3DModel.pObject[i].pFaces;
		delete [] m3DModel.pObject[i].pNormals;
		delete [] m3DModel.pObject[i].pVerts;
		delete [] m3DModel.pObject[i].pTexVerts;
	}
}












