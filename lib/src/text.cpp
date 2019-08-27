#include <windows.h>											// Header File For Windows
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )

#include <gl\glu.h>												// Header File For The GLu32 Library
#include <stdio.h>												// Header File For Standard Input/Output

#include "text.h"											

GLuint fontTexture[1];

GLuint	base;
GLYPHMETRICSFLOAT gmf[256];										// Storage For Information About Our Outline Font Characters
	
GLvoid BuildFont(HDC *hDC)										// Build Our Bitmap Font
{
	HFONT	font;												// Windows Font ID

	base = glGenLists(MAX_CHARS);										// Storage For 256 Characters

	font = CreateFont(	-12,									// Height Of Font
						0,										// Width Of Font
						0,										// Angle Of Escapement
						0,										// Orientation Angle
						FW_BOLD,								// Font Weight
						FALSE,									// Italic
						FALSE,									// Underline
						FALSE,									// Strikeout
						ANSI_CHARSET,							// Character Set Identifier
						OUT_TT_PRECIS,							// Output Precision
						CLIP_DEFAULT_PRECIS,					// Clipping Precision
						ANTIALIASED_QUALITY,					// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,				// Family And Pitch
						NULL);									// Font Name
	
	//HDC hDC = window->hDC;
	SelectObject(*hDC, font);									// Selects The Font We Created

	wglUseFontOutlines(	*hDC,									// Select The Current DC
						0,										// Starting Character
						MAX_CHARS - 1,									// Number Of Display Lists To Build
						base,									// Starting Display Lists
						0.0f,									// Deviation From The True Outlines
						0.05f,									// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,						// Use Polygons, Not Lines
						gmf);									// Address Of Buffer To Recieve Data
	return;
}


GLvoid KillFont(GLvoid)											// Delete The Font
{
	glDeleteLists(base, 256);									// Delete All 256 Characters
}


GLvoid glPrint(float x, float y, float z, const char *fmt, int fontSize, ...)	// Custom GL "Print" Routine
{
	float		length=0;										// Used To Find The Length Of The Text
	char		text[256];										// Holds Our String
	unsigned int loop;
	va_list		ap;												// Pointer To List Of Arguments
	GLfloat fontScale = fontSize/12.0f;
	
	if (fmt == NULL)											// If There's No Text
		return;													// Do Nothing

	va_start(ap, fmt);											// Parses The String For Variables
	    vsprintf(text, fmt, ap);								// And Converts Symbols To Actual Numbers
	va_end(ap);													// Results Are Stored In Text

	for (loop=0;loop<(strlen(text));loop++)		// Loop To Find Text Length
	{
		length+=gmf[text[loop]].gmfCellIncX;					// Increase Length By Each Characters Width
	}

	glTranslatef(x - length, y, z);								// Position Text On The Screen
	glScalef(fontScale,fontScale,1.0f);
	
	glPushAttrib(GL_LIST_BIT);									// Pushes The Display List Bits
	glListBase(base);											// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);			// Draws The Display List Text
	glPopAttrib();												// Pops The Display List Bits
	
	glScalef(1/fontScale,1/fontScale,1.0f);
	glTranslatef(-x, -y, -z);									// Position Text On The Screen
}


GLvoid glPrintHead(GLint x, GLint y, const char *string, int fontSize)	// Where The Printing Happens
{
	char		text[256];										// Holds Our String
	va_list		ap;												// Pointer To List Of Arguments
	int  strLength;
	
	GLfloat fontScale = 10.0f*fontSize/12;
	
	va_start(ap, string);											// Parses The String For Variables
	    vsprintf(text, string, ap);								// And Converts Symbols To Actual Numbers
	va_end(ap);													// Results Are Stored In Text
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,400,0,400,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glTranslated(x,y,-1);								// Position The Text (0,0 - Bottom Left)
	glScalef(fontScale,fontScale,1.0f);
	glListBase(base);									// Choose The Font Set (0 or 1)
	strLength = strlen(text);
	//for(int i=0; i<strLength; i++)
	//	text[i]++;
	glCallLists(strlen(text),GL_UNSIGNED_BYTE,text);	// Write The Text To The Screen

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_LIGHTING);
}

GLvoid glPrintHead(GLint x, GLint y, int num, int fontSize)
{
	char numtext[100];

	sprintf(numtext, "%i", num);		//convert int to chars
	glPrintHead(x, y, numtext, fontSize);
}

GLvoid glPrintHead(GLint x, GLint y, GLfloat num, int fontSize)
{
	char numtext[100];
	sprintf(numtext, "%f", num);		//convert int to chars
	glPrintHead(x, y, numtext, fontSize);
}

///////////////////////////////// CREATE OPENGL 3D FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function creates a 3D windows font like "Arial", and returns a display list ID
/////
///////////////////////////////// CREATE OPENGL 3D FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

UINT CreateOpenGL3DFont(HDC& hDC, LPCWSTR strFontName, float extrude, font3d_s* inFont)	
//UINT CreateOpenGL3DFont(HDC& hDC, LPCSTR strFontName, float extrude, font3d_s* inFont)	
{
	UINT	fontListID = 0;								// This will hold the base ID for our display list
	HFONT	hFont;										// This will store the handle to our font

	// Here we generate the lists for each character we want to use.
	// This function then returns the base pointer, which will be 1 because
	// we haven't created any other lists.  If we generated another list after
	// this, the base pointer would be at 257 since the last one used was 256 (which is MAX_CHARS)
	fontListID = glGenLists(MAX_CHARS);					// Generate the list for the font

	// Now we actually need to create the font.  We use a windows function called:
	// CreateFont() that returns a handle to a font (HFONT).  Our CreateOpenGLFont()
	// function allows us to pass in a name and height.  For simplistic reasons, I left
	// other options out, but feel free to add them to your function (like bold, italic, width..)
	// In the last tutorial we passed in a height, now we pass in a extrude value.  This
	// value basically makes the thickness in 3D.  The height parameter in CreateFont() doesn't
	// matter now, so it doesn't really matter what value we put in, it is just ignored by wglUseFontOutlines().

	hFont = CreateFont(	0,								// This HEIGHT parameter is ignored by wglUseFontOutlines(). Use glScalef()
						0,								// The WIDTH (If we leave this zero it will pick the best width depending on the height)
						0,								// The angle of escapement
						0,								// The angle of orientation
						FW_BOLD,						// The font's weight (We want it bold)
						FALSE,							// Italic - We don't want italic
						FALSE,							// Underline - We don't want it underlined
						FALSE,							// Strikeout - We don't want it strikethrough
						ANSI_CHARSET,					// This is the type of character set
						OUT_TT_PRECIS,					// The Output Precision
						CLIP_DEFAULT_PRECIS,			// The Clipping Precision
						ANTIALIASED_QUALITY,			// The quality of the font - We want anitaliased fonts
						FF_DONTCARE|DEFAULT_PITCH,		// The family and pitch of the font.  We don't care.
						strFontName);					// The font name (Like "Arial", "Courier", etc...)

	// Now that we have created a new font, we need to select that font into our global HDC.
	// We store the old font so we can select it back in when we are done to avoid memory leaks.
	inFont->hOldFont = (HFONT)SelectObject(hDC, hFont);

	// This is the function that creates all the magic.  This will actually output the
	// polygons into our display lists, which creates the outlined characters.
	// But first, we need to give it our desired information.
	// One new thing from the last tutorial is GLYPH's.  A glyph is a 3D character.
	// The GLYPHMETRICSFLOAT structure used holds information about that 3D character,
	// such as it's width and height in 3D units, as well as orientation within it's bounding box.
	// We can use this information if we want to find out how long our sentences are in actual
	// unit lengths, not pixel length.
	wglUseFontOutlines(	hDC,							// This is the global HDC with the desired font selected.
						0,								// This is the starting ASCII value.
						MAX_CHARS - 1,					// This is the ending ASCII value to use (255 is the last).
						fontListID,						// This is the base pointer of our display list we wish to use.
						0,								// This is the deviation from a true outline (floating point)
						0.4f,							// This is the extrude value, or in other words, the thickness in Z.
						WGL_FONT_POLYGONS,				// We specify here that we want it rendered in polygons rather than lines
						inFont->g_GlyphInfo);					// The address to the buffer that will hold the 3D font info for each character.

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	inFont->g_FontListID = fontListID;
	return fontListID;									// Return the ID to the display list to use later
}


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

///////////////////////////////// GL DRAW 3D TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This draws 3D text onto the screen using OpenGL.
/////
///////////////////////////////// GL DRAW 3D TEXT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void glDraw3DText(const char *strString, font3d_s* inFont, ...)
{
	char		strText[256];							// This will hold our text to display
	va_list		argumentPtr;							// This will hold the pointer to the argument list
	float		unitLength=0.0f;						// This will store the length of the 3D Font in unit length

	// If you have never used a va_list, listen up.  Remember printf()?
	// or sprintf()?  Well, you can add unlimited arguments into the text like:
	// printf("My name is %s and I am %d years old!", strName, age);
	// Well, that is what va_list's do.  

	// First we need to check if there was even a string given
	if (strString == NULL)								// Check if a string was given
		return;											// Don't render anything then

	// First we need to parse the string for arguments given
	// To do this we pass in a va_list variable that is a pointer to the list of arguments.
	// Then we pass in the string that holds all of those arguments.
	va_start(argumentPtr, strString);					// Parse the arguments out of the string

	// Then we use a special version of sprintf() that takes a pointer to the argument list.
	// This then does the normal sprintf() functionality.
	vsprintf(strText, strString, argumentPtr);			// Now add the arguments into the full string

	va_end(argumentPtr);								// This resets and frees the pointer to the argument list.

	// Below we find out the total length of the characters in 3D units, then center them.

	for (int i=0; i < (int)strlen(strText); i++)		// Go through all of the characters
	{
		// Here we go through each character and add up it's length.
		// It doesn't matter where the text if facing in 3D, it uses a 2D system
		// for the width and height of the characters.  So X is the width, Y is the height.
		unitLength += inFont->g_GlyphInfo[strText[i]].gmfCellIncX;	
	}

	// Here we translate the text centered around the XYZ according to it's width.
	// Since we have the length, we can just divide it by 2, then subtract that from the X.
	// This will then center the text at that position, in the way of width.
	// Can you see how to center the height too if you wanted? (hint: .gmfCellIncY)
	glTranslatef(0.0f - (unitLength / 2), 0.0f, 0.0f);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


	// Now, before we set the list base, we need to save off the current one.
	glPushAttrib(GL_LIST_BIT);							// This saves the list base information

	// Then we want to set the list base to the font's list base, which should be 1 in our case.
	// That way when we call our display list it will start from the font's lists'.
	glListBase(inFont->g_FontListID);					// This sets the lists base

	// Now comes the actually rendering.  We pass in the length of the string,
	// then the data types (which are characters so its a UINT), then the actually char array.
	// This will then take the ASCII value of each character and associate it with a bitmap.
	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);

	glPopAttrib();										// Return the display list back to it's previous state
}


///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function frees our display lists
/////
///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void DestroyFont(HDC &hDC, font3d_s* fontIn)										
{
	glDeleteLists(fontIn->g_FontListID, MAX_CHARS);				// Free the display list
	SelectObject(hDC, fontIn->hOldFont);						// Select the old font back in so we don't have memory leaks
}
