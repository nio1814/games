#ifndef GLWIDGET
#define GLWIDGET

#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
class GLWidget : public QOpenGLWidget
#else
#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
public slots:
    void process();
};

#endif // GLWIDGET

