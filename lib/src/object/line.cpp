#include "line.h"

Line::Line(float mass, Vector3D v1, Vector3D v2, float cmf) :
  Object(Vector3D(), mass),
  centerOfMassFraction(cmf)
{
//	Object();
//	object_line();
  shape = LINE;
  width = 15;
    bMovable = true;
  this->momentOfInertia = this->mass * std::pow(length,2)/12.0f;
  const Vector3D vertexOneToTwo = v2 - v1;
  this->length = vertexOneToTwo.length();
  this->orientation = Quaternion(Z, vertexOneToTwo);
  this->pos = v1 + this->vector()*this->centerOfMassFraction*this->length;
}

Vector3D Line::vertex(const int index)
{
  if (index > 1)
    throw std::runtime_error(QString("Invalid vertex index %1").arg(index).toStdString().c_str());

  const float distanceToVertexFactor = index==0 ? centerOfMassFraction : 1 - centerOfMassFraction;
  const Vector3D centerOfMassToVertexDirection = index== 0 ? -this->direction() : this->direction();

  return this->pos + centerOfMassToVertexDirection * distanceToVertexFactor * this->length;
}

void Line::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
  this->applyForce(moveForce/this->mass);
  moveForce = Vector3D(0,0,0);
}

bool Line::detectCollision(Object::Pointer object)
{
  if(object->shape != this->shape)
    return false;

  return this->detectCollision(std::dynamic_pointer_cast<Line>(object));
}

bool Line::detectCollision(std::shared_ptr<Line> line)
{
  Q_UNUSED(line);
  return false;
}

void Line::collide(Object::ConstPointer line)
{
  Q_UNUSED(line);
}


Vector3D Line::vector()
{
  return this->direction() * this->length;
}

Vector3D Line::direction()
{
  return this->orientation.rotate(Z);
}

void Line::draw()
{
//  calcGeo();
  glLineWidth(4);
  glBegin(GL_LINES);								//horizontal line
//    glNormal3f(normal.x, normal.y, normal.z);	//normal vector to line points up
    glColor3ub(255, 255, 255);					// Set Color To White
    glVertex3f(this->vertex(0).x, this->vertex(0).y, this->vertex(0).z);
    glVertex3f(this->vertex(1).x, this->vertex(1).y, this->vertex(1).z);
  glEnd();

  return;
}

void* Line::getProperty(int idx, dataType &type)
{
  void* ptr = NULL;

  if((0 <= idx) && (idx <14))
    Object::getProperty(idx, type);
  else
  {
    switch(idx)
    {
    case 14:
      ptr = &this->vertex(0);
      type = tpVECTOR3D;
      break;
    /*case 15:
      ptr = &vertex[1];
      type = tpSHAPE;
      break;
    case 16:
      ptr = texture;
      type = tpTEXTURE;
      break;
    case 17:
      ptr = &movable;
      type = tpBOOL;
      break;
    case 18:
      ptr = &moveForce;
      type = tpVECTOR3D;
      break;
    case 19:
      ptr = &isTouching;
      type = tpBOOL;
      break;
    case 6:
      ptr = &touchObj;
      type = tpOBJP;
      break;
    case 7:
      ptr = &isTouching3ds;
      type = tpBOOL;
      break;
    case 8:
      //ptr = touchObj3ds;
      //type = tpMASS;
      break;
    case 9:
      ptr = &self;
      type = tpOBJP;
      break;
    case 10:
      ptr = touches;
      type = tpOBJP;
      break;
    case 11:
      ptr = &bDraw;
      type = tpBOOL;
      break;
    case 12:
      ptr = &bDetect;
      type = tpBOOL;
      break;
    case 13:
      ptr = &bCollide;
      type = tpBOOL;
      break;*/
    default:
      break;
    }
  }

  return ptr;
}

void Line::addTouchedObject(Object::Pointer object, const int vertexIndex)
{
  Object::addTouchedObject(object);
  this->touchingVertexIndex[object] = vertexIndex;
}


Vector3D Line::vertexVelocity(int vertexIndex)
{
  Vector3D linVel, rotVel, velDir, velOut;
  GLfloat armLength;		//distance from com to vertex

  linVel = this->vel;
  switch(vertexIndex)
  {
    case 0:
      armLength = centerOfMassFraction*length;
      velDir = Cross(this->axis,this->vertex(0) - this->vertex(1));
      velDir.unitize();
      rotVel = velDir*armLength*this->angularVelocity;
      break;
    case 1:
      armLength = (1.0f-centerOfMassFraction)*length;
      velDir = Cross(this->axis, this->vertex(1) - this->vertex(0));
      velDir.unitize();
      rotVel = velDir*armLength*this->angularVelocity;
      break;
    default:
      break;
  }
  velOut = linVel + rotVel;

  return velOut;
}
