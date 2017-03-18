#include "scene.h"

#include "ellipse.h"
#include "scenerenderer.h"
#include <qquickwindow.h>

Scene::Scene() : m_renderer(NULL)
{
	connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void Scene::handleWindowChanged(QQuickWindow *win)
{
	if(win)
	{
		connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()));
		connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()));
		win->setClearBeforeRendering(false);
	}
	return;
}

void Scene::sync()
{
	if(!m_renderer)
	{
		m_renderer = new SceneRenderer;
		connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()));
	}
	m_renderer->setViewportSize(window()->size()*window()->devicePixelRatio());
}

void Scene::cleanup()
{
	if(m_renderer)
	{
		delete m_renderer;
		m_renderer = NULL;
	}

	return;
}

void Scene::render(QOpenGLShaderProgram *program)
{
	m_ellipses.draw(program);

	return;
}
