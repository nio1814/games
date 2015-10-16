#ifndef REMOTESELECTOR_H
#define REMOTESELECTOR_H

#include <QDialog>

namespace Ui {
class RemoteSelector;
}

class RemoteSelector : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteSelector(QWidget *parent = 0);
    ~RemoteSelector();

private:
    Ui::RemoteSelector *ui;
};

#endif // REMOTESELECTOR_H
