#include "mainwindow.h"

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	gl = new GLWidget(this);
	
	setCentralWidget(gl);
	centralWidget()->setFocus();
	
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), gl, SLOT(animate()));
    timer->start(50);
}

MainWindow::~MainWindow()
{

}
