#ifndef QTLOGO_H
#define QTLOGO_H

#include <QObject>
#include <qmatrix4x4.h>
#include <QtOpenGL>

struct Geometry
{
	void appendFaceted(const QVector3D &a, const QVector3D& n);
	void appendSmooth(const QVector3D &a, const QVector3D& n, int from);

	void finalize();
	void loadArrays();

    QVector<GLushort> faces;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;

};

class Patch
{
public:
	enum Smoothing {Faceted, Smooth};
    Patch(Geometry* geo);

    void draw() const;
    void addTri(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D &n);
    void addQuad(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D &d);
    void translate(const QVector3D& t);
    void rotate(qreal deg, QVector3D axis);

    GLushort start;
    GLushort count;
    QMatrix4x4 mat;
    Geometry* geom;
    GLfloat faceColor[4];
};

class Rectoid
{
public:
    void translate(const QVector3D &t)
    {
        for(int i=0; i<parts.count(); i++)
            parts[i]->translate(t);
        return;
    }

    void rotate(qreal deg, QVector3D axis)
    {
        for(int i=0; i<parts.count(); i++)
            parts[i]->rotate(deg, axis);
    }

    QList<Patch*> parts;
};

class RectTorus : public Rectoid
{
public:
    RectTorus(Geometry* g, qreal iRad, qreal oRad, qreal depth, int numSections);
};

class QtLogo : public QObject
{
    Q_OBJECT
public:
    QtLogo(QObject *parent = 0, int d=64, qreal s=1.0);
    ~QtLogo();
    void draw() const;
private:
    void buildGeometry(int divisions, qreal scale);
    QList<Patch*> parts;
    Geometry* geom;
signals:

public slots:
};

#endif // QTLOGO_H
