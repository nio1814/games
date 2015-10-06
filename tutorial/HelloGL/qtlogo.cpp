#include "qtlogo.h"

void Patch::addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n)
{
	QVector3D norm = n.isNull() ? QVector3D::normal(a,b,c) : n;

	geom->appendFaceted(a, norm);
	geom->appendFaceted(b, norm);
	geom->appendFaceted(c, norm);

	count += 3;

	return;
}

void Patch::addQuad(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d)
{
	QVector3D norm = QVector3D::normal(a,b,c);
	addTri(a,b,c, norm);
	int k = geom->vertices.count();
	count += 3;

	return;
}

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

RectTorus::RectTorus(Geometry *g, qreal iRad, qreal oRad, qreal depth, int numSections)
{
	QVector<QVector3D> inside;
	QVector<QVector3D> outside;

	Patch* front = new Patch(g);

	for(int i=0; i<numSections; i++)
	{
		front->addQuad(outside[i], inside[i], inside[(i+1)%numSections], outside[(i+1)%numSections]);
	}

	parts << front;
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
