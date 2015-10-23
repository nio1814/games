#include "remoteselector.h"
#include "ui_remoteselector.h"

RemoteSelector::RemoteSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteSelector)
{
    ui->setupUi(this);
}

RemoteSelector::~RemoteSelector()
{
    delete ui;
}
