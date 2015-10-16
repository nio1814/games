#include "glwidget.h"

#include <qimage.h>

GLWidget::GLWidget(QWidget* parent, QGLWidget* shareWidget)
    : QGLWidget(parent, shareWidget), xRot(0), yRot(0), zRot(0), zPos(-1), scale(16)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::makeObject()
{
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    GLfloat s = .2f;
    for (int i=0; i<6; i++)
    {
	    QImage image = QImage(QString(":images/side%1.tga").arg(i+1),"TGA");
	   textures[i] = bindTexture(QImage(QString(":images/side%1.png").arg(i+1)), GL_TEXTURE_2D);
//        textures[i] = bindTexture(QPixmap(QString(":images/side%1.png").arg(i+1)), GL_TEXTURE_2D);
        for (int j=0; j<4; j++)
        {
            texCoords.append(QVector2D(j==0 || j==3, j<2));
            vertices.append(s*QVector3D(coords[i][j][0], coords[i][j][1], coords[i][j][2]));
        }
    }

    return;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}

void GLWidget::initializeGL()
{
    makeObject();

    qglClearColor(Qt::blue);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
//	glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return;
}

void GLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width-side)/2, (height-side)/2, side,side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-.5, .5, .5, -.5, 4, 15);
	m_projection.setToIdentity();
	GLfloat aspect = width/height;
	m_projection.perspective(60, aspect, .3, 1000);
    glMultMatrixf(m_projection.constData());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glDepthMask(GL_FALSE);

    m_view.setToIdentity();
    m_view.lookAt(QVector3D(0,0,zPos), QVector3D(0,0,0), QVector3D(0,1,0));
    glMultMatrixf(m_view.constData());

    glPushMatrix();
//    glOrtho(-.5, .5, .5, -.5, zPos+14, zPos+25);
//    glTranslatef(0,0,-10);

    glRotatef(xRot/scale, 1, 0, 0);
    glRotatef(yRot/scale, 0, 1, 0);
    glRotatef(zRot/scale, 0, 0, 1);

//    glColor3f(.05,.25,.1);
//    glColor4f(0,0,0,1);
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    for (int i=0; i<6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
	   glEnable(GL_TEXTURE_2D);
	   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);
	   glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;

    updateGL();

    return;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();

	return;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat rotateScale = .5*scale;
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
        rotateBy(rotateScale*dy, rotateScale*dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(rotateScale*dy, 0, rotateScale*dx);
    }

	lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    return;
}

//bool GLWidget::event(QEvent *event)
//{
//    switch(event->type())
//    {
//        case QEvent::TouchBegin:
//            QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
//            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
//    }
//}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	zPos += event->delta()/400.0;

	updateGL();

	return;
}
