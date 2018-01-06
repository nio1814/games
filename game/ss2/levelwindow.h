#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include "glwidget.h"

#include <QDateTime>
#include <memory>

QT_FORWARD_DECLARE_CLASS(Level)
QT_FORWARD_DECLARE_CLASS(Camera)
QT_FORWARD_DECLARE_CLASS(Keys)

class LevelWindow : public GLWidget
{
	Q_OBJECT
public:
	enum Mode {GameMode, CameraMode};

	LevelWindow(QWidget* parent);
	~LevelWindow();

public slots:
	void run();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
private:	
	std::shared_ptr<Level> m_level;
	std::shared_ptr<Keys> m_keys;
	QDateTime m_lastTime;
	Mode m_mode = GameMode;
	std::unique_ptr<Camera> m_camera;
	QPointer<QTimer> m_timer;
	float m_throttle = 1.0f;
};

#endif // LEVELWINDOW_H
