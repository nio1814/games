#include "window.h"

#include <QHBoxLayout>

#include "glwidget.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    glWidget = new GLWidget;
    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(xSlider);
    mainLayout->addWidget(ySlider);
    mainLayout->addWidget(zSlider);
    setLayout(mainLayout);
}

Window::~Window()
{

}

QSlider* Window::createSlider()
{
    int scale = 16;
    QSlider* slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360*scale);
    slider->setSingleStep(scale);
    slider->setPageStep(15*scale);
    slider->setTickInterval(15*scale);
    slider->setTickPosition(QSlider::TicksRight);

    return slider;

}
