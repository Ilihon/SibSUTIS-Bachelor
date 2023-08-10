#include "mydatabase.h"

myDataBase::myDataBase()
{

}

void myDataBase::Connection(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:\\labs\\qt\\kurswork\\curator_journal\\Base\\DataBase.db");
    if(!mydb.open()){
        QMessageBox::warning(0, QObject::tr("Ошибка"), QObject::tr("Ошибка подключения к базе!!!"));
    }
}
