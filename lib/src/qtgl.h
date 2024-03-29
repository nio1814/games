#ifndef QTGL_H
#define QTGL_H

#include <QtGlobal>

#if QT_VERSION >= 0x050400
#include <qopengl.h>
#else
#include <QtOpenGL>
#endif

#include <qvector3d.h>

void glLookAt(QVector3D cameraPosition, QVector3D lookPosition, QVector3D upDirection);
void glPerspective(GLfloat viewAngle, GLfloat aspectRatio, GLfloat clipClose, GLfloat clipFar);

#endif // QTGL_H



