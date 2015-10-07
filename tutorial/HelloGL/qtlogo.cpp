#include "qtlogo.h"

static inline void qSetColor(float colorVec[], QColor c)
{
	colorVec[0] = c.redF();
	colorVec[1] = c.greenF();
	colorVec[2] = c.blueF();
	colorVec[3] = c.alphaF();

	return;
}

void Geometry::appendFaceted(const QVector3D &a, const QVector3D& n)
{
	int v = vertices.count();
	vertices.append(a);
	normals.append(n);
	faces.append(v);

	return;
}

void Geometry::appendSmooth(const QVector3D &a, const QVector3D &n, int from)
{
	int v = vertices.count() - 1;
	for(; v>=from; v--)
	{
		if(qFuzzyCompare(vertices[v], a))
			break;
	}
	if(v<from)
	{
		v = vertices.count();
		vertices.append(a);
		normals.append(n);
	}
	else
	{
		normals[v] += n;
	}

	faces.append(v);

	return;
}

void Geometry::loadArrays()
{
	glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
	glNormalPointer(GL_FLOAT, 0, normals.constData());

	return;
}

void Geometry::finalize()
{
	for(int i=0; i<normals.count(); i++)
	{
		normals[i].normalize();
	}

	return;
}

Patch::Patch(Geometry* geo)
	: start(geo->faces.count()), count(0), geom(geo)
{
	qSetColor(faceColor, QColor(Qt::darkGray));
}

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
	geom->appendSmooth(a, norm, k);
	geom->appendSmooth(c, norm, k);
	geom->appendFaceted(d, norm);

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

	for(int i=0; i<numSections; i++)
	{
		qreal angle = (i*2*M_PI)/numSections;
		inside << QVector3D(iRad*qSin(angle), iRad*qCos(angle), depth/2.0);
		outside << QVector3D(oRad*qSin(angle), oRad*qCos(angle), depth/2.0);
	}

	Patch* front = new Patch(g);

	for(int i=0; i<numSections; i++)
	{
		front->addQuad(outside[i], inside[i], inside[(i+1)%numSections], outside[(i+1)%numSections]);
	}

	parts << front;
}

QtLogo::QtLogo(QObject *parent, int d, qreal s) : QObject(parent), geom(new Geometry())
{
	buildGeometry(d, s);
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
	geom->loadArrays();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    for(int i=0; i<parts.count(); i++)
        parts[i]->draw();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    return;
}
