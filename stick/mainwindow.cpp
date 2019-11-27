#include "mainwindow.h"

#include "glwidget.h"

#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	gl = new GLWidget(this);
	
	setCentralWidget(gl);
	centralWidget()->setFocus();
	
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), centralWidget(), SLOT(animate()));
    timer->start(30);
}

MainWindow::~MainWindow()
{

}
