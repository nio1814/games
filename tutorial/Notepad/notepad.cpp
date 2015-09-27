#include "notepad.h"
#include "ui_notepad.h"

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextstream.h>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_quitButton_clicked()
{
    qApp->quit();
}

void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Text files (*.txt);;c++ Files (*.cpp *.h)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void Notepad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("Text files (*.txt);;c++ Files (*.cpp *.h)"));

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file for saving"));
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        out.flush();
        file.close();
    }
}

void Notepad::on_actionQuit_triggered()
{
    on_quitButton_clicked();
}
