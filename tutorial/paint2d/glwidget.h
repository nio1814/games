#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>

class Helper;

class GLWidget : public QGLWidget
{
	Q_OBJECT
public:
	GLWidget(Helper *helper, QWidget *parent);

signals:

public slots:
private:
	Helper *helper;
};

#endif // GLWIDGET_H
