#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

public slots:
//    void setCurrentGLWidget();
//    void rotateOneStep();

private:
    enum {
        NumRows = 2,
        NumColumns = 3
    };

    GLWidget* glWidgets[NumRows][NumColumns];
    GLWidget* currentGLWidget;
};

#endif // WINDOW_H
