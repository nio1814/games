#include "line.h"

object_line::object_line(float mass, Vector3D v1, Vector3D v2, float cmf) :
  Object(mass),
  centerOfMassFraction(cmf)
{
//	Object();
//	object_line();
  type = LINE;
  vertex[0] = v1;
  vertex[1] = v2;
  width = 15;
  initGeo();
    bMovable = true;
}

void object_line::initGeo()
{
  lvec = (vertex[1] - vertex[0]).unit();
  length = (vertex[1] - vertex[0]).length();
  normal = Z - Z.proj(lvec);							//make normal vector starting from Z

  mass->pos = vertex[0] + (vertex[1] - vertex[0]) * centerOfMassFraction;
  mass->I = mass->m*pow(length,2)/12.0f;
  return;
}

void object_line::calcGeo()
{
  lvec = lvec.rotate3D(mass->axis, mass->dtheta);
  vertex[0] = mass->pos - (lvec*length*centerOfMassFraction);
  vertex[1] = mass->pos + (lvec*length*(1-centerOfMassFraction));
  normal = Z - Z.proj(lvec);							//make normal vector starting from Z

  return;
}

void object_line::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
  mass->applyForce(moveForce/mass->m);
  calcGeo();
  moveForce = Vector3D(0,0,0);
}

void object_line::draw()
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

void* object_line::getProperty(int idx, dataType &type)
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


Vector3D object_line::calcVertexVel(int vnum)
{
  Vector3D linVel, rotVel, velDir, velOut;
  GLfloat armLength;		//distance from com to vertex

  linVel = mass->vel;
  switch(vnum)
  {
    case 0:
      armLength = centerOfMassFraction*length;
      velDir = Cross(mass->axis,vertex[0]-vertex[1]);
      velDir.unitize();
      rotVel = velDir*armLength*mass->avel;
      break;
    case 1:
      armLength = (1.0f-centerOfMassFraction)*length;
      velDir = Cross(mass->axis, vertex[1]-vertex[0]);
      velDir.unitize();
      rotVel = velDir*armLength*mass->avel;
      break;
    default:
      break;
  }
  velOut = linVel + rotVel;

  return velOut;
}
