#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QWidget>

class TableEditor : public QWidget
{
	Q_OBJECT

public:
	TableEditor(const QString &tableName, QWidget *parent = 0);
	~TableEditor();
};

#endif // TABLEEDITOR_H
