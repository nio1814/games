#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "simulation.h"

#include <QtOpenGL/QGLWidget>
class GLWidget : public QGLWidget
{
//    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
public slots:
    void animate();
private:
    Simulation sim;

};

#endif // GLWIDGET_H
