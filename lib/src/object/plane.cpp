#include "plane.h"

const float EPSILON = 1E-7;

object_plane::object_plane(float mass, float wid, float len, float phi, float theta, Vector3D mAxis) : Object(mass),
  width(wid), length(len), angles(Vector2D(phi, theta))
{
//	object_plane();
  type = PLANE;
  makeBase(&mAxis);
}

object_plane::object_plane(float width, float length, Vector3D position, Vector3D norm, matrix2D3 basis) : Object(1),
  width(width), length(length)//, m_basis(basis)
{
  norm.unitize();
  normal = norm;
  type = PLANE;
  mass->pos = position;
  basis = basis;
  orient(norm);
}

object_plane& object_plane::operator = (const object_plane& plane)
{
    Object::operator =(plane);

    width = plane.width;
    length = plane.length;
    normal = plane.normal;
    wvec = plane.wvec;
    lvec = plane.lvec;
    angles = plane.angles;

    return *this;
}

void object_plane::draw()
{
  Vector3D v;							//keeps coords of vertex for drawing
  bool textureExists = texture!=NULL;
  //int numTexture = texture->numLayers;

  glEnable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
  glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping
  glPushMatrix();
  glTranslatef(mass->pos.x, mass->pos.y, mass->pos.z);

  glPushMatrix();

  if(textureExists)
    glBindTexture(GL_TEXTURE_2D, texture->layer[0]);			// Select Texture 1 (0)
  glBegin(GL_QUADS);									// Begin Drawing A Quad
    //glNormal3f(0.0f, 1.0f, 0.0f);						// Normal Pointing Up
    glNormal3f(normal.x, normal.y, normal.z);						// Normal Pointing Up
    glColor3ub(0, 59, 255);
    glTexCoord2f(0.0f, 1.0f);					// Bottom Left Of Texture
    v = (-wvec*width + lvec*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Bottom Left Corner Of Floor

    glTexCoord2f(0.0f, 0.0f);					// Top Left Of Texture
    v = (-wvec*width - lvec*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Top Left Corner Of Floor

    glTexCoord2f(1.0f, 0.0f);					// Top Right Of Texture
    v = (wvec*width - lvec*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Top Right Corner Of Floor

    glTexCoord2f(1.0f, 1.0f);					// Bottom Right Of Texture
    v = (wvec*width + lvec*length)*.5f;
    glVertex3f(v.x, v.y, v.z);					// Bottom Right Corner Of Floor
  glEnd();

  glPopMatrix();
    glTranslatef(-mass->pos.x, -mass->pos.y, -mass->pos.z);
  glPopMatrix();
  glDisable(GL_LIGHTING);								// Since We Use Blending, We Disable Lighting
}

void object_plane::makeBase(const Vector3D* mAxis)
{
  if(*mAxis == Z)
  {
    wvec = X.rotate3D(Z, angles.x);							//rotate x by phi
    lvec = (Y.rotate3D(Y, angles.x)).rotate3D(wvec,angles.y);	//rotate y down by phi then theta
  }
  else if(*mAxis == Y)
  {
    wvec = Z.rotate3D(Y, angles.x);
    lvec = (X.rotate3D(Y, angles.x)).rotate3D(wvec,angles.y);
  }
  else if(*mAxis == X)
  {
    wvec = Y.rotate3D(X, angles.x);
    lvec = (Z.rotate3D(Y, angles.x)).rotate3D(wvec,angles.y);
  }
  else
    //msgbox('incorrect major axis');
    return;

  normal = Cross(wvec, lvec);

  return;
}

void object_plane::flipBase()
{
  Vector3D temp;
  temp = lvec;
  lvec = wvec;
  wvec = temp;

  return;
}

void object_plane::orient(const Vector3D& norm)
{
  normal = norm;
  Vector3D sphericalCoords = basis.cartesianToSpherical(norm);
  wvec = basis.A[0].rotate3D(basis.A[1], sphericalCoords.z);
  wvec = wvec.rotate3D(basis.A[2], sphericalCoords.y);

//	lvec = m_basis.A[1].rotate3D(m_basis.A[1], sphericalCoords.z);
  lvec = basis.A[1].rotate3D(basis.A[2], sphericalCoords.y);

  return;
}

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

void object_plane::rotate(const Vector3D &axis, GLfloat degrees)
{
  normal = normal.rotate3D(axis, degrees);
  wvec = wvec.rotate3D(axis, degrees);
  lvec = lvec.rotate3D(axis, degrees);

    return;
}

void object_plane::rotateAroundNormal(GLfloat degrees)
{
  return rotate(normal, degrees);
}

bool object_plane::inPlane(const Vector3D *v)
{
  bool in = false;
  Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

  in = (fabs(planeBasisv.x) < .5f*width) && (fabs(planeBasisv.y) < .5f*length);
  return in;
}

bool object_plane::atSurface(const Vector3D *v)
{
  bool atSurf = false;
  Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

  atSurf = (fabs(planeBasisv.z) < EPSILON);

  return atSurf;
}

bool object_plane::isAbove(const Vector3D *v) const
{
  bool above = false;
  Vector3D planeBasisv = v->decompose(wvec, lvec, normal);

  above = (planeBasisv.z > 0.0f);

  return above;
}

std::shared_ptr<object_plane> copyPlane(std::shared_ptr<const object_plane> plane)
{
  return std::make_shared<object_plane>(*plane);
}
