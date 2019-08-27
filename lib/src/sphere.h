#ifndef SPHERE_H
#define SPHERE_H

void drawtriangle(float *v1, float *v2, float *v3);
void normalize(float v[3]);
void subdivide(float *v1, float *v2, float *v3, long depth);
void drawSphere(int subDivisions);

#endif // SPHERE_H
