#include "sphere.h"

#define SPHERE_X .525731112119133606
#define SPHERE_Z .850650808352039932

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


object_sphere::object_sphere(float mass, float rad, const Vector3D position) : Object(mass),
  radius(rad)
{
  type = SPHERE;
    /*quad = gluNewQuadric();								// Create A New Quadratic
  gluQuadricNormals(quad, GL_SMOOTH);					// Generate Smooth Normals For The Quad
    gluQuadricTexture(quad, GL_TRUE);						// Enable Texture Coords For The Quad*/
  bMovable = true;
  this->mass->pos = position;
}

object_sphere::~object_sphere()
{
//	delete quad;								// Create A New Quadratic
}

void object_sphere::solve()													//gravitational force will be applied therefore we need a "solve" method.
{
  //mass->applyForce(Vector3D(0.0f, gravity, 0.0f) * mass->m);				//gravitational force is as F = m * g. (mass times the gravitational acceleration)
  mass->applyForce(moveForce/mass->m);
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
  glTranslatef(mass->pos.x, mass->pos.y, mass->pos.z);

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
  glTranslatef(-mass->pos.x, -mass->pos.y, -mass->pos.z);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);							// Disable 2D Texture Mapping
}

bool object_sphere::detectCollision(const std::shared_ptr<object_sphere> obj2)
{
  bool detect = false;

  Vector3D vecToSphere;
  GLfloat dist;

//  if(!isSame(self, obj2->self))
//  {
    vecToSphere = mass->pos - obj2->mass->pos;
    dist = vecToSphere.length();

    if(dist < (radius + obj2->radius))
    {
      detect = true;
      m_touchedObjects.push_back(obj2);
      //p.index = sidx;
      //p.shape = SPHERE;
      //p.holder = allobj;
    }
//  }

  return detect;
}

//bool object_sphere::detectCollision(const object_plane *plane)
//{
//  bool detect = false;

//  Vector3D vecToPlane = mass->pos - plane->mass->pos;
//  GLfloat normDist = fabs(vecToPlane.dot(plane->normal));
//          //normToPlane = normToPlane.length();

//  if(normDist <= radius)
//  {
//     GLfloat wDist = fabs(vecToPlane.dot(plane->wvec));
//    if(wDist<=.5f*plane->width)
//    {
//      GLfloat lDist = fabs(vecToPlane.dot(plane->lvec));
//      if(lDist<=.5f*plane->length)
//      {
//        detect = true;
//        m_touchedObjects.append(plane);
////                p.index = pidx;
////                p.shape = plane->objType;
////                p.holder = allobj;
//        //p.holder = reinterpret_cast<object_holder*>(allobj);
//      }
//    }
//  }

//  return detect;
//}

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

void object_sphere::collide(const object_sphere *sphere2)
{
  Mass *mass1, *mass2;
  GLfloat m1, m2, v1normMag;
  Vector3D v1, v2, sphereNorm;
  Vector3D sforce = mass->force;

  mass1 = mass;
  mass2 = sphere2->mass;

  m1 = mass1->m;
  m2 = mass2->m;
  v1 = mass1->vel;
  v2 = mass2->vel;
  v1normMag = fabs(v1.dot(&sphereNorm));
  sphereNorm = (mass1->pos - mass2->pos);
  sphereNorm/sphereNorm.length();

  if(sphere2->bMovable)
    v1 = v1*((m1-m2)/(m1+m2)) + v2*(2*m2/(m1+m2));
  else
    v1 += sphereNorm*(mass1->elas)*v1normMag*2;

//	s1->xrotspeed = v1.dot(&Vector3D(1,0,0));
  mass1->avelnew = v1.dot(Vector3D(1,0,0));
//	s1->yrotspeed = v1.dot(&Vector3D(0,1,0));
  mass1->avelnew += v1.dot(Vector3D(0,1,0));
  //s1->zrotspeed = v1.dot(&Vector3D(0,0,1));

  mass1->velnew = v1;
  mass = mass1;
  sforce += sphereNorm*(fabs(sphereNorm.dot(&sforce)));
  mass->forcenew = sforce;

  return;
}

//void object_sphere::collide(const object_plane *plane)
//{
//  GLfloat MINBOUNCEVEL = .1f;

//  Mass *mass1, *mass2;
//  GLfloat m1, m2, v1normMag;
//  Vector3D v1, v2, vpara, planeNorm;
//  int awayDir;

//  Vector3D sforce = mass->force;

//  mass1 = mass;
//  mass2 = plane->mass;

//  m1 = mass1->m;
//  m2 = mass2->m;
//  v1 = mass1->vel;
//  v2 = mass2->vel;

//  /*if(plane->isAbove(&mass->pos))
//    planeNorm = plane->normal;
//  else
//    planeNorm = plane->normal*-1;*/
//  planeNorm = (mass1->pos - mass2->pos).proj(plane->normal);
//  planeNorm.unitize();
//  v1normMag = fabs(v1.dot(&planeNorm));

//  if(fabs(v1.length()) < MINBOUNCEVEL)
//    v1 -= v1;
//  else if(plane->bMovable)
//    v1 = v1*((m1-m2)/(m1+m2)) + v2*(2*m2/(m1+m2));
//  else
//    v1 += planeNorm*(1+mass1->elas)*v1normMag;

//  mass1->velnew = v1;
//  mass = mass1;
//  sforce += planeNorm*(fabs(planeNorm.dot(&sforce)));
//  mass->forcenew = sforce;

//  mass->pos += planeNorm*(radius - planeNorm.dot(mass1->pos-mass2->pos));

//  vpara = v1 - v1.proj(Y);

////	sphere->xrotspeed = vpara.dot(&Vector3D(0,0,1))/(sphere->radius*2*PI);
//  mass->avelnew = vpara.dot(Vector3D(0,0,1))/(radius*2*PI);
////	sphere->zrotspeed = vpara.dot(&Vector3D(-1,0,0))/(sphere->radius*2*PI);
//  mass->avelnew += vpara.dot(Vector3D(-1,0,0))/(radius*2*PI);

//  return;
//}
