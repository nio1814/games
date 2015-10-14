/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
#include <cstdlib> 

#include <mouse.h>
#include <camera.h>
#include <constants.h>
#include <light.h>
#include <keys.h>

#include "shape.h"

GLfloat LightAmbient[]=		{ 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 5.0f, 5.0f, 6.0f, 1.0f };

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

int WindowSizeX = 640;
int WindowSizeY = 480;
Vector2D windowSize;
Vector2D fovAngle = Vector2D(0.0f,45.0f);
GLfloat clipClose = 0.01f;
GLfloat clipFar = 100.0f;
Vector2D screenDimGL;
Vector2D mousePtInSpace;

cube_c cube(CORNER, YELLOW, WHITE, RED, ORANGE, GREEN, BLUE);				//cube object for testing
rcube_c rcube;
mouse_s mos(WindowSizeX,WindowSizeY);
Vector3D majAxis = Y;
CameraPoint cam(Vector3D(0.0f,0.0f,6.0f),Vector3D(0,0,0),majAxis,6.0f);
Vector3D moslook;

//light_c light(0, Vector3D(rand(),3,-6), Vector;
light_c light;
bool blight;

#define CAMOVESPEED 2.0f

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(fovAngle.y,(GLfloat)width/(GLfloat)height,clipClose,clipFar);
	fovAngle.x = (GLfloat)width/(GLfloat)height*fovAngle.y;

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void initialize()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				//rcube.cubes[i][j][k] = cube_c(CORNER, static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1), static_cast<color>((rand()%6)+1));
				rcube.cubes[i][j][k] = cube_c(CORNER, YELLOW, WHITE, RED, ORANGE, GREEN, BLUE);
			}
		}
	}
	
	light.pos = Vector3D(rand()*3.0f/RAND_MAX+2,rand()*3.0f/RAND_MAX+2,rand()*3.0f/RAND_MAX+2);
	light.ambient = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	light.diffuse = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	light.specular = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	/*light.ambient = Vector3D(.10f,.10f,.10f);
	light.diffuse = Vector3D(1,1,1);
	light.specular = Vector3D(1,1,1);*/
	
	
	//glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	
	SetCursorPos(WindowSizeX/2, WindowSizeY/2);
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.2f, 0.2f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	
	blight = false;
	
	return TRUE;										// Initialization Went OK
}

int runControls()
{
	Vector3D cam2look = cam.cam2look();
	Vector3D toSideDir = cam.dir2RSide();
	Vector3D look2cam = -cam2look;
	Vector3D camposOld;
	Vector3D mouseMove;
		
	if(isBtnsM(mbRBTN, &mos))
	{
		if(mos.y != mos.yOld)
		{
			look2cam = look2cam.rotate3D(&toSideDir,(mos.yOld-mos.y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			cam.up = cam.up.rotate3D(&toSideDir,(mos.yOld-mos.y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			camposOld = cam.pos;
			cam.pos = cam.look + look2cam;
		}
		cam2look = cam.cam2look();
		toSideDir = cam.dir2RSide();
		if(mos.x != mos.xOld)
		{
			look2cam = look2cam.rotate3D(&cam.up,-(mos.x-mos.xOld)*DEFMOUSETHROTTLEX*1.3f*CAMOVESPEED);
			camposOld = cam.pos;
			cam.pos = cam.look + look2cam;
		}
	}
	if(isBtnsM(mbLBTN, &mos))
	{
		mouseMove = Vector3D(mos.x-mos.xOld, mos.yOld-mos.y, 0);	//find movement in screen coords
		GLfloat len = mouseMove.length();
		if(mouseMove.length() > 2.0f)
		{
			mouseMove.unitize();
			mouseMove = cam.up*mouseMove.y + cam.dir2RSide()*mouseMove.x;
			rcube.twistCube(cam.pos, moslook, mouseMove);
		}
	}
	static GLfloat origFollowDist = cam.followDist;
	cam.followDist = origFollowDist*exp(-mos.wheel*.07f);
	cam.pos = cam.look + look2cam.unit()*cam.followDist;

	screenDimGL.x = 2*cam.followDist*tan(fovAngle.x*DEG2RAD/2.0f);
	screenDimGL.y = 2*cam.followDist*tan(fovAngle.y*DEG2RAD/2.0f);

	mousePtInSpace.x = ((mos.x-WindowSizeX/2)/(float)WindowSizeX)*screenDimGL.x;
	mousePtInSpace.y = ((WindowSizeY/2-mos.y)/(float)WindowSizeY)*screenDimGL.y;
	moslook = cam.dir2RSide()*mousePtInSpace.x+cam.up*mousePtInSpace.y;
	
	if(canToggle('L'))
		blight = !blight;
	if(canToggle('P'))	
		int pause = 5;

	return 0;
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	if(blight)
	{
		glEnable(GL_LIGHTING);
		light.enable();
	}
	else
		glDisable(GL_LIGHTING);
	
	runControls();
	gluLookAt(cam.pos.x, cam.pos.y+.001f, cam.pos.z, cam.look.x, cam.look.y, cam.look.z, cam.up.x,cam.up.y,cam.up.z);
	
	static int tan = 0;
	/*switch(tan)
	{
	case 0:
		rcube.rotateCube('Y', 0, 1);
		break;
	case 1:
		rcube.rotateCube('X', 1, -1);
		break;
	case 2:
		rcube.rotateCube('Z', 2, 1);
		break;
	case 3:
		//rcube.rotateCube('Y', 2, -1);
		break;
	case 4:
		rcube.rotateCube('X', 2, 1);
		break;
	default:
		break;
	}*/
	
	//rcube.drawCube();
	
	glColor3ub(255, 255, 205);		// Set Color To White
	glPushMatrix();
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex3f(.9f*cam.pos.x, .9f*cam.pos.y, .9f*cam.pos.z); // origin of the line
		glVertex3f(moslook.x,moslook.y , moslook.z); // ending point of the line
	glEnd( );
	

	glPopMatrix();
	
	rcube.updateCube();
	
	/*if(!rcube.isRotating)
		tan++;*/
	
	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

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

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	int wheeltemp;
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
			// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
			// A NonZero Value Indicates The Window Is Minimized.
			if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		
		case WM_LBUTTONDOWN:								// If the left mouse button was clicked
			btnDownM(mbLBTN,&mos);
			break;
		
		case WM_LBUTTONUP:								// If the left mouse button was clicked
			btnUpM(mbLBTN,&mos);
			break;
		
		case WM_RBUTTONDOWN:								// If the right mouse button was clicked.
			btnDownM(mbRBTN,&mos);

			break;
		
		case WM_RBUTTONUP:								// If the left mouse button was clicked
			btnUpM(mbRBTN,&mos);
			break;
		
		case WM_MOUSEMOVE:
			GetCursorPos(&mos.msPoint);
			updatePosM(mos.msPoint.x-2,mos.msPoint.y-36,&mos);
			break;

		case WM_MOUSEWHEEL:
			wheeltemp = (int)wParam;
			mos.wheelOld = mos.wheel;
			if(wheeltemp>0)
				mos.wheel++;
			else if(wheeltemp<0)
				mos.wheel--;
			break;
		
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keyDown(wParam);
			//keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keyUp(wParam);
			//keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	initialize();				//function to initialize objects

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Tan and Okai's Rubik's Cube",WindowSizeX,WindowSizeY,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || isKeys(VK_ESCAPE))	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if(canToggle(VK_F1))						// Is F1 Being Pressed?
			{
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Tan and Okai's Rubik's Cube",WindowSizeX,WindowSizeY,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
