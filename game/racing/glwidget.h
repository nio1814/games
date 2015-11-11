#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "light.h"

class Level;

#include "QtOpenGL/QGLWidget"
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
private:
	Level* level;
};

#endif // GLWIDGET_H
