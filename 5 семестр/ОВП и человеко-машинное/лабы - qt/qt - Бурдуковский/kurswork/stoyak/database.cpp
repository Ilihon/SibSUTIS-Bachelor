#include "database.h"

database::database()
{

}

void database::Connection(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:\\labs\\qt\\kurswork\\stoyak\\Base\\ip813.db");
    if(!mydb.open()){
        QMessageBox::warning(0, QObject::tr("Ошибка"), QObject::tr("Ошибка подключения к базе!!!"));
    }
    else {
        qDebug() << ("Connected");
    }
}
