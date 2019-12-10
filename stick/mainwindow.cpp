#include "mainwindow.h"

#include "window.h"

#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  window = QPointer<Window>(new Window(this));
	
  setCentralWidget(window);
	centralWidget()->setFocus();
	
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), centralWidget(), SLOT(animate()));
    timer->start(30);
}

MainWindow::~MainWindow()
{

}
