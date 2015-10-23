#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include "qplaintextedit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void newFile();
private:
    bool maybeSave();
    void writeSettings();

    void setCurrentFile(const QString &fileName);
    void createActions();
    void createMenus();

    QPlainTextEdit *textEdit;
    QString curFile;
    QAction *newAct;
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
