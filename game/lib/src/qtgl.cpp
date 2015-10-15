#include "qtgl.h"

#include <qmatrix4x4.h>

const GLfloat* matrixData(QMatrix4x4& matrix)
{
#if QT_VERSION == 0x050500
    const GLfloat* multMatrixData = static_cast<const GLfloat*>(matrix.constData());
#elif QT_VERSION > 0x050000
    const GLfloat* multMatrixData = matrix.constData();
#else
    GLfloat multMatrixData[16];
    const qreal* matrixData = matrix.constData();

    for (int n=0; n<16; n++)
	   multMatrixData[n] = matrixData[n];
#endif
    return multMatrixData;
}

void glLookAt(QVector3D cameraPosition, QVector3D lookPosition, QVector3D upDirection)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.lookAt(cameraPosition, lookPosition, upDirection);

    glLoadIdentity();												// Reset The Current Modelview Matrix
    glMultMatrixf(matrixData(matrix));

    return;
}

void glPerspective(GLfloat viewAngle, GLfloat aspectRatio, GLfloat clipClose, GLfloat clipFar)
{
	QMatrix4x4 matrix;
	matrix.setToIdentity();
	matrix.perspective(viewAngle, aspectRatio, clipClose, clipFar);

	glLoadIdentity();
	glMultMatrixf(matrixData(matrix));

	return;
}
