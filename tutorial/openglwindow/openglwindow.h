#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <qwindow.h>
#include <qopenglfunctions.h>
#include <qopenglpaintdevice.h>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

    virtual void initialize();

    virtual void render();
    virtual void render(QPainter *painter);

    void setAnimating(bool animating);
protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;


private:
    QOpenGLPaintDevice *m_device;
    QOpenGLContext *m_context;

    bool m_updatePending;
    bool m_animating;

public slots:
    void renderLater();
    void renderNow();
};

#endif // OPENGLWINDOW_H
