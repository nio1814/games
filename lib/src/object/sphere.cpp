#include "sphere.h"

const float SPHERE_X = .525731112119133606f;
const float SPHERE_Z = .850650808352039932f;

static GLfloat vdata[12][3] = {
   {-SPHERE_X, 0.0, SPHERE_Z}, {SPHERE_X, 0.0, SPHERE_Z}, {-SPHERE_X, 0.0, -SPHERE_Z}, {SPHERE_X, 0.0, -SPHERE_Z},
   {0.0, SPHERE_Z, SPHERE_X}, {0.0, SPHERE_Z, -SPHERE_X}, {0.0, -SPHERE_Z, SPHERE_X}, {0.0, -SPHERE_Z, -SPHERE_X},
   {SPHERE_Z, SPHERE_X, 0.0}, {-SPHERE_Z, SPHERE_X, 0.0}, {SPHERE_Z, -SPHERE_X, 0.0}, {-SPHERE_Z, -SPHERE_X, 0.0}
};

static GLint tindices[20][3] = {
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

void drawtriangle(float *v1, float *v2, float *v3)
{
   glBegin(GL_POLYGON);
    glNormal3fv(v1); glVertex3fv(v1);
    glNormal3fv(v2); glVertex3fv(v2);
    glNormal3fv(v3); glVertex3fv(v3);
   glEnd();
}

void normalize(float v[3])
{
   GLfloat d = sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
   if (d == 0.0f) {
      qErrnoWarning("zero length vector");
      return;
   }
   v[0] /= d; v[1] /= d; v[2] /= d;
}

void subdivide(float *v1, float *v2, float *v3, long depth)
{
   GLfloat v12[3], v23[3], v31[3];
   GLint i;

   if (depth == 0) {
      drawtriangle(v1, v2, v3);
       return;
   }

   for (i = 0; i < 3; i++) {
       v12[i] = v1[i]+v2[i];
      v23[i] = v2[i]+v3[i];
      v31[i] = v3[i]+v1[i];
   }
   normalize(v12);
   normalize(v23);
   normalize(v31);
   subdivide(v1, v12, v31, depth-1);
   subdivide(v2, v23, v12, depth-1);
   subdivide(v3, v31, v23, depth-1);
   subdivide(v12, v23, v31, depth-1);
}

void drawSphere(int subDivisions)
{
    for (int i = 0; i < 20; i++)
    {
    subdivide(&vdata[tindices[i][0]][0],
          &vdata[tindices[i][1]][0],
    &vdata[tindices[i][2]][0],
        subDivisions);
    }
}


object_sphere::object_sphere(float mass, float rad, const Vector3D position) :
  Object(position, mass),
  radius(rad)
{
  shape = SPHERE;
    /*quad = gluNewQuadric();								// Create A New Quadratic
  gluQuadricNormals(quad, GL_SMOOTH);					// Generate Smooth Normals For The Quad
    gluQuadricTexture(quad, GL_TRUE);						// Enable Texture Coords For The Quad*/
  bMovable = true;
  this->pos = position;
}

object_sphere::~object_sphere()
{
//	delete quad;								// Create A New Quadratic
}

void object_sphere::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
  //mass->applyForce(Vector3D(0.0f, gravity, 0.0f) * mass->m);				//gravitational force is as F = m * g. (mass times the gravitational acceleration)
  this->applyForce(moveForce/this->mass);
  //mass->applyForce(mass->force);
  moveForce = Vector3D(0,0,0);
}

void object_sphere::draw()
{
  glColor4f(1.0f, 1.0f, 1.0f, .9f);						// Set Color To White
  //glColor3ub(texture->color.x, texture->color.y, texture->color.z);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);							// Enable 2D Texture Mapping

  glPushMatrix();
  glTranslatef(this->pos.x, this->pos.y, this->pos.z);

  glPushMatrix();
  //glRotatef(xrot,1.0f,0.0f,0.0f);						// Rotate On The X Axis By xrot
  //glRotatef(yrot,0.0f,1.0f,0.0f);						// Rotate On The Y Axis By yrot
  //glRotatef(zrot,0.0f,0.0f,1.0f);						// Rotate On The Y Axis By yrot
  if(hasTexture())
  {
    glBindTexture(GL_TEXTURE_2D, this->texture.layer[0]);			// Select Texture 2 (1)

//	gluSphere(quad, radius, 32, 16);						// Draw First Sphere

    glBindTexture(GL_TEXTURE_2D, texture.layer[1]);			// Select Texture 3 (2)
  }
  glColor4f(1.0f, 1.0f, 1.0f, 0.4f);					// Set Color To White With 40% Alpha
  //glColor3ub(texture->color.x, texture->color.y, texture->color.z);
  glEnable(GL_BLEND);									// Enable Blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set Blending Mode To Mix Based On SRC Alpha
  //
  //if(numTexture>0)
    glEnable(GL_TEXTURE_GEN_S);							// Enable Sphere Mapping
    glEnable(GL_TEXTURE_GEN_T);							// Enable Sphere Mapping

//		gluSphere(quad, radius, 32, 16);					// Draw Another Sphere Using New Texture
                              // Textures Will Mix Creating A MultiTexture Effect (Reflection)
    glScalef(radius, radius, radius);
    drawSphere(2);

    glDisable(GL_TEXTURE_GEN_S);						// Disable Sphere Mapping
    glDisable(GL_TEXTURE_GEN_T);						// Disable Sphere Mapping

  //

  glDisable(GL_BLEND);
  glDisable(GL_LIGHTING);
  glPopMatrix();
  glTranslatef(-this->pos.x, -this->pos.y, -this->pos.z);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);							// Disable 2D Texture Mapping
}

bool object_sphere::detectCollision(std::shared_ptr<Object> object)
{
  if(object->shape != this->shape)
    return false;

  return this->detectCollision(std::dynamic_pointer_cast<const object_sphere>(object));
}

bool object_sphere::detectCollision(const std::shared_ptr<const object_sphere> sphere)
{
  bool detect = false;

  Vector3D vecToSphere;
  GLfloat dist;

//  if(!isSame(self, obj2->self))
//  {
    vecToSphere = this->pos - sphere->pos;
    dist = vecToSphere.length();

    if(dist < (radius + sphere->radius))
    {
      detect = true;
      touchedObjects.push_back(sphere);
      //p.index = sidx;
      //p.shape = SPHERE;
      //p.holder = allobj;
    }
//  }

  return detect;
}

void object_sphere::collide(Object::ConstPointer object)
{
  if(object->shape == Object::SPHERE)
    this->collide(std::dynamic_pointer_cast<const object_sphere>(object));
}

/*bool object_sphere::doCollisions(const object_holder *allObjs)
{
  bool detect = false;
  objP point;

  detect = detectCollision(this, allObjs, point);

  if(detect)
  {
    isTouching = true;
    if(point.shape == SPHERE)
      collide(this, &allObjs->spheres->objs[point.index]);
    else if(point.shape == PLANE)
      collide(this, &allObjs->planes->objs[point.index]);
  }

  return detect;
}*/

void object_sphere::collide(std::shared_ptr<const object_sphere> sphere)
{
  GLfloat m1, m2, v1normMag;
  Vector3D v1, v2, sphereNorm;
  Vector3D sforce = this->force;

  m1 = this->mass;
  v1 = this->vel;
  m2 = sphere->mass;
  v2 = sphere->vel;
  v1normMag = fabs(v1.dot(sphereNorm));
  sphereNorm = (this->pos - sphere->pos);
  sphereNorm/sphereNorm.length();

  if(sphere->bMovable)
    v1 = v1*((m1-m2)/(m1+m2)) + v2*(2*m2/(m1+m2));
  else
    v1 += sphereNorm*(sphere->elasticity)*v1normMag*2;

//	s1->xrotspeed = v1.dot(&Vector3D(1,0,0));
  this->angularVelocityNext = v1.dot(Vector3D(1,0,0));
//	s1->yrotspeed = v1.dot(&Vector3D(0,1,0));
  this->angularVelocityNext += v1.dot(Vector3D(0,1,0));
  //s1->zrotspeed = v1.dot(&Vector3D(0,0,1));

  this->velnew = v1;
  sforce += sphereNorm*(fabs(sphereNorm.dot(sforce)));
  this->forcenew = sforce;

  return;
}
