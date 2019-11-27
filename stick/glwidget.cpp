#include "glwidget.h"

#include "qtgl.h"
#include "simulation.h"
#include "object/sphere.h"
#include "object/line.h"
#include "object/plane.h"

#include <QTimer>
#include <QDateTime>

GLWidget::GLWidget(QWidget *parent)
#if (QT_VERSION >= 0x050500)
        : QOpenGLWidget(parent)
#else
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
#endif
{
    sim = new Simulation;

    const Vector3D gravity = Z * -2;

    Object::Pointer object = sim->allObj.addObject(std::make_shared<object_line>(1.0f,Vector3D(0,2,3), Vector3D(0,0,5), .5f));
    object->setGravity(gravity);
    object->mass->pos = Vector3D();
//    sim->allObj.addLines(1, 1.0f,Vector3D(0,2,3), Vector3D(0,0,5), .5f);
//    sim->allObj.addSpheres(1,1,Vector3D(0,0,5));
    object = sim->allObj.addObject(std::make_shared<object_sphere>(1, 1, Vector3D(0,0,5)));
    object->mass->elas = .5;
    object->setGravity(gravity);
//    sim->cameraFollowObject = object;
//    sim->allObj.spheres.objs[0]->mass->elas = .5f;
//	sim->allObj.addPlanes(1, 10, 11, 11, 0, 159, Vector3D(1,-3,2));
  sim->cameraFollowObject = sim->allObj.addObject(std::make_shared<object_plane>(10, 11, 11, 0, 159, Vector3D(1,-3,2)));
//	sim->allObj.addPlanes(1, 10, 10, 5, 0, 20, Vector3D(0,5,-5));
  sim->allObj.addObject(std::make_shared<object_plane>(10, 10, 5, 0, 20, Vector3D(0,5,-5)));
//	sim->allObj.addPlanes(1, 10, 10, 25, 0, 0, Vector3D(0,-6,-7));
  sim->allObj.addObject(std::make_shared<object_plane>(10, 10, 25, 0, 0, Vector3D(0,-6,-7)));
	sim->cameras->addPoint(Vector3D(20, 0, 0), Vector3D(0,-.5,2), Vector3D(0,0,1), 5.0f);
    sim->cameras->camview = CAMERAMODE;
//    sim->allObj.makeTree();
//    sim->allObj.tree->ID = "holder";

//    Vector3D test = Vector3D(1,1,1);
//    Vector3D testang = test.cart2angxyz();

//    Vector3D testin = Vector3D(1,0,0);
//    Vector3D test2 = testin.rotate3D(&Vector3D(1,1,0), 90);

//    joystick = new joystick_s;
    bGravityOn = true;
    gravityON = true;
}

GLWidget::~GLWidget()
{
    delete sim;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1000, 800);
}

void GLWidget::initializeGL()
{
    glEnable(GL_BLEND);									// Enable Blending       (disable alpha testing)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Enable Alpha Blending (disable alpha testing)

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);							// Enables Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Test To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations

    GLfloat LightAmb[] = {0.50f, 0.50f, 0.50f, .60f};	// Ambient Light
    GLfloat LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};		// Diffuse Light
    GLfloat LightPos[] = {2.0f, 2.0f, 3.0f, 1.0f};		// Light Position

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set The Ambient Lighting For Light0
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set The Diffuse Lighting For Light0
    glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set The Position For Light0

    glEnable(GL_LIGHT1);								// Enable Light One
    glEnable(GL_LIGHTING);								// Enable Lighting
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glDisable(GL_TEXTURE_2D);

    return;
}

void GLWidget::resizeGL(int w, int h)
{
    h = qMax(1,h);

    glViewport (0, 0, (GLsizei)(w), (GLsizei)(h));				// Reset The Current Viewport
    glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
    glLoadIdentity ();													// Reset The Projection Matrix
    glPerspective (45.0f, (GLfloat)(w)/(GLfloat)(h),			// Calculate The Aspect Ratio Of The Window
                    1.0f, 100.0f);

    glMatrixMode (GL_MODELVIEW);				// Select The Modelview Matrix
    glLoadIdentity ();							// Reset The Modelview Matrix

	return;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    sim->draw();

    return;
}

void GLWidget::animate()
{
//    int dt = qobject_cast<QTimer*>(sender())->interval();
    const qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    const qint64 timeDelta = this->previousRunTime > 0 ? std::min((int)(currentTime - this->previousRunTime), 100) : 0;

    sim->run(timeDelta * 1e-3);
    this->previousRunTime = currentTime;

    update();

    return;
}
