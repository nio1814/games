#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <qtimer.h>

const int ROWS = 2;
const int COLS = 3;

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MyModel(QObject *parent);
    ~MyModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QString m_gridData[ROWS][COLS];
signals:
    void editCompleted(const QString&);
private slots:
    void timerHit();

public:
    QTimer* timer;
};

#endif // MYMODEL_H
