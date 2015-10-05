#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class GLWidget;
class QSlider;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    QSlider* createSlider();
    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif // WINDOW_H
