#include <QApplication>
#include "StartDialogBurdukovsky.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialogBurdukovsky StartDialogBurdukovsky;
    StartDialogBurdukovsky.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
