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
private:
    bool maybeSave();
    void writeSettings();
    void newFile();
    void setCurrentFile(const QString &fileName);

    QPlainTextEdit *textEdit;
    QString curFile;
};

#endif // MAINWINDOW_H
