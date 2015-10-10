#include "glwidget.h"

#include <qimage.h>

GLWidget::GLWidget(QWidget* parent, QGLWidget* shareWidget)
    : QGLWidget(parent, shareWidget), xRot(0), yRot(0), zRot(0), scale(16)
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
//        textures[i] = bindTexture(QImage(QString(":images/side%1.png").arg(i+1)), GL_TEXTURE_2D);
        textures[i] = bindTexture(QPixmap(QString(":images/side%1.png").arg(i+1)), GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(xRot/scale, 1, 0, 0);
    glRotatef(yRot/scale, 0, 1, 0);
    glRotatef(zRot/scale, 0, 0, 1);

    glColor3f(.05,.25,.1);
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    for (int i=0; i<6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);
    }

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
