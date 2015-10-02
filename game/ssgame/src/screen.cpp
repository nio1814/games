#include<qglobal.h>

#ifdef Q_OS_WIN32
#include <windows.h>								// Header File For Windows
#include <gl\gl.h>								// Header File For The OpenGL32 Library
#include <gl\glu.h>
#elif defined(Q_OS_LINUX)
#include <GL/gl.h>
#endif

#include "screen.h"
//#include "TGA.h"
#include "masking.h"

GLuint healthTexture[1];
GLuint healthFrameTexture[1];

void initScreen()
{
	TGA_Texture(healthTexture, "Data/img/health.tga", 0);
	TGA_Texture(healthFrameTexture, "Data/img/healthFrame.tga", 0);

	return;
}

void printScreen(GLfloat healthPctg)
{
	int set = 1;

	//glBindTexture(GL_TEXTURE_2D, healthTexture[0]);			// Select Our Font Texture
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,640,0,480,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(5,450,0);								// Position The Text (0,0 - Bottom Left)
	//glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1)
	//glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	printHealth(healthPctg);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	if(light)
		glEnable(GL_LIGHTING);
	return;
}


void printHealth(GLfloat healthPctg)
{
	glBindTexture(GL_TEXTURE_2D, healthTexture[0]);				// Select A Texture Based On filter
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);						// Draw A Quad
		glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f,1.0f);glVertex2d(30.0 , 20.0);				// Top Left
		glTexCoord2f(1.0f,1.0f);glVertex2d(healthPctg*100 + 30, 20.0);				// Top Right
		glTexCoord2f(1.0f,0.0f);glVertex2d(healthPctg*100 + 30, 0.0);				// Bottom Right
		glTexCoord2f(0.0f,0.0f);glVertex2d(30.0 , 0.0);				// Bottom Left
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, healthFrameTexture[0]);				// Select A Texture Based On filter
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);						// Draw A Quad
		glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f,1.0f);glVertex2d(0.0 , 25.0);				// Top Left
		glTexCoord2f(1.0f,1.0f);glVertex2d(135 , 25.0);				// Top Right
		glTexCoord2f(1.0f,0.0f);glVertex2d(135 , -5.0);				// Bottom Right
		glTexCoord2f(0.0f,0.0f);glVertex2d(0.0 , -5.0);				// Bottom Left
	glEnd();
	glDisable(GL_TEXTURE_2D);

	return;
}
