#include "mainwindow.h"

#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gl = new GLWidget(this);
    gl->setFocus();
}

MainWindow::~MainWindow()
{

}
