#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->centralWidget, SLOT(animate()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
