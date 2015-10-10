#include "window.h"

#include "glwidget.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout* mainLayout = new QGridLayout;

    for (int i=0; i<NumRows; i++)
    {
        for (int j=0; j<NumColumns; j++)
        {
            glWidgets[i][j] = new GLWidget(0,0);
            mainLayout->addWidget(glWidgets[i][j], i, j);
            connect(glWidgets[i][j], SIGNAL(clicked()), this, SLOT(setCurrentGLWidget()));
        }
    }
    setLayout(mainLayout);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    timer->start(20);
}

Window::~Window()
{

}
