#include "qtgl.h"

#include <qmatrix4x4.h>

void multMatrix(const QMatrix4x4& matrix)
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

    glLoadIdentity();
    glMultMatrixf(multMatrixData);

    return;
}

void glLookAt(QVector3D cameraPosition, QVector3D lookPosition, QVector3D upDirection)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.lookAt(cameraPosition, lookPosition, upDirection);

    multMatrix(matrix);
//    glMultMatrixf(matrixData(matrix));
//    glMultMatrixf(reinterpret_cast<const GLfloat*>(matrix.constData()));

    return;
}

void glLookAt(const std::vector<float>& cameraPosition, const std::vector<float>& lookPosition, const std::vector<float>& up)
{
	QVector3D camPosition = QVector3D(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	QVector3D camLook = QVector3D(lookPosition[0], lookPosition[1], lookPosition[2]);
	QVector3D camUp = QVector3D(up[0], up[1], up[2]);

	glLookAt(camPosition, camLook, camUp);
}

void glPerspective(GLfloat viewAngle, GLfloat aspectRatio, GLfloat clipClose, GLfloat clipFar)
{
	QMatrix4x4 matrix;
	matrix.setToIdentity();
    matrix.perspective(viewAngle, aspectRatio, clipClose, clipFar);

	glLoadIdentity();
//    glMultMatrixf(matrixData(matrix));
     multMatrix(matrix);

	return;
}
