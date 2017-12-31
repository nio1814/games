#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include "glwidget.h"

#include <QDateTime>
#include <memory>

QT_FORWARD_DECLARE_CLASS(Level)

class LevelWindow : public GLWidget
{
public:
	LevelWindow(QWidget* parent);
	~LevelWindow();

	void run();
public slots:
	void update();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void keyPressEvent(QKeyEvent *key);
private:	
	std::shared_ptr<Level> m_level;
	std::shared_ptr<std::map<int,bool> > m_keys;
	QDateTime m_lastTime;
};

#endif // LEVELWINDOW_H
