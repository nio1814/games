#ifndef GLWIDGET
#define GLWIDGET

class gameObj;
class Mouse;
class object_sphere;

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
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void initializeObjects();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
public slots:
    void process();
    void ProcessKeyboard();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    gameObj* game;
    Mouse* mos;
    object_sphere* ball;
};

#endif // GLWIDGET

