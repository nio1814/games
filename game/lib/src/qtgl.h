#ifndef QTGL_H
#define QTGL_H

#include <QtGlobal>

#if QT_VERSION >= 0x050400
#else
#include <QtOpenGL>
#endif

#endif // QTGL_H

void glLookAt(QVector3D cameraPosition, QVector3D lookPosition, QVector3D upDirection);

