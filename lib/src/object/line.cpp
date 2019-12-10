#include "line.h"

Line::Line(float mass, Vector3D v1, Vector3D v2, float cmf) :
  Object(Vector3D(), mass),
  centerOfMassFraction(cmf)
{
//	Object();
//	object_line();
  shape = LINE;
  vertex[0] = v1;
  vertex[1] = v2;
  width = 15;
  initGeo();
    bMovable = true;
}

void Line::initGeo()
{
  lvec = (vertex[1] - vertex[0]).unit();
  length = (vertex[1] - vertex[0]).length();
  normal = Z - Z.proj(lvec);							//make normal vector starting from Z

  this->pos = vertex[0] + (vertex[1] - vertex[0]) * centerOfMassFraction;
  this->I = this->m*pow(length,2)/12.0f;
  return;
}

void Line::calcGeo()
{
  lvec = lvec.rotate3D(this->axis, this->dtheta);
  vertex[0] = this->pos - (lvec*length*centerOfMassFraction);
  vertex[1] = this->pos + (lvec*length*(1-centerOfMassFraction));
  normal = Z - Z.proj(lvec);							//make normal vector starting from Z

  return;
}

void Line::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
  this->applyForce(moveForce/this->m);
  calcGeo();
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

void Line::draw()
{
  calcGeo();
  glLineWidth(4);
  glBegin(GL_LINES);								//horizontal line
    glNormal3f(normal.x, normal.y, normal.z);	//normal vector to line points up
    glColor3ub(255, 255, 255);					// Set Color To White
    glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
    glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
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
      ptr = &vertex[0];
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


Vector3D Line::calcVertexVel(int vnum)
{
  Vector3D linVel, rotVel, velDir, velOut;
  GLfloat armLength;		//distance from com to vertex

  linVel = this->vel;
  switch(vnum)
  {
    case 0:
      armLength = centerOfMassFraction*length;
      velDir = Cross(this->axis,vertex[0]-vertex[1]);
      velDir.unitize();
      rotVel = velDir*armLength*this->avel;
      break;
    case 1:
      armLength = (1.0f-centerOfMassFraction)*length;
      velDir = Cross(this->axis, vertex[1]-vertex[0]);
      velDir.unitize();
      rotVel = velDir*armLength*this->avel;
      break;
    default:
      break;
  }
  velOut = linVel + rotVel;

  return velOut;
}
