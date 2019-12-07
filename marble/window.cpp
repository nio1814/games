#include "window.h"

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

#include "object/sphere.h"
#include <gameobject.h>
//#include <mass.h>
//#include "motion.h"
#include <constants.h>
#include <keys.h>
//#include "text.h"
#include <texture.h>

#include "commands.h"
#include "qtgl.h"
#include "levels.h"

#include <QKeyEvent>

//bool		keys[256];									// Array Used For The Keyboard Routine
bool		active=true;								// Window Active Flag Set To TRUE By Default
bool		fullscreen=true;							// Fullscreen Flag Set To Fullscreen Mode By Default

//object_holder allObjects;
//object_holder menu;

Plane* floors;
//object_sphere* ball = new object_sphere(1.0f, .35f);
//object_plane* floors = new object_plane(1,4,4,0);
//level level1;

// Light Parameters
static GLfloat LightAmb[] = {0.7f, 0.7f, 0.7f, 1.0f};	// Ambient Light
static GLfloat LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};	// Diffuse Light
static GLfloat LightPos[] = {4.0f, 4.0f, 6.0f, 1.0f};	// Light Position

//GLUquadricObj	*q;										// Quadratic For Drawing A Sphere

Vector2D WindowSize = Vector2D(1024, 768);
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

Window::Window(QWidget *parent) : GLWidget(parent)
{
	//game = new gameObj();
  mouse = new Mouse(WindowSize.x,WindowSize.y);
	initializeObjects();

	connect(this, SIGNAL(keyPressed()), this, SLOT(processKeyboard()));
}


void Window::initializeGL()										// All Setup For OpenGL Goes Here
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

void Window::initializeObjects()
{
//	nullTexture.ID = "null texture";

	//MAKE MENU

	//MAKE LEVEL1
	//level1.levelNum = 1;
	//level1.allObj = allObjects;
	//texture_s* balltxr = level1.addTexture("Data/Ball.bmp", "Data/EnvRoll.bmp", "ball");

	//numExtraSpheres = 0;
	//gravityON = false;
	//currentgravity = 0;

	this->game.addMenu("Marble Game");
    //game->addLevel(0);
//    game->addLevel(1);
//    game->addLevel(2);
	this->game.addLevel(createLevel1());

	//level1.allObj.spheres->objs[1].texture[1] = texture[1];
	//level1.allObj.spheres->objs[1].texture[2] = texture[2];
	//ball->numTextures = 2;
	//floors->texture[0] = texture[0];
	//level1.allObj.planes->objs[23].texture[0] = texture[0];

	bGravityOn = true;
	gravityDir = -Y;

//	ball = game->levels[game->currentLevel].ball;
  this->ball = std::dynamic_pointer_cast<object_sphere>(this->game.currentLevel()->player);
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

void Window::paintGL()									// Draw Everything
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
    this->game.render();

    return;
}

void Window::processKeyboard()							// Process Keyboard Results
{
	Vector3D forward, toleft;
//	forward = camToLook.unit();
  forward = (ball->pos - this->game.currentLevel()->cameras.current()->pos).unit();
	forward.y = 0;
	toleft = forward.rotate3D(Y, 90);
  std::shared_ptr<Level> level = game.currentLevel();
  std::shared_ptr<CameraPoint> camera = level->cameras.current();

    if (isKeys(Qt::Key_H))	yrotspeed += 0.08f;			// Right Arrow Pressed (Increase yrotspeed)
    if (isKeys(Qt::Key_K))		yrotspeed -= 0.08f;			// Left Arrow Pressed (Decrease yrotspeed)
    if (isKeys(Qt::Key_U))		xrotspeed += 0.08f;			// Down Arrow Pressed (Increase xrotspeed)
    if (isKeys(Qt::Key_J))		xrotspeed -= 0.08f;			// Up Arrow Pressed (Decrease xrotspeed)

  if (isKeys(Qt::Key_A))
    camera->pos += level->majorAxis * 0.05f;				// 'A' Key Pressed ... Zoom In
  if (isKeys(Qt::Key_Z))
    camera->pos -= level->majorAxis * 0.05f;				// 'Z' Key Pressed ... Zoom Out

    if (isKeys(Qt::Key_PageUp))		ballHeight +=0.03f;				// Page Up Key Pressed Move Ball Up
    if (isKeys(Qt::Key_PageDown))		ballHeight -=0.03f;				// Page Down Key Pressed Move Ball Down

	/*if (keys[VK_UP])		ball->moveForce -= Vector3D(0.0, 0.0, 2.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_DOWN])		ball->moveForce += Vector3D(0.0, 0.0, 2.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_LEFT])		ball->moveForce -= Vector3D(2.0, 0.0, 0.0);				// Page Down Key Pressed Move Ball Down
	if (keys[VK_RIGHT])		ball->moveForce += Vector3D(2.0, 0.0, 0.0);				// Page Down Key Pressed Move Ball Down
	*/
  if(this->ball->touching())
  {
      if (isKeys(Qt::Key_Up))
        ball->moveForce += forward;		// Page Down Key Pressed Move Ball Down
      if (isKeys(Qt::Key_Down))		ball->moveForce -= forward;		// Page Down Key Pressed Move Ball Down
      if (isKeys(Qt::Key_Left))		ball->moveForce += toleft;				// Page Down Key Pressed Move Ball Down
      if (isKeys(Qt::Key_Right))		ball->moveForce -= toleft;				// Page Down Key Pressed Move Ball Down

  }
  if (isKeys(Qt::Key_G))			ball->moveForce += Vector3D(0.0, 20.0, 0.0);			// Page Down Key Pressed Move Ball Down

	CameraView newView;
	if(isKeys(Qt::Key_C))
	{
    switch(this->game.currentLevel()->cameras.camview)
		{
			case FOLLOW:
				newView = LOCKED;
				break;
			case FIRST:
				newView = FOLLOW;
				break;
			case LOCKED:
				newView = FIRST;
				break;
		}
    this->game.currentLevel()->cameras.camview = newView;
	}
}

void Window::process()
{
    delta = qobject_cast<QTimer*>(sender())->interval();

	//camToLook = Vector3D(xLook-xCam, yLook-yCam, zLook-zCam);
//	DrawGLScene();						// Draw The Scene
	//ball->operate(delta, &allObjects);

	if(delta > MAXDELTA)
		delta = MAXDELTA;
	//game.levels[0].allObj.run(delta);
//	game->levels[0].allObj.run(.03);
    void (*commandFcn)(gameObj *, Mouse *) = nullptr;
    //commandFcn(game, mos);
    game.run(mouse, commandFcn, delta);

	processKeyboard();

  GLfloat zc = .01f*ball->vel.dot(Vector3D(0,0,1));
	zCam += zc;
	zLook += zc;
	gravityV = Vector3D(0,1,0)*currentgravity;


    update();

	return;
}


void Window::keyPressEvent(QKeyEvent *event)
{
	return keyDown(event->key());
//	emit keyPressed();

	return;
}

void Window::keyReleaseEvent(QKeyEvent *event)
{
	return keyUp(event->key());
}


void Window::mousePressEvent(QMouseEvent *event)
{
    mouse->btnDown(event->button());

    return;
}
