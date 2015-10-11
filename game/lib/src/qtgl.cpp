#include "qtgl.h"

void glLookAt(QVector3D cameraPosition, QVector3D lookPosition, QVector3D upDirection)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
#if QT_VERSION > 0x050000
    GLfloat* matrixData = matrix.constData();
#else
    GLfloat multMatrixData[16];
    const qreal* matrixData = matrix.constData();

    for (int n=0; n<16; n++)
        multMatrixData[n] = matrixData[n];
#endif

    glMultMatrixf(multMatrixData);
}
