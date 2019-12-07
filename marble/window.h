#ifndef WINDOW_H
#define WINDOW_H

#include "gameobject.h"
#include "glwidget.h"


class Mouse;
class object_sphere;

class Window : public GLWidget
{
    Q_OBJECT
public:
    Window(QWidget *parent);

    void initializeObjects();

    gameObj game;
protected:
    void initializeGL();
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
    std::shared_ptr<object_sphere> ball;
};

#endif // GLWIDGET

