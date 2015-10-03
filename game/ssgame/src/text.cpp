//#include <windows.h>								// Header File For Windows
//#include <gl\gl.h>								// Header File For The OpenGL32 Library
//#include <gl\glu.h>
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <string.h>

#include "text.h"
#include "masking.h"

using std::string;

GLuint	base;							// Base Display List For The Font Set
GLfloat	cnt1;							// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2;							// 2nd Counter Used To Move Text & For Coloring
typedef int GLYPHMETRICSFLOAT;
GLYPHMETRICSFLOAT *gmf;

GLuint NUMFONT = 4;
GLuint NUMBMAPFONTS = 2;
GLuint NUMOUTFONTS = NUMFONT - NUMBMAPFONTS;

GLuint NUMFONTS = NUMFONT;

GLuint fontTexture[1];

#if 0
GLvoid BuildFont(HDC *hDC)								// Build Our Font Display List
{
	int		loop;
	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord
	string	fontName;									//string for font name
	fonts	currentFont;

	base = glGenLists(128*NUMFONTS);							// Creating 256 Display Lists
	gmf = new GLYPHMETRICSFLOAT[NUMFONTS*128];

	glBindTexture(GL_TEXTURE_2D, fontTexture[0]);		// Select Our Font Texture
	for (loop=0; loop<128*NUMBMAPFONTS; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx,1-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1-cy);			// Texture Coord (Top Right)
				glVertex2i(16,16);						// Vertex Coord (Top Right)
				glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
				glVertex2i(0,16);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(10,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
	
	//make outline fonts
	HFONT	font;												// Windows Font ID
	base = glGenLists(256);
	/*
	for (loop=NUMBMAPFONTS; loop<NUMBMAPFONTS+NUMOUTFONTS; loop++)						// Loop Through All 256 Lists
	{
		currentFont = static_cast<fonts>(loop);
		switch(currentFont)
		{
			case ARIAL:
				//fontName = new char[6];
				fontName = "Arial";
				break;
			default:
				fontName = '\0';
				break;
		}
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
							fontName.c_str());								// Font Name
		
		//HDC hDC = window->hDC;
		SelectObject(*hDC, font);									// Selects The Font We Created

		wglUseFontOutlines(	*hDC,									// Select The Current DC
							128*loop,								// Starting Character
							128*(loop+1),									// Number Of Display Lists To Build
							base,									// Starting Display Lists
							0.0f,									// Deviation From The True Outlines
							0.05f,									// Font Thickness In The Z Direction
							WGL_FONT_POLYGONS,						// Use Polygons, Not Lines
							gmf);									// Address Of Buffer To Recieve Data
	}*/

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
						255,									// Number Of Display Lists To Build
						base,									// Starting Display Lists
						0.0f,									// Deviation From The True Outlines
						0.05f,									// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,						// Use Polygons, Not Lines
						gmf);									// Address Of Buffer To Recieve Data
}
#endif

GLvoid KillFont()									// Delete The Font From Memory
{
	glDeleteLists(base,128*NUMFONTS);							// Delete All 256 Display Lists
	delete gmf;
}


GLvoid glPrint(GLint x, GLint y, char *string, int set)	// Where The Printing Happens
{
	if (set>1)
	{
		set=1;
	}
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fontTexture[0]);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,640,0,480,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(x,y,1);								// Position The Text (0,0 - Bottom Left)
	glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_TEXTURE_2D);
	if(light)
		glEnable(GL_LIGHTING);
}

GLvoid glPrintHead(GLint x, GLint y, const char *string, fonts ft, int fontSize)	// Where The Printing Happens
{
	GLfloat fontScale = 10.0f*fontSize/12;
	int fontInt = static_cast<int>(ft);
	
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
	//glListBase(base+fontInt*128);
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

GLvoid glPrintHead(GLint x, GLint y, int num, fonts ft, int fontSize)
{
	char numtext[100];

	sprintf(numtext, "%i", num);		//convert int to chars
	glPrintHead(x, y, numtext, ft, fontSize);
}

GLvoid glPrintHead(GLint x, GLint y, GLfloat num, fonts ft, int fontSize)
{
	char numtext[100];
	sprintf(numtext, "%f", num);		//convert int to chars
	glPrintHead(x, y, numtext, ft, fontSize);
}







