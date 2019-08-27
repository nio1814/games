#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    GLWidget *gl;
};

#endif // MAINWINDOW_H
