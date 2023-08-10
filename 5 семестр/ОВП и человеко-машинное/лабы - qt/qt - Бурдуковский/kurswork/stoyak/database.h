#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

class database
{
public:
    database();
    QSqlDatabase mydb;
    void Connection();
};

#endif // DATABASE_H
