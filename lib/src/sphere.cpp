#include "sphere.h"

#include "qtgl.h"

#include <math.h>

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
