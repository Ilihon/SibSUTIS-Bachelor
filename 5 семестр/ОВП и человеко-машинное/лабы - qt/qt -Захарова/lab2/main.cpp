#include <QApplication>
#include <StartDialogZaharowa.h>
//#include <inputdialogzaharowa.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    StartDialogZaharowa startDialogZaharowa;
    startDialogZaharowa.show();
 //   MainWindow w;
 //   w.show();

    return a.exec();
}
