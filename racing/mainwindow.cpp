#include "mainwindow.h"

#include "glwidget.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    gl = new GLWidget(this);
    setCentralWidget(gl);
    centralWidget()->setFocus();

//	gl->restartTimer();
//	while(1)
//	{
//		gl->process();
//	}
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), gl, SLOT(process()));
	timer->start(5);
}

MainWindow::~MainWindow()
{

}
