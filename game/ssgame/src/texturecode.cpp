#include	"texturecode.h"

//#include <windows.h>								// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>								// Header File For Windows Math Library
#include <stdlib.h>
#include "qtgl.h"


#include	"error.h"

p_texdata Tex_Alloc(int size)
{
	p_texdata retr;
	retr = (p_texdata)malloc(size);
	//retr = VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
	//tr = (p_texdata )GlobalAlloc(GMEM_FIXED, size);

//	if (retr == NULL) Error("Tex_Alloc() failed - tried to allocate %d bytes", size);

	return retr;
}

void Tex_Free(p_texdata ptr)
{
	free(ptr);
	//if (!VirtualFree(ptr, 0, MEM_RELEASE))
/*	if (GlobalFree((HGLOBAL)ptr))
	{
		DWORD lastError;
		if ((lastError = GetLastError()) != NO_ERROR)
			Error("Tex_Free() failed on error %d", lastError);
	}*/
}

/*
bool TextureLoad___ (char *filename)

prereq: none
proreq:
	tex->width contains the image in filename's width
	tex->height contains the image in filename's height
	tex->bytes_per_pixel contains the image in filename's bytes per pixel (3 or 4)
	tex->data contains the interleaved RGB data

returns:
	true if loading all was sucessful
	false if an error occured (mind you, tex->data will be freed if this occurs)
*/


//*********************************** LOAD THE IMAGE *********************************** 

/*
typedef struct {
  unsigned short        id PACKED;          //'BM' 0x4d42

  0  unsigned long         filesize PACKED;
  1  unsigned long         reserved PACKED;         //0
  2  unsigned long         pictureoffset PACKED;

  3  unsigned long         headersize PACKED;     //40
  4  unsigned long         width PACKED;
  5  unsigned long         height PACKED;
  6  unsigned short        planes PACKED;
     unsigned short        bpp PACKED;
  7  unsigned long         compression PACKED;
  8  unsigned long         picturesize PACKED;
  9  unsigned long         width_in_ppm PACKED;
  A  unsigned long         height_in_ppm PACKED;
  B  unsigned long         colors_used PACKED;
  C  unsigned long         important_colors PACKED;
} bmp_header;


typedef struct tagBITMAPFILEHEADER { // bmfh 
        WORD    bfType; 
        DWORD   bfSize; 
        WORD    bfReserved1; 
        WORD    bfReserved2; 
        DWORD   bfOffBits; 
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER{ // bmih 
   DWORD  biSize; 
   LONG   biWidth; 
   LONG   biHeight; 
   WORD   biPlanes; 
   WORD   biBitCount 
   DWORD  biCompression; 
   DWORD  biSizeImage; 
   LONG   biXPelsPerMeter; 
   LONG   biYPelsPerMeter; 
   DWORD  biClrUsed; 
   DWORD  biClrImportant; 
} BITMAPINFOHEADER; 

typedef struct tagBITMAPCOREHEADER { // bmch 
        DWORD   bcSize; 
        WORD    bcWidth; 
        WORD    bcHeight; 
        WORD    bcPlanes; 
        WORD    bcBitCount; 
} BITMAPCOREHEADER; 

*/

bool TextureLoadBMP(texture_t *tex, char *filename)			// Loads A TGA File Into Memory
{
/*	BITMAPFILEHEADER	bmfh;

	unsigned int		src_extraDataSize = 0;
	p_texdata			src_extraData = NULL;
	unsigned int		src_palDataSize = 0;

	BITMAPINFOHEADER	*bmih = NULL;
	BITMAPCOREHEADER	*bmch = NULL;

	unsigned int		src_bitsPerPixel = 0;			//the src iamge's bits per pixel
	unsigned int		src_compression = 0;
	unsigned char		*src_palette = NULL;
	unsigned int		src_palIndexCount = 0;

	GLuint				dest_imageSize = 0;				//the dest image's size

	DWORD		dwBytesRead;	//for ReadFile()

//open the file
	HANDLE hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
	{
		Error("I Couldn't Open the BMP");
		return false;
	}

//read the BITMAPFILEHEADER struct
	if ((!ReadFile(hFile, &bmfh, sizeof(bmfh), &dwBytesRead, NULL)) ||
		(dwBytesRead != sizeof(bmfh)))
	{
		CloseHandle(hFile);
		Error( "I Couldn't Read The Bitmap File Header.  This Bitmap Is Probably Corrupt");
		return false;
	}

	if (bmfh.bfType != 0x4D42)
	{
		MessageBox(NULL, filename, "ERROR", MB_OK);
//		Error("The Bitmap ID Was Incorrect.  This Bitmap Is Probably Corrupt");
		if (MessageBox(
				NULL,
				"The Bitmap ID Is Incorrect.  This Bitmap Is Probably Corrupt"
				"Click OK To Proceed Anyways.",
				"Error",
				MB_OKCANCEL) == IDCANCEL)
		{
			CloseHandle(hFile);
			return false;
		}
	}

//alloc mem to store intermediate data, between the bmfh and the bitmap bits

	src_extraDataSize = bmfh.bfOffBits - sizeof(bmfh);
	if (!(src_extraData = Tex_Alloc(src_extraDataSize)))
	{
		CloseHandle(hFile);
		Error("I Couldnt Load The File Header.  Unable to Alloc %u Bytes of Memory", src_extraDataSize);
		return false;
	}

//read the intermediate data - either a BITMAPCOREINFO or a BITMAPINFO struct

	if ((!ReadFile(hFile, src_extraData, src_extraDataSize, &dwBytesRead, NULL)) ||
		(dwBytesRead != src_extraDataSize))
	{
		Tex_Free(src_extraData);
		CloseHandle(hFile);
		Error( "I Couldn't Read The Bitmap File Header.  This Bitmap Is Probably Corrupt");
		return false;
	}

//and gather the useful stats...
	bmih = (BITMAPINFOHEADER *)src_extraData;
	bmch = (BITMAPCOREHEADER *)src_extraData;

	if (bmih->biSize == 12)
	{
		//use the bmch

		//read stats from header
		tex->width = bmch->bcWidth;
		tex->height = bmch->bcHeight;
		src_bitsPerPixel = bmch->bcBitCount;
		src_palIndexCount = 0;
		src_compression = 0;
	}
	else if (bmih->biSize == 40)
	{
		//use the bmih

		tex->width = bmih->biWidth;
		tex->height = bmih->biHeight;
		src_bitsPerPixel = bmih->biBitCount;
		src_palIndexCount = bmih->biClrUsed;
		src_compression = bmih->biCompression;
	}
	else
	{
		//corrupt bitmap

		Tex_Free(src_extraData);
		CloseHandle(hFile);
		Error( "The Bitmap File Header had an Invalid Size of %d.  This Bitmap Is Probably Corrupt", bmih->biSize);
		return false;
	}

	switch (src_compression)
	{
	case BI_RGB:
		break;
	case BI_RLE4:
	case BI_RLE8:
	case BI_BITFIELDS:
	default:
		Tex_Free(src_extraData);
		CloseHandle(hFile);
		Error("This Image is RLE Compressed.  This Screensaver Does Not Yet Support RLE Compressed BMP files.");
		return false;
	}

	switch (src_bitsPerPixel)
	{
	case 1:
	case 4:
	case 8:
	case 16:
	case 24:
	case 32:
		tex->bytes_per_pixel = 3;
		break;
	default:
		Tex_Free(src_extraData);
		CloseHandle(hFile);
		Error("The Bits Per Pixel Is %d, An Unsupported Value.", src_bitsPerPixel);
		return false;
	}

//determine how much extra data is remaining for the palette
	src_palDataSize = src_extraDataSize - sizeof(bmfh) - bmih->biSize;

//allocate the dest image
	dest_imageSize = tex->width * tex->height * tex->bytes_per_pixel;
	tex->data = Tex_Alloc(dest_imageSize);

	if (tex->data==NULL)
	{
		Tex_Free(src_extraData);
		CloseHandle(hFile);
		Error("I Couldnt Load the Image.  Unable to Allocate %u Bytes of Memory.", dest_imageSize);
		return false;
	}

//when exactly do we need to load a palette?
//is it only for 1,4,8-bpp files?

	if (src_bitsPerPixel <= 8)					//if an offset to the image exists...
	{
		//if (palIndexCount > 256) then we cant grab all the indecies
		if (src_palIndexCount == 0) src_palIndexCount = (1 << src_bitsPerPixel);
		if (src_palIndexCount > 256) src_palIndexCount = 256;
		src_palette = (unsigned char *)bmih + (WORD)bmih->biSize;
	}

	//for reading the rows of the bitmap and for calc'ing the row offset
	p_texdata	rowPtr = NULL;
	unsigned int rowSize = tex->width * src_bitsPerPixel;
	rowSize = (rowSize>>3) + !!(rowSize & 7);

	//waste of space - thank the people at microsoft for this idea - the row offset
	unsigned int rowOffset = rowSize & 3;
	if (rowOffset)	rowOffset = 4 - rowOffset;

	//used for indexed bitmaps:
	GLubyte curByte;
	int current_bit_offset = 8 - src_bitsPerPixel;
	int pixels_per_byte = 8 / src_bitsPerPixel;
	int pixel_bitmask = (1 << src_bitsPerPixel) - 1;
	int index;

	rowPtr = tex->data;
	for (int y = 0; y < (int)tex->height; y++)
	{

		//load the poop as indexed, then convert it from the palette
		if (src_bitsPerPixel <= 8)
		{
			//load these per-byte and convert them as we go
			for (int x = 0; x < (int)tex->width; x++)
			{
				if ((x % pixels_per_byte) == 0)
				{
					current_bit_offset = 8 - src_bitsPerPixel;
					if ((!ReadFile(hFile, &curByte, 1, &dwBytesRead, NULL)) ||
						(dwBytesRead != 1))
					{
						Tex_Free(src_extraData);
						Tex_Free(tex->data);	tex->data = NULL;
						CloseHandle(hFile);
						Error("There Was An Error Reading Image Byte <%d,%d>", x, y);
						return false;
					}

					index = (curByte >> current_bit_offset) & pixel_bitmask;
					current_bit_offset -= src_bitsPerPixel;
					memcpy(rowPtr, &src_palette[index<<2], tex->bytes_per_pixel);
				}
				else
				{
					index = (curByte >> current_bit_offset) & pixel_bitmask;
					current_bit_offset -= src_bitsPerPixel;
					memcpy(rowPtr, &src_palette[index<<2], tex->bytes_per_pixel);
				}
				rowPtr += tex->bytes_per_pixel;
			}
		}
		else
		{	//load the poop as true color
			for (int x = 0; x < (int)tex->width; x++)
			{
				int read_pixel;
				unsigned int src_bytesPerPixel = src_bitsPerPixel>>3;
				if ((!ReadFile(hFile, &read_pixel, src_bytesPerPixel, &dwBytesRead, NULL)) ||
					(dwBytesRead != src_bytesPerPixel))
				{
					Tex_Free(src_extraData);
					Tex_Free(tex->data);	tex->data = NULL;
					CloseHandle(hFile);
					Error("There Was An Error Reading Image Pixel <%d,%d>", x, y);
					return false;
				}
				switch (src_bytesPerPixel) {
				case 2:
					//expand
					rowPtr[0] = ((read_pixel >> 5*0) & ((1<<5)-1)) << (8-5);
					rowPtr[1] = ((read_pixel >> 5*1) & ((1<<5)-1)) << (8-5);
					rowPtr[2] = ((read_pixel >> 5*2) & ((1<<5)-1)) << (8-5);
					break;
				case 3:
				case 4:
					memcpy(rowPtr, &read_pixel, 3);
					break;
				}
				rowPtr += tex->bytes_per_pixel;
			}
		}

		if (rowOffset)
		{
			SetFilePointer(hFile, rowOffset, NULL, FILE_CURRENT);
			if (GetLastError() != NO_ERROR)
			{
				Tex_Free(src_extraData);
				Tex_Free(tex->data);	tex->data = NULL;
				CloseHandle(hFile);
				Error("I was Unable to Seek Through the Offset of Row %d", y);
				return false;
			}
		}
	}

	Tex_Free(src_extraData);

	CloseHandle(hFile);

	//tex->flags |= TEXTURE_FLAG_BGR;
*/
	return true;
}
