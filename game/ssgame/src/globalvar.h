#ifndef GLOBALVAR
#define GLOBALVAR

#include <qglobal.h>

#ifdef Q_OS_WIN32
//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#elif defined(Q_OS_LINUX)
#include <GL/gl.h>
#endif

extern bool pause;
extern bool	gameOver;

extern GLfloat THROTTLE;								//time throttle

#endif
