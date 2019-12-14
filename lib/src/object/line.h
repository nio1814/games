#ifndef LINE_H
#define LINE_H

#include "object.h"
#include "quaternion.h"

class Line : public Object
{
public:
  float length, width;
  float centerOfMassFraction;												//com location(as fraction from v1 to v2)
  Quaternion orientation;

//	object_line();
//	object_line(float mass, Vector3D v1, Vector3D v2);			//input mass and 2 vertices
  Line(float mass=1, Vector3D v1=Vector3D(0,0,0), Vector3D v2=Z, float cmf=.5);			//input mass and 2 vertices and

  Vector3D vertex(const int index);
  Vector3D vector();
  Vector3D direction();
  virtual void draw();
  virtual void solve();									//gravitational force will be applied therefore we need a "solve" method.
  bool detectCollision(Object::Pointer object);
  bool detectCollision(std::shared_ptr<Line> line);
  void collide(Object::ConstPointer line);
  //virtual bool doCollisions(const object_holder *allObjs);
  virtual void* getProperty(int idx, dataType &shape);
  void addTouchedObject(Object::Pointer object, const int vertexIndex);
  Vector3D vertexVelocity(int vertexIndex);
  std::map<Object::ConstPointer, int> touchingVertexIndex;
private:
//  virtual void collide(const object_plane* plane, const Vector3D &contactPoint, const Vector3D &contactNormal);

  QList<Vector3D> contactPoints;
  QList<Vector3D> contactNormals;
};


#endif // LINE_H
