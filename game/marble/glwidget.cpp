#include "glwidget.h"

/*		This code has been created by Banu Octavian aka Choko - 20 may 2000
 *		and uses NeHe tutorials as a starting point (window initialization,
 *		texture loading, GL initialization and code for keypresses) - very good
 *		tutorials, Jeff. If anyone is interested about the presented algorithm
 *		please e-mail me at boct@romwest.ro
 *
 *		Code Commmenting And Clean Up By Jeff Molofee ( NeHe )
 *		NeHe Productions	...		http://nehe.gamedev.net
 */
//Version 4.3

#include <stdio.h>										// Header File For Standard Input / Output
#include <math.h>

#include <qtimer.h>

#include <object.h>
#include <gameobject.h>
//#include <mass.h>
//#include "motion.h"
#include <constants.h>
#include <keys.h>
//#include "text.h"
#include <texture.h>

#include "commands.h"

//bool		keys[256];									// Array Used For The Keyboard Routine
bool		active=true;								// Window Active Flag Set To TRUE By Default
bool		fullscreen=true;							// Fullscreen Flag Set To Fullscreen Mode By Default

//object_holder allObjects;
object_holder menu;

object_plane* floors;
//object_sphere* ball = new object_sphere(1.0f, .35f);
//object_plane* floors = new object_plane(1,4,4,0);
//level level1;

// Light Parameters
static GLfloat LightAmb[] = {0.7f, 0.7f, 0.7f, 1.0f};	// Ambient Light
static GLfloat LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};	// Diffuse Light
static GLfloat LightPos[] = {4.0f, 4.0f, 6.0f, 1.0f};	// Light Position

//GLUquadricObj	*q;										// Quadratic For Drawing A Sphere

Vector2D WindowSize = Vector2D(1024,768);
GLfloat		xrot		=  0.0f;						// X Rotation
GLfloat		yrot		=  0.0f;						// Y Rotation
GLfloat		xrotspeed	=  0.0f;						// X Rotation Speed
GLfloat		yrotspeed	=  0.0f;						// Y Rotation Speed
GLfloat		zoom		= -7.0f;						// Depth Into The Screen
GLfloat		ballHeight		=  2.0f;						// Height Of Ball From Floor

GLfloat xCam = 0.0f;
GLfloat yCam = 4.60f;
GLfloat zCam = 8.0f;
GLfloat xLook = 0.0f;
GLfloat yLook = 0.0f;
GLfloat zLook = 0.0f;
Vector3D camToLook;

GLfloat lastTime = 0.0f;
GLfloat currentTime = 0.0f;
GLfloat delta;

Vector3D gravityV;
GLfloat currentgravity = 9.8f;

//GLuint		texture[3];									// 3 Textures

//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void process();

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
        : QOpenGLWidget(parent)
#else
       : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
	game = new gameObj();
	mos = new Mouse(WindowSize.x,WindowSize.y);
	initializeObjects();
}

GLWidget::~GLWidget()
{
	delete game;
	delete mos;
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(40,30);
}

QSize GLWidget::sizeHint() const
{
	return QSize(400,300);
}

void GLWidget::resizeGL(GLsizei w, GLsizei h)		// Resize And Initialize The GL Window
{
    h = qMax(h,1);

    glViewport(0,0,w,h);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
    glPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


void GLWidget::initializeGL()										// All Setup For OpenGL Goes Here
{
	/*if (!LoadGLTextures())								// If Loading The Textures Failed
	{
		return FALSE;									// Return False
	}*/
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.5f, 1.0f, 1.0f);				// Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear The Stencil Buffer To 0
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);			// Set The Ambient Lighting For Light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);			// Set The Diffuse Lighting For Light0
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Set The Position For Light0

	glEnable(GL_LIGHT0);								// Enable Light 0
	glEnable(GL_LIGHTING);								// Enable Lighting

    /*q = gluNewQuadric();								// Create A New Quadratic
    gluQuadricNormals(q, GL_SMOOTH);					// Generate Smooth Normals For The Quad
    gluQuadricTexture(q, GL_TRUE);*/						// Enable Texture Coords For The Quad

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

//	BuildFont(&hDC);

    return;										// Initialization Went OK
}

void GLWidget::initializeObjects()
{
//	nullTexture.ID = "null texture";

	//MAKE MENU

	//MAKE LEVEL1
	//level1.levelNum = 1;
	//level1.allObj = allObjects;
    texture_s* tile1txr = game->addTexture(":Data/Envwall.bmp", "tile1");
	//texture_s* balltxr = level1.addTexture("Data/Ball.bmp", "Data/EnvRoll.bmp", "ball");
    texture_s* wall1txr = game->addTexture(":Data/wall.bmp", "wall");

	//numExtraSpheres = 0;
	//gravityON = false;
	//currentgravity = 0;

	game->addMenu("Marble Game");
    game->addLevel(0);
//    game->addLevel(1);
//    game->addLevel(2);


	//level1.allObj.spheres->objs[1].texture[1] = texture[1];
	//level1.allObj.spheres->objs[1].texture[2] = texture[2];
	//ball->numTextures = 2;
	//floors->texture[0] = texture[0];
	//level1.allObj.planes->objs[23].texture[0] = texture[0];

	bGravityOn = true;
	gravityDir = -Y;

//	ball = game->levels[game->currentLevel].ball;
    ball = game->currentLevel().ball;
	
	return;
}

void DrawObject()										// Draw Our Ball
{
	glColor3f(1.0f, 1.0f, 1.0f);						// Set Color To White
//	glBindTexture(GL_TEXTURE_2D, texture[1]);			// Select Texture 2 (1)
//	gluSphere(q, 0.35f, 32, 16);						// Draw First Sphere
	
//	glBindTexture(GL_TEXTURE_2D, texture[2]);			// Select Texture 3 (2)
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// Set Color To White With 40% Alpha
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set Blending Mode To Mix Based On SRC Alpha
	glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
	glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping

//	gluSphere(q, 0.35f, 32, 16);						// Draw Another Sphere Using New Texture
														// Textures Will Mix Creating A MultiTexture Effect (Reflection)
	glDisable(GL_TEXTURE_GEN_S);						// Disable Sphere Mapping
	glDisable(GL_TEXTURE_GEN_T);						// Disable Sphere Mapping
	glDisable(GL_BLEND);								// Disable Blending
}

void DrawFloor()										// Draws The Floor
{
	/*glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Texture 1 (0)
	glBegin(GL_QUADS);									// Begin Drawing A Quad
		glNormal3f(0.0, 1.0, 0.0);						// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f);					// Bottom Left Of Texture
		glVertex3f(-2.0, 0.0, 2.0);					// Bottom Left Corner Of Floor
		
		glTexCoord2f(0.0f, 0.0f);					// Top Left Of Texture
		glVertex3f(-2.0, 0.0,-2.0);					// Top Left Corner Of Floor
		
		glTexCoord2f(1.0f, 0.0f);					// Top Right Of Texture
		glVertex3f( 2.0, 0.0,-2.0);					// Top Right Corner Of Floor
		
		glTexCoord2f(1.0f, 1.0f);					// Bottom Right Of Texture
		glVertex3f( 2.0, 0.0, 2.0);					// Bottom Right Corner Of Floor
	glEnd();*/											// Done Drawing The Quad

	//floors->draw();

	glColor3f(0.0f, 0.0f, 1.0f);
	/*glTranslatef(ball.masses[0]->pos.x, ball.masses[0]->pos.y, ball.masses[0]->pos.z);
	gluSphere(ball.quad, 0.35f, 32, 16);						// Draw First Sphere
	glTranslatef(-ball.masses[0]->pos.x, -ball.masses[0]->pos.y, -ball.masses[0]->pos.z);*/
	//ball.draw();
}

void GLWidget::paintGL()									// Draw Everything
{
	// Clear Screen, Depth Buffer & Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
										// Reset The Modelview Matrix
	//yCam = zLook*cos(DEG2RAD*xrot);
	//gluLookAt(xCam, yCam, zCam, xLook, yLook, zLook, 0.0, 1.0, 0.0);
	//camToLook = game.levels[0].setCam(&ball->mass->pos);
	//glRotatef(xrot,1.0f,0.0f,0.0f);						// Rotate On The X Axis By xrot
	//glRotatef(yrot,0.0f,1.0f,0.0f);						// Rotate On The Y Axis By yrot
	
	//allObjects.draw();
	//game.levels[levelnum].run(1);
//	game->currentLevel = 2;
//	game.run(mos, runKeys);
	
	/*game.levels[levelnum].allObj.draw();

	// Clip Plane Equations
	double eqr[] = {0.0f,-1.0f, 0.0f, 0.0f};			// Plane Equation To Use For The Reflected Objects

	glColorMask(0,0,0,0);								// Set Color Mask
	glEnable(GL_STENCIL_TEST);							// Enable Stencil Buffer For "marking" The Floor
	glStencilFunc(GL_ALWAYS, 1, 1);						// Always Passes, 1 Bit Plane, 1 As Mask
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
														// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
														// Replace If Test Passes
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing

	//DrawFloor();										// Draw The Floor (Draws To The Stencil Buffer)
														// We Only Want To Mark It In The Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	glColorMask(1,1,1,1);								// Set Color Mask to TRUE, TRUE, TRUE, TRUE
	glStencilFunc(GL_EQUAL, 1, 1);						// We Draw Only Where The Stencil Is 1
														// (I.E. Where The Floor Was Drawn)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Don't Change The Stencil Buffer
	glEnable(GL_CLIP_PLANE0);							// Enable Clip Plane For Removing Artifacts
														// (When The Object Crosses The Floor)
	glClipPlane(GL_CLIP_PLANE0, eqr);					// Equation For Reflected Objects
	glPushMatrix();										// Push The Matrix Onto The Stack
		glScalef(1.0f, -1.0f, 1.0f);					// Mirror Y Axis
		glLightfv(GL_LIGHT0, GL_POSITION, LightPos);	// Set Up Light0
		//glTranslatef(0.0f, height, 0.0f);				// Position The Object
		glRotatef(xrot, 1.0f, 0.0f, 0.0f);				// Rotate Local Coordinate System On X Axis
		glRotatef(yrot, 0.0f, 1.0f, 0.0f);				// Rotate Local Coordinate System On Y Axis
		//DrawObject();									// Draw The Sphere (Reflection)
		//ball->draw();
//		allObjects.draw();
		game.levels[levelnum].allObj.draw();
	glPopMatrix();										// Pop The Matrix Off The Stack
	
	glDisable(GL_CLIP_PLANE0);							// Disable Clip Plane For Drawing The Floor
	glDisable(GL_STENCIL_TEST);							// We Don't Need The Stencil Buffer Any More (Disable)
	
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Set Up Light0 Position
	glEnable(GL_BLEND);									// Enable Blending (Otherwise The Reflected Object Wont Show)
	glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);					// Set Color To White With 80% Alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending Based On Source Alpha And 1 Minus Dest Alpha
	//DrawFloor();										// Draw The Floor To The Screen
	glEnable(GL_LIGHTING);								// Enable Lighting
//	allObjects.draw();
	//ball->draw();
game.levels[levelnum].allObj.draw();

	glDisable(GL_BLEND);								// Disable Blending
	glTranslatef(0.0f, height, 0.0f);					// Position The Ball At Proper Height
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Rotate On The X Axis
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Rotate On The Y Axis
	//DrawObject();										// Draw The Ball
	xrot += xrotspeed;									// Update X Rotation Angle By xrotspeed
	yrot += yrotspeed;									// Update Y Rotation Angle By yrotspeed
	glFlush();											// Flush The GL Pipeline
*/
    game->render();

    return;
}

void GLWidget::ProcessKeyboard()							// Process Keyboard Results
{
	Vector3D forward, toleft;
	forward = camToLook.unit();
	forward.y = 0;
	toleft = forward.rotate3D(Y, 90);

    if (isKeys(Qt::Key_H))	yrotspeed += 0.08f;			// Right Arrow Pressed (Increase yrotspeed)
    if (isKeys(Qt::Key_K))		yrotspeed -= 0.08f;			// Left Arrow Pressed (Decrease yrotspeed)
    if (isKeys(Qt::Key_U))		xrotspeed += 0.08f;			// Down Arrow Pressed (Increase xrotspeed)
    if (isKeys(Qt::Key_J))		xrotspeed -= 0.08f;			// Up Arrow Pressed (Decrease xrotspeed)

    if (isKeys(Qt::Key_A))			zCam +=0.05f;				// 'A' Key Pressed ... Zoom In
    if (isKeys(Qt::Key_Z))			zCam -=0.05f;				// 'Z' Key Pressed ... Zoom Out

    if (isKeys(Qt::Key_PageUp))		ballHeight +=0.03f;				// Page Up Key Pressed Move Ball Up
    if (isKeys(Qt::Key_PageDown))		ballHeight -=0.03f;				// Page Down Key Pressed Move Ball Down

	/*if (keys[VK_UP])		ball->moveForce -= Vector3D(0.0, 0.0, 2.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_DOWN])		ball->moveForce += Vector3D(0.0, 0.0, 2.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_LEFT])		ball->moveForce -= Vector3D(2.0, 0.0, 0.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_RIGHT])		ball->moveForce += Vector3D(2.0, 0.0, 0.0);				// Page Down Key Pressed Move Ball Down
	*/
    if (isKeys(Qt::Key_Up))		ball->moveForce += forward;		// Page Down Key Pressed Move Ball Down
    if (isKeys(Qt::Key_Down))		ball->moveForce -= forward;		// Page Down Key Pressed Move Ball Down
    if (isKeys(Qt::Key_Left))		ball->moveForce += toleft;				// Page Down Key Pressed Move Ball Down
    if (isKeys(Qt::Key_Right))		ball->moveForce -= toleft;				// Page Down Key Pressed Move Ball Down
    if (isKeys(Qt::Key_G))			ball->moveForce += Vector3D(0.0, 20.0, 0.0);			// Page Down Key Pressed Move Ball Down
}

void GLWidget::process()
{
    delta = qobject_cast<QTimer*>(sender())->interval();

	//camToLook = Vector3D(xLook-xCam, yLook-yCam, zLook-zCam);
//	DrawGLScene();						// Draw The Scene
	//ball->operate(delta, &allObjects);

	if(delta > MAXDELTA)
		delta = MAXDELTA;
	//game.levels[0].allObj.run(delta);
//	game->levels[0].allObj.run(.03);
    void (*commandFcn)(gameObj *, Mouse *);
    //commandFcn(game, mos);
    game->run(mos, commandFcn, delta);

	GLfloat zc = .01f*ball->mass->vel.dot(Vector3D(0,0,1));
	zCam += zc;
	zLook += zc;
	gravityV = Vector3D(0,1,0)*currentgravity;

    update();

	return;
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
	return keyDown(event->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	return keyUp(event->key());
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mos->btnDown(event->button());

    return;
}

/*GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}*/

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
/*BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;							// Holds The Results After Searching For A Match
	WNDCLASS	wc;										// Windows Class Structure
	DWORD		dwExStyle;								// Window Extended Style
	DWORD		dwStyle;								// Window Style

	fullscreen=fullscreenflag;							// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;							// No Extra Window Data
	wc.cbWndExtra		= 0;							// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;							// No Background Required For GL
	wc.lpszMenuName		= NULL;							// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";						// Set The Class Name

	if (!RegisterClass(&wc))							// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	
	if (fullscreen)										// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;						// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;		// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;			// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;						// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;							// Return FALSE
			}
		}
	}

	if (fullscreen)										// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;						// Window Extended Style
		dwStyle=WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ShowCursor(FALSE);								// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
	}

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
								"OpenGL",				// Class Name
								title,					// Window Title
								dwStyle,				// Window Style
								0, 0,					// Window Position
								width, height,			// Selected Width And Height
								NULL,					// No Parent Window
								NULL,					// No Menu
								hInstance,				// Instance
								NULL)))					// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		bits,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)  
		1,												// Use Stencil Buffer ( * Important * )
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))								// Did We Get A Device Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);							// Show The Window
	SetForegroundWindow(hWnd);							// Slightly Higher Priority
	SetFocus(hWnd);										// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);						// Set Up Our Perspective GL Screen

	if (!InitGL())										// Initialize Our Newly Created GL Window
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	return TRUE;										// Success
}


LRESULT CALLBACK WndProc(	HWND	hWnd,				// Handle For This Window
							UINT	uMsg,				// Message For This Window
							WPARAM	wParam,				// Additional Message Information
							LPARAM	lParam)				// Additional Message Information
{
	static bool g_bLighting;
	int xPos,yPos;

	switch (uMsg)										// Check For Windows Messages
	{
		case WM_ACTIVATE:								// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))						// Check Minimization State
			{
				active=TRUE;							// Program Is Active
			}
			else										// Otherwise
			{
				active=FALSE;							// Program Is No Longer Active
			}

			return 0;									// Return To The Message Loop
		}

		case WM_SYSCOMMAND:								// Intercept System Commands
		{
			switch (wParam)								// Check System Calls
			{
				case SC_SCREENSAVE:						// Screensaver Trying To Start?
				case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
				return 0;								// Prevent From Happening
			}
			break;										// Exit
		}

		case WM_CLOSE:									// Did We Receive A Close Message?
		{
			PostQuitMessage(0);							// Send A Quit Message
			return 0;									// Jump Back
		}

		case WM_KEYDOWN:								// Is A Key Being Held Down?
		{
			keyDown(wParam);						// If So, Mark It As TRUE
			return 0;									// Jump Back
		}

		case WM_KEYUP:									// Has A Key Been Released?
		{
			keyUp(wParam);						// If So, Mark It As FALSE
			return 0;									// Jump Back
		}

		case WM_LBUTTONDOWN:								// If the left mouse button was clicked
			btnDownM(mbLBTN,mos);
			break;
		
		case WM_LBUTTONUP:								// If the left mouse button was clicked
			btnUpM(mbLBTN,mos);
			break;
			
		case WM_RBUTTONDOWN:								// If the right mouse button was clicked.
			btnDownM(mbRBTN,mos);
			g_bLighting = !g_bLighting;						// Turn lighting ON/OFF

			if(g_bLighting) {								// If lighting is ON
				glEnable(GL_LIGHTING);						// Enable OpenGL lighting
			} else {
				glDisable(GL_LIGHTING);						// Disable OpenGL lighting
			}
			break;
			
		case WM_RBUTTONUP:								// If the left mouse button was clicked
			btnUpM(mbRBTN,mos);
			break;
			
		case WM_MOUSEMOVE:
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			GetCursorPos(&mos->msPoint);
			updatePosM(mos->msPoint.x,mos->msPoint.y,mos);
			
		case WM_SIZE:									// Resize The OpenGL Window
			{
				ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
				return 0;									// Jump Back
			}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);		// Return Unhandled Messages
}

int WINAPI WinMain(	HINSTANCE	hInstance,				// Instance
					HINSTANCE	hPrevInstance,			// Previous Instance
					LPSTR		lpCmdLine,				// Command Line Parameters
					int			nCmdShow)				// Window Show State
{
	MSG		msg;										// Windows Message Structure
	BOOL	done=FALSE;									// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;								// Windowed Mode
	}

	
	// Create Our OpenGL Window
	if (!CreateGLWindow("Banu Octavian & NeHe's Stencil & Reflection Tutorial", 1024, 768, 32, fullscreen))
	{
		return 0;										// Quit If Window Was Not Created
	}

	initializeObjects();

	currentTime = lastTime = GetTickCount() * 0.001f;
	while(!done)										// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))		// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)					// Have We Received A Quit Message?
			{
				done=TRUE;								// If So done=TRUE
			}
			else										// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);					// Translate The Message
				DispatchMessage(&msg);					// Dispatch The Message
			}
		}
		else											// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)									// Program Active?
			{
				if (isKeys(VK_ESCAPE))					// Was Escape Pressed?
				{
					done=TRUE;							// ESC Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					process();
					
					SwapBuffers(hDC);					// Swap Buffers (Double Buffering)

					//runKeys(&allObjects);
					//runKeys(&level1);
					//ProcessKeyboard();					// Processed Keyboard Presses
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}*/
