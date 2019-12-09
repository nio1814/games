#ifndef COLLECTION_H
#define COLLECTION_H

#include "spheres.h"
#include "planes.h"
#include "lines.h"

class object_holder
{
  public:
    Vector3D majorAxis;
    int numObjects;
    int numShape[NUMSHAPES];

    object_holder();
    ~object_holder();
    object_sphere* addSpheres(int numObjs, float mass, float radius, Vector3D basePos, Vector3D offsetDir);
    object_sphere* addSpheres(float mass, float radius, Vector3D basePos);
    void addPlane(const Plane& plne);
    Plane* addPlanes(int numObjs, float mass, float wid, float len, float ph, float th, Vector3D basePos, Vector3D offDir=Vector3D(0,0,1), float distBetween=0);
    Plane* addPlanes(float mass, float wid, float len, float ph, float th, Vector3D basePos);
    Line* addLines(int numObjs, float mass, Vector3D v1, Vector3D v2, float cmf, Vector3D offsetDir=Z, float offsetDist=0.0f);
    void setMass(Shape objType, int index, float mass);
    void setElas(Shape objType, int index, float el);
    void setPos(Shape objType, int index, Vector3D pos);
    void setVel(Shape objType, int index, Vector3D vel);
    void setForce(Shape objType, int index, Vector3D force);
    void setNormal(Shape objType, int index, Vector3D norm);
    void flipBase(Shape objType, int index);
    void setTexture(Shape objType, int index, texture_s* txr);
    void setColor(Shape objType, int index, const Vector3D& color);
    NodeClass<void*>* makeTree();

    object_sphere* getSphere(int index) const;
    Plane* getPlane(int index) const;
    Line* getLine(int index) const;

    void run(GLfloat dt);
    void draw();

  //private:
//		QList<QPointer<Object> > objects;
    object_spheres spheres;
//		QList<QPointer<object_sphere> > spheres;
    object_planes planes;
    object_lines lines;
    //object_boxes* boxes;
    pointerTree* tree;

    matrix2D3 m_basis;
};

struct objP							//pointer to an object
{
  int index;
  Shape shape;
  const object_holder* holder;
};

bool isSame(objP p1, objP p2);

#endif // COLLECTION_H
