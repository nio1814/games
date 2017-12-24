#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include "GLWidget.h"

class LevelWindow : public GLWidget
{
public:
	LevelWindow(QWidget* parent);
	~LevelWindow();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
private:
	QMatrix4x4 m_projection;
	GLfloat m_aspectRatio;
};

#endif // LEVELWINDOW_H
