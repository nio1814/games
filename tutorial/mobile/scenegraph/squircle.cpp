#include "squircle.h"

#include <qquickwindow.h>
#include "squirclerenderer.h"

Squircle::Squircle() : m_t(0), m_renderer(NULL)
{
	connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

qreal Squircle::t() const
{
	return m_t;
}

void Squircle::setT(qreal t)
{
	if(t!=m_t)
	{
		m_t = t;
		emit tChanged();
		if(window())
			window()->update();
	}

	return;
}

void Squircle::handleWindowChanged(QQuickWindow *win)
{
	if(win)
	{
		connect(win, SIGNAL(beforeRendering()), this, SLOT(sync()));
		connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()));
		win->setClearBeforeRendering(false);
	}
}

void Squircle::sync()
{
	if(!m_renderer)
	{
		m_renderer = new SquircleRenderer;
		connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()));
	}
	m_renderer->setViewportSize(window()->size()*window()->devicePixelRatio());
	m_renderer->setT(m_t);

	return;
}

void Squircle::cleanup()
{
	if(m_renderer)
	{
		delete m_renderer;
		m_renderer = NULL;
	}

	return;
}
