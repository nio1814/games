#include "mainwindow.h"

#include "window.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)

{
  this->window = new Window(this);
    setCentralWidget(this->window);
    centralWidget()->setFocus();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this->window, SLOT(process()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
}
