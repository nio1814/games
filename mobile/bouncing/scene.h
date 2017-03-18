#ifndef SCENE_H
#define SCENE_H

#include <QQuickItem>
#include "ellipse.h"

class QOpenGLShaderProgram;
class SceneRenderer;

class Scene : public QQuickItem
{
    Q_OBJECT
public:
    Scene();

	int numEllipses();
	void render(QOpenGLShaderProgram* program);

signals:
public slots:
	void sync();
	void cleanup();
private slots:
	void handleWindowChanged(QQuickWindow* win);
private:
	Ellipses m_ellipses;
	SceneRenderer* m_renderer;
};

#endif // SCENE_H
