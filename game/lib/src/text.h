#ifndef SCREENTEXT
#define SCREENTEXT

#define MAX_CHARS	256	
#define FONT_EXTRUDE	0.4f

extern GLuint fontTexture[1];

enum Fonts{DEFAULT, ARIAL, BMAP1, BMAP2};

struct font_s
{
	GLuint base;
	GLuint fontTexture[1];
	
	font_s()
	{
		base = 0;
		fontTexture[0] = 0;
	}
};

struct font3d_s
{
	UINT g_FontListID;
	HFONT hOldFont;
	GLYPHMETRICSFLOAT g_GlyphInfo[MAX_CHARS];
	
	font3d_s()
	{
		g_FontListID = 0;
	}
};
	
GLvoid BuildFont(HDC *hDC);											// Build Our Bitmap Font
GLvoid KillFont(GLvoid);											// Delete The Font
GLvoid glPrint(GLint x, GLint y, char *string, int set);				// Custom GL "Print" Routine
GLvoid glPrint(float x, float y, float z, const char *fmt, int fontSize, ...);	// Prints text in 3D space
GLvoid glPrintHead(GLint x, GLint y, const char *string, int fontSize);				// Prints stationary text
GLvoid glPrintHead(GLint x, GLint y, int num, int fontSize);
GLvoid glPrintHead(GLint x, GLint y, int num, Fonts ft, int fontSize);
GLvoid glPrintHead(GLint x, GLint y, GLfloat num, int fontSize);
GLvoid glPrintHead(GLint x, GLint y, const char *string, Fonts ft, int fontSize);				// Prints stationary text
UINT CreateOpenGL3DFont(HDC& hDC, LPSTR strFontName, float extrude, font3d_s* inFont);
void glDraw3DText(const char *strString, font3d_s* inFont, ...);
void DestroyFont(HDC &hDC, font_s* fontIn);

#endif
