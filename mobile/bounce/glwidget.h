#ifndef GLWIDGET
#define GLWIDGET

#include "ellipse.h"


#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
#include <qopenglfunctions.h>
#include <qmatrix4x4.h>
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
#else
#include "QtOpenGL/QGLWidget"

class GLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();
    void initializeObjects();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
signals:

public slots:
    void process();

private:
	Ellipses m_ellipses;
	QMatrix4x4 m_projection;

	QOpenGLShaderProgram* m_program;

};

#endif // GLWIDGET

