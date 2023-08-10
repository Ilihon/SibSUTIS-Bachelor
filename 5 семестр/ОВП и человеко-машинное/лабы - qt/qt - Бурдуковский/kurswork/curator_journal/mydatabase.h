#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QMessageBox>
#include <QtSql/QSqlDatabase>

class myDataBase
{
public:
    myDataBase();
    QSqlDatabase mydb;
    void Connection();
};

#endif // MYDATABASE_H
