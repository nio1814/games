#include "mainwindow.h"

#include <qsettings.h>
#include <qaction.h>
#include <qmenubar.h>

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit();
    setCentralWidget(textEdit);

    createActions();
    createMenus();
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

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":images/new.png"), tr("new"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addSeparator();
}
