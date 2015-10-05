#include "qtlogo.h"


void Patch::draw() const
{
    glPushMatrix();
    const GLushort* indices = geom->faces.constData();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices+start);

    glPopMatrix();
}

void Patch::translate(const QVector3D &t)
{
    mat.translate(t);
    return;
}

void Patch::rotate(qreal deg, QVector3D axis)
{
    mat.rotate(deg, axis);
}

QtLogo::QtLogo(QObject *parent, int d, qreal s) : QObject(parent)
{

}

QtLogo::~QtLogo()
{

}

void QtLogo::buildGeometry(int divisions, qreal scale)
{
    RectTorus body(geom, .2, .3, .1, divisions);

    parts << body.parts;
}

void QtLogo::draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    for(int i=0; i<parts.count(); i++)
        parts[i]->draw();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    return;
}
