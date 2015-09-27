#include "mymodel.h"

#include <qdebug.h>
#include <qfont.h>
#include <qbrush.h>
#include <QTime>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    timer->start();
}

MyModel::~MyModel()
{
    delete timer;
}

int MyModel::rowCount(const QModelIndex &) const
{
    return 2;
}

int MyModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

    switch(role)
    {
        case Qt::DisplayRole:
            if(col==1)
            {
                if(row==0)
                    return QString("<--left");
                else if(row==1)
                    return QString("right-->");
            }
            else if(col==0 && row==0)
                    return QTime::currentTime().toString();

//            return QString("Row%1, Column%2").arg(row+1).arg(col+1);
                return m_gridData[row][col];
            break;
        case Qt::FontRole:
            if(row==0 && col==0)
            {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }
            break;
        case Qt::BackgroundRole:
            if(row==1 && col==2)
            {
                QBrush greenBackground(Qt::green);
                return greenBackground;
            }
            break;
    case Qt::CheckStateRole:
        if(row==1 && col==0)
            return Qt::Checked;
    }

    return QVariant();
}


QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole && orientation==Qt::Horizontal)
    {
        switch(section)
        {
            case 0:
                return QString("first");
                break;
            case 1:
                return QString("second");
                break;
            case 2:
                return QString("third");
                break;
        }
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::EditRole)
    {
        m_gridData[index.row()][index.column()] = value.toString();
        QString result;
        for(int row=0; row<ROWS; row++)
        {
            for(int col=0; col<COLS; col++)
            {
                result += m_gridData[row][col] + " ";
            }
        }
        emit editCompleted(result);
    }
    return true;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void MyModel::timerHit()
{
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft);
}
