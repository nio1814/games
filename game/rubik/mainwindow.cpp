#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	gl = new GLWidget(this);
	setCentralWidget(gl);
	centralWidget()->setFocus();
}

MainWindow::~MainWindow()
{
	delete ui;
}
