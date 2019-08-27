#ifndef STEXT
#define STEXT

#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include "qtgl.h"
//#include <gl\glu.h>
#include <string>

extern GLuint	base;							// Base Display List For The Font Set
extern GLfloat	cnt1;							// 1st Counter Used To Move Text & For Coloring
extern GLfloat	cnt2;							// 2nd Counter Used To Move Text & For Coloring

extern GLuint fontTexture[1];

enum fonts{BMAP1, BMAP2, DEFAULT, ARIAL};

//GLvoid BuildFont(HDC *hDC);									// Build Our Font Display List
GLvoid KillFont();						// Delete The Font List
GLvoid glPrint(GLint x, GLint y, char *string, int set);				// Custom GL "Print" Routine
GLvoid glPrintHead(GLint x, GLint y, const char *string, fonts ft, int fontSize);				// Prints stationary text
GLvoid glPrintHead(GLint x, GLint y, int num, fonts ft, int fontSize);
GLvoid glPrintHead(GLint x, GLint y, GLfloat num, fonts ft, int fontSize);

#endif
