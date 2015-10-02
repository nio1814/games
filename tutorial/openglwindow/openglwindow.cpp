#include "openglwindow.h"

#include <qpainter.h>
#include <qcoreapplication.h>

OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QWindow(parent)
    , m_updatePending(0),m_animating(false),m_context(0),m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initialize()
{

    return;
}

void OpenGLWindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::render()
{
    if(!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}


void OpenGLWindow::renderLater()
{
    if(!m_updatePending){
        m_updatePending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
    return;
}

void OpenGLWindow::renderNow()
{
    if(!isExposed())
        return;

    bool needsInitialize = false;

    if(!m_context)
    {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();
        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if(needsInitialize)
    {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if(m_animating)
        renderLater();
}

bool OpenGLWindow::event(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::UpdateRequest:
            m_updatePending = false;
            renderNow();
            return true;
        default:
            return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if(isExposed())
        renderNow();
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;
    if(animating)
        renderLater();
}
