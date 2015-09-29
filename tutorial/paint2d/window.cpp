#include "window.h"
#include "widget.h"

#include "qgridlayout.h"
#include "qtimer.h"
#include "qlabel.h"

Window::Window()
{
    Widget *native = new Widget(&helper, this);
    QLabel *nativeLabel = new QLabel(tr("native"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0,0);
//    layout->addWidget(nativeLabel, 1, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
    timer->start(50);
}

