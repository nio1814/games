#include "plane.h"

const float EPSILON = 1E-7;

Plane::Plane(float wid, float len, const Vector3D &position, float phi, float theta, Vector3D axis) : Object(position),
  width(wid),
  length(len)//, angles(Vector2D(phi, theta))
{
//	object_plane();
  shape = PLANE;
  orient(axis, theta, phi);
}

Plane::Plane(float width, float length, const Vector3D &position, const Vector3D &up, const Vector3D &toRight) :
  Object(position),
  width(width), length(length)//, m_basis(basis)
{
//  norm.unitize();
//  normal = norm;
  shape = PLANE;
//  mass->pos = position;
//  normal = normal;
  orient(up, toRight);
}

Plane& Plane::operator = (const Plane& plane)
{
    Object::operator =(plane);
  this->quaternion = plane.quaternion;
    width = plane.width;
    length = plane.length;
//    normal = plane.normal;
//    wvec = plane.wvec;
//    lvec = plane.lvec;
//    angles = plane.angles;

    return *this;
}

Vector3D Plane::normal() const
{
  return this->quaternion.rotate(Z);
}

Vector3D Plane::right()
{
  return this->quaternion.rotate(X);
}

Vector3D Plane::forward()
{
  return this->quaternion.rotate(Y);
}

//void Plane::setNormal(const Vector3D normal, const Vector3D majorAxis)
//{
//  this->normal = normal;
//  this->makeBase(majorAxis);
//}

void Plane::draw()
{
  Vector3D v;							//keeps coords of vertex for drawing
  //int numTexture = texture->numLayers;

  glEnable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
  glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
  glPushMatrix();
  glTranslatef(this->pos.x, this->pos.y, this->pos.z);

  glPushMatrix();

  if(this->hasTexture())
    glBindTexture(GL_TEXTURE_2D, this->texture.layer[0]);			// Select Texture 1 (0)
  glBegin(GL_QUADS);									// Begin Drawing A Quad
    //glNormal3f(0.0f, 1.0f, 0.0f);						// Normal Pointing Up
    glNormal3f(this->normal().x, this->normal().y, this->normal().z);						// Normal Pointing Up
    glColor3ub(0, 59, 255);
    glTexCoord2f(0.0f, 1.0f);					// Bottom Left Of Texture
    v = (-this->right()*width + this->forward()*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Bottom Left Corner Of Floor

    glTexCoord2f(0.0f, 0.0f);					// Top Left Of Texture
    v = (-this->right()*width - this->forward()*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Top Left Corner Of Floor

    glTexCoord2f(1.0f, 0.0f);					// Top Right Of Texture
    v = (this->right()*width - this->forward()*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Top Right Corner Of Floor

    glTexCoord2f(1.0f, 1.0f);					// Bottom Right Of Texture
    v = (this->right()*width + this->forward()*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Bottom Right Corner Of Floor
  glEnd();

  glPopMatrix();
    glTranslatef(-this->pos.x, -this->pos.y, -this->pos.z);
  glPopMatrix();
  glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
}

void Plane::orient(const matrix2D3 &basis)
{
  this->quaternion = Quaternion(basis).inverse();
}

void Plane::orient(const Vector3D &up, const Vector3D &toRight, Vector3D toFront)
{
  if(toFront.isNull())
    toFront = Cross(up.unit(), toRight.unit());
  orient(matrix2D3(toRight, toFront, up, false));
}

void Plane::orient(const Vector3D& majorAxis, const float theta, const float phi)
{
  Vector3D toRight;
  Vector3D toFront;

  if(majorAxis == Z)
  {
    toRight = X.rotate3D(Z, theta);							//rotate x by phi
    toFront = (Y.rotate3D(Y, theta)).rotate3D(toRight, phi);	//rotate y down by phi then theta
  }
  else if(majorAxis == Y)
  {
    toRight = Z.rotate3D(Y, theta);
    toFront = (X.rotate3D(Y, theta)).rotate3D(toRight, phi);
  }
  else if(majorAxis == X)
  {
    toRight = Y.rotate3D(X, theta);
    toFront = (Z.rotate3D(Y, theta)).rotate3D(toRight, phi);
  }
  else
    //msgbox('incorrect major axis');
    return;

  const Vector3D up = Cross(toRight.unit(), toFront.unit());
  orient(up, toRight, toFront);
  //  return;
}

Vector3D Plane::basisPosition(const Vector3D point) const
{
  const Vector3D offset = point - this->pos;

  return this->quaternion.rotate(offset);
}

void Plane::flipBase()
{
//  Vector3D temp;
//  temp = lvec;
//  lvec = wvec;
//  wvec = temp;

//  return;
}

//void Plane::orient(const Vector3D& norm)
//{
//  normal = norm;
//  Vector3D sphericalCoords = basis.cartesianToSpherical(norm);
//  wvec = basis.A[0].rotate3D(basis.A[1], sphericalCoords.z);
//  wvec = wvec.rotate3D(basis.A[2], sphericalCoords.y);

////	lvec = m_basis.A[1].rotate3D(m_basis.A[1], sphericalCoords.z);
//  lvec = basis.A[1].rotate3D(basis.A[2], sphericalCoords.y);

//  return;
//}

/*bool object_plane::doCollisions(const object_holder *allObjs)
{
  bool detect = false;
  objP point;

  detect = detectCollision(this, allObjs, point);
  touching = true;

  if(detect)
  {
    collide(this, allObjs, point);
  }

  return detect;
}*/

void Plane::rotate(const Vector3D &axis, GLfloat degrees)
{
  Quaternion rotation(axis, degrees);

}

void Plane::rotateAroundNormal(GLfloat degrees)
{
  return this->rotate(this->normal(), degrees);
}

bool Plane::detectCollision(std::shared_ptr<Object> object)
{
  if(this->shape != object->shape)
    return false;

  return this->detectCollision(std::dynamic_pointer_cast<Plane>(object));
}

bool Plane::detectCollision(std::shared_ptr<Plane> plane)
{
  Q_UNUSED(plane);
  return false;
}

void Plane::collide(Object::ConstPointer object)
{
  Q_UNUSED(object);
}

bool Plane::inPlane(const Vector3D& v)
{
  const Vector3D relativePosition = this->basisPosition(v);

  return (std::abs(relativePosition.x) < .5f*width) && (std::abs(relativePosition.y) < .5f*length);
}

bool Plane::atSurface(const Vector3D& point)
{
  const Vector3D relativePosition = this->basisPosition(point);

  return relativePosition.z < EPSILON;
}

bool Plane::isAbove(const Vector3D& point) const
{
  const Vector3D relativePosition = this->basisPosition(point);

  return relativePosition.z > EPSILON;
}

std::shared_ptr<Plane> copyPlane(std::shared_ptr<const Plane> plane)
{
  return std::make_shared<Plane>(*plane);
}
