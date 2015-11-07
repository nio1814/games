#ifndef GLWIDGET_H
#define GLWIDGET_H

class Simulation;

#if (QT_VERSION >= 0x050500)
#include "qopenglwidget.h"
class GLWidget : public QOpenGLWidget
#else
#include <QtOpenGL/QGLWidget>
class GLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent=0);
    ~GLWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
public slots:
    void animate();
private:
    Simulation* sim;
};

#endif // GLWIDGET_H
