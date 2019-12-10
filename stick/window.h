#ifndef WINDOW_H
#define WINDOW_H

#include "simulation.h"

#include "glwidget.h"

class Window : public GLWidget
{
    Q_OBJECT
public:
    Window(QWidget *parent=0);
    ~Window(){};
protected:
    void initializeGL();
    void paintGL();
public slots:
    void animate();
private:
    Simulation simulation;
    qint64 previousRunTime;
};

#endif
