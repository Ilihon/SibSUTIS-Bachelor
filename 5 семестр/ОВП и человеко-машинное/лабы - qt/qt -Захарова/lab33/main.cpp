#include "sdiprogramzaharowa.h"
#include <QApplication>


void LoadModules(QSplashScreen* psplash){
    QTime time;
    time.start();
    for(int i=0;i<100;){
        if (time.elapsed()>40){
            time.start();
            i++;
        }
        QString str;
        str.size();
        psplash->showMessage("Loading modules:"
                             + QString::number(i)+"%",
                             Qt::AlignCenter | Qt::AlignBottom,
                             Qt::white
                             );
        qApp->processEvents();
    }

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap("1.JPG"));
    splash.show();
    SDIProgramZaharowa w;
    LoadModules(&splash);
    splash.finish(&w);
    w.show();
    return a.exec();
}
