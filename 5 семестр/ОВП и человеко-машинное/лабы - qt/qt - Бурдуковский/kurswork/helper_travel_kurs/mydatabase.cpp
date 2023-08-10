#include "mydatabase.h"
#include <QMessageBox>

myDataBase::myDataBase()
{

}

void myDataBase::Connection(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
   // mydb.setDatabaseName("C:\\DataBase.db");
    mydb.setDatabaseName("D:\\labs\\qt\\kurswork\\helper_travel_kurs\\BaseData\\BaseData.db");
    if(!mydb.open()){
        QMessageBox::warning(0, QObject::tr("Ошибка"),
                                     QObject::tr("Ошибка подключения к базе!!!"));
    }
}
