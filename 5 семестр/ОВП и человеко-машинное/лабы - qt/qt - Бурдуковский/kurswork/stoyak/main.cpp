#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QFile styleF;

//    styleF.setFileName(a.applicationDirPath() + "/style.css");
//    styleF.open(QFile::ReadOnly);
//    QString qssStr = styleF.readAll();

//    qApp->setStyleSheet(qssStr);
    w.show();

    return a.exec();
}
