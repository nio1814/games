#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cubewindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_cubeWindow = new CubeWindow(this);
	setCentralWidget(m_cubeWindow);
	centralWidget()->setFocus();
}

MainWindow::~MainWindow()
{
	delete ui;
}
