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
private:
    QOpenGLPaintDevice *m_device;

};

#endif // OPENGLWINDOW_H
