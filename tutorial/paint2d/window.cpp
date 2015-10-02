#include "qgridlayout.h"
#include "qtimer.h"
#include "qlabel.h"

#include "window.h"
#include "widget.h"
#include "glwidget.h"

Window::Window()
{
    Widget *native = new Widget(&helper, this);
    QLabel *nativeLabel = new QLabel(tr("native"));

    GLWidget *openGL = new GLWidget(&helper, this);
    QLabel *openGLLabel = new QLabel(tr("OpenGL"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native,0,0);
    layout->addWidget(openGL,0,1);
    layout->addWidget(nativeLabel, 1, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
    connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
    timer->start(50);
}

