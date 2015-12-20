#include "scene.h"

#include "ellipse.h"
#include "scenerenderer.h"

Scene::Scene() : m_renderer(NULL)
{
	connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void Scene::handleWindowChanged(QQuickWindow *win)
{
	return;
}

void Scene::render(QOpenGLShaderProgram *program)
{
	m_ellipses.draw(program);

	return;
}
