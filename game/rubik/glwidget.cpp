#include "glwidget.h"

#include "camera.h"
#include "keys.h"
#include "constants.h"

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
        : QOpenGLWidget(parent)
#else
	   : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
		m_twisting(false), m_timer(NULL)
#endif
{
	fovAngle = Vector2D(0.0f,45.0f);
	cam = new CameraPoint(Vector3D(0.0f,0.0f,6.0f),Vector3D(0,0,0),Y,6.0f);
	m_timer = new QTimer;

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

	/*light.pos = Vector3D(rand()*3.0f/RAND_MAX+2,rand()*3.0f/RAND_MAX+2,rand()*3.0f/RAND_MAX+2);
	light.ambient = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	light.diffuse = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);
	light.specular = Vector3D(rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX,rand()*1.0f/RAND_MAX);*/
	/*light.ambient = Vector3D(.10f,.10f,.10f);
	light.diffuse = Vector3D(1,1,1);
	light.specular = Vector3D(1,1,1);*/


	GLfloat LightAmbient[]=		{ 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ 5.0f, 5.0f, 6.0f, 1.0f };

	//glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

//	SetCursorPos(m_windowSizeX/2, m_windowSizeY/2);
}

GLWidget::~GLWidget()
{
	delete cam;
}

void GLWidget::initializeGL()
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

	lightActive = false;

	return;
}

void GLWidget::resizeGL(int w, int h)
{
	if (h==0)										// Prevent A Divide By Zero By
		h=1;										// Making Height Equal One

	m_windowSizeX = w;
	m_windowSizeY = h;

	glViewport(0,0,w,h);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
										// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
//	gluPerspective(fovAngle.y,(GLfloat)w/(GLfloat)h,clipClose,clipFar);
	fovAngle.x = (GLfloat)w/(GLfloat)h*fovAngle.y;
	glPerspective(fovAngle.y, (GLfloat)w/(GLfloat)h, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	if(lightActive)
	{
		glEnable(GL_LIGHTING);
//		light.enable();
	}
	else
		glDisable(GL_LIGHTING);

	runControls();
//	gluLookAt(cam->pos.x, cam->pos.y+.001f, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x,cam->up.y,cam->up.z);
	glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());

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

	rcube.drawCube();

	glColor3ub(255, 255, 205);		// Set Color To White
	glPushMatrix();
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex3f(.9f*cam->pos.x, .9f*cam->pos.y, .9f*cam->pos.z); // origin of the line
		glVertex3f(moslook.x,moslook.y , moslook.z); // ending point of the line
	glEnd( );

	glPopMatrix();

	rcube.updateCube();

	/*if(!rcube.isRotating)
		tan++;*/
}

void GLWidget::animate()
{
	if(!rcube.isRotating)
		disconnect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));

	updateGL();

	return;
}

int GLWidget::runControls()
{
	Vector3D cam2look = cam->cam2look();
	Vector3D toSideDir = cam->dir2RSide();
	Vector3D look2cam = -cam2look;
	Vector3D camposOld;
	Vector3D mouseMove;

	/*if(isBtnsM(mbRBTN, &mos))
	{
		if(mos.y != mos.yOld)
		{
			look2cam = look2cam->rotate3D(&toSideDir,(mos.yOld-mos.y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			cam->up = cam->up.rotate3D(&toSideDir,(mos.yOld-mos.y)*DEFMOUSETHROTTLEY*CAMOVESPEED);
			camposOld = cam->pos;
			cam->pos = cam->look + look2cam;
		}
		cam2look = cam->cam2look();
		toSideDir = cam->dir2RSide();
		if(mos.x != mos.xOld)
		{
			look2cam = look2cam->rotate3D(&cam->up,-(mos.x-mos.xOld)*DEFMOUSETHROTTLEX*1.3f*CAMOVESPEED);
			camposOld = cam->pos;
			cam->pos = cam->look + look2cam;
		}
	}
	if(isBtnsM(mbLBTN, &mos))
	{
		mouseMove = Vector3D(mos.x-mos.xOld, mos.yOld-mos.y, 0);	//find movement in screen coords
		GLfloat len = mouseMove.length();
		if(mouseMove.length() > 2.0f)
		{
			mouseMove.unitize();
			mouseMove = cam->up*mouseMove.y + cam->dir2RSide()*mouseMove.x;
			rcube.twistCube(cam->pos, moslook, mouseMove);
		}
	}*/
	static GLfloat origFollowDist = cam->followDist;
//	cam->followDist = origFollowDist*exp(-mos.wheel*.07f);
	cam->pos = cam->look + look2cam.unit()*cam->followDist;

	Vector2D screenDimGL;
	screenDimGL.x = 2*cam->followDist*tan(fovAngle.x*DEG2RAD/2.0f);
	screenDimGL.y = 2*cam->followDist*tan(fovAngle.y*DEG2RAD/2.0f);

//	mousePtInSpace.x = ((mos.x-m_windowSizeX/2)/(float)m_windowSizeX)*screenDimGL.x;
//	mousePtInSpace.y = ((m_windowSizeY/2-mos.y)/(float)m_windowSizeY)*screenDimGL.y;
//	moslook = cam->dir2RSide()*mousePtInSpace.x+cam->up*mousePtInSpace.y;



	return 0;
}

void GLWidget::rotateLR(GLfloat angle)
{
	Vector3D look2cam = -cam->cam2look();

	look2cam = look2cam.rotate3D(&cam->up,-angle);
//	camposOld = cam->pos;
	cam->pos = cam->look + look2cam;

	emit animate();
}

void GLWidget::rotateUD(GLfloat angle)
{
	Vector3D look2cam = -cam->cam2look();
	Vector3D toSideDir = cam->dir2RSide();

	look2cam = look2cam.rotate3D(&toSideDir, angle);
	cam->up = cam->up.rotate3D(&toSideDir, angle);
//	camposOld = cam->pos;
	cam->pos = cam->look + look2cam;

	emit animate();
}

void GLWidget::runKeys()
{
	bool wasRotating = rcube.isRotating;

	GLfloat rotateAngle = 5;
	if(isKeys(Qt::Key_Left))
		rotateLR(-rotateAngle);
	else if(isKeys(Qt::Key_Right))
		rotateLR(rotateAngle);

	if(isKeys(Qt::Key_Up))
		rotateUD(-rotateAngle);
	else if(isKeys(Qt::Key_Down))
		rotateUD(rotateAngle);

	if(canToggle(Qt::Key_L))
		lightActive = !lightActive;
	if(canToggle(Qt::Key_P))
		int pause = 5;

	if(!rcube.isRotating)
	{
		if(canToggle(Qt::Key_Y))
			rcube.rotateCube(cam->up, 2, 1);
		else if(canToggle(Qt::Key_W))
			rcube.rotateCube(cam->up, 2, -1);
		else if(canToggle(Qt::Key_G))
			rcube.rotateCube(cam->up, 1, 1);
		else if(canToggle(Qt::Key_D))
			rcube.rotateCube(cam->up, 1, -1);
		else if(canToggle(Qt::Key_N))
			rcube.rotateCube(cam->up, 0, 1);
		else if(canToggle(Qt::Key_X))
			rcube.rotateCube(cam->up, 0, -1);
		else if(canToggle(Qt::Key_T))
			rcube.rotateCube(cam->dir2RSide(), 2, -1);
	}

	if(!wasRotating && rcube.isRotating)
	{
		connect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));
		m_timer->start(30);
	}

//	emit animate();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	keyDown(event->key());

//	if(m_timer.isNull())
//	{
//		m_timer = new QTimer;
//		connect(m_timer, SIGNAL(timeout()), this, SLOT(runKeys()));
//		m_timer->start(50);
//	}
	emit runKeys();

	return;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	keyUp(event->key());
//	delete m_timer;

	return;
}
