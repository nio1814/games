#include "mainwindow.h"

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    gl = new GLWidget(this);
    setCentralWidget(gl);
    centralWidget()->setFocus();

	gl->restartTimer();
	while(1)
	{
		gl->process();
	}
}

MainWindow::~MainWindow()
{

}
