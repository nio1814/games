#include "mymodel.h"
#include <QApplication>
#include <qtableview.h>
#include <qtreeview.h>

#include <qitemselectionmodel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    QTreeView treeView;
    MyModel myModel(0);
    tableView.setModel(&myModel);
    tableView.show();
    /*treeView.setModel(&myModel);
    treeView.show();*/

//    QItemSelectionModel *selectionModel = tableView.selectionModel();
//    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChangedSlot(QItemSelection,QItemSelection)));

    return a.exec();
}
