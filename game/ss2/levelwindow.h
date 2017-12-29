#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include "glwidget.h"

#include <memory>

QT_FORWARD_DECLARE_CLASS(Level)

class LevelWindow : public GLWidget
{
public:
	LevelWindow(QWidget* parent);
	~LevelWindow();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void keyPressEvent(QKeyEvent *key);
private:
	QMatrix4x4 m_projection;
	GLfloat m_aspectRatio;
	std::shared_ptr<Level> m_level;

	std::shared_ptr<std::map<int,bool> > m_keys;

};

#endif // LEVELWINDOW_H
