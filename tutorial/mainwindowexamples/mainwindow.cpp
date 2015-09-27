#include "mainwindow.h"

#include <qsettings.h>

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit();
}

MainWindow::~MainWindow()
{
    delete textEdit;
}

bool MainWindow::maybeSave()
{
    return true;
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "ApplicationExample");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if(curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::newFile()
{
    if(maybeSave())
    {
        textEdit->clear();
        setCurrentFile("");
    }
}
