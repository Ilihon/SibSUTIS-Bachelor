#include "main_widget.h"
#include <QApplication>
#include <QTime>
#include <QFile>
#include<QSplashScreen>


void LoadModules(QSplashScreen* psplash){
    QTime time;
    time.start();
    for(int i=0; i<100;){
        if(time.elapsed()>20){
            time.start();
            i++;
        }
        QString str;
        str.size();
        psplash->showMessage("Загрузка приложения:"+QString::number(i)+"%",Qt::AlignCenter | Qt::AlignBottom, Qt::white);
        qApp->processEvents();
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_Widget w;

    //Заставка
    QSplashScreen splash(QPixmap("D:\\labs\\qt\\kurswork\\curator_journal\\Base\\favicon.png"));
    splash.show();
    LoadModules(&splash);
    splash.finish(&w);
    w.setWindowIcon(QIcon("D:\\labs\\qt\\kurswork\\curator_journal\\Base\\favicon.png"));
    //w.setWindowIcon(favicon);
    //css файл
    QFile file("style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    w.show();
    return a.exec();
}
