#include "connection.h"

#include <QtSql/qsqldatabase.h>

static bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(":memory");
}
