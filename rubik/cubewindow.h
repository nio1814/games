#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include "glwidget.h"
#include "shape.h"

class CubeWindow : public GLWidget
{
public:
	CubeWindow(QWidget *parent);

protected:
	void paintGL();

public slots:
    void animate();
    void runKeys();
    void runMouse();

private:
	void rotateLR(GLfloat angle);
	void rotateUD(GLfloat angle);

	rcube_c rcube;
};

#endif // CUBEWINDOW_H
