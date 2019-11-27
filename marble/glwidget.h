#ifndef GLWIDGET
#define GLWIDGET

#include "gameobject.h"

#include <QtGlobal>

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

    gameObj game;
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
signals:
    void keyPressed();
public slots:
    void process();
	void processKeyboard();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    Mouse* mouse;
    std::shared_ptr<object_sphere> ball;
};

#endif // GLWIDGET

