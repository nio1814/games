#ifndef GLWIDGET
#define GLWIDGET

#include <qopenglwidget.h>

class GLWidget : public QOpenGLWidget
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

