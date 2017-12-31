#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include "glwidget.h"

#include <QDateTime>
#include <memory>

QT_FORWARD_DECLARE_CLASS(Level)
QT_FORWARD_DECLARE_CLASS(Camera)

class LevelWindow : public GLWidget
{
public:
	enum Mode {GameMode, CameraMode};

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
	Mode m_mode = GameMode;
	std::unique_ptr<Camera> m_camera;
};

#endif // LEVELWINDOW_H
