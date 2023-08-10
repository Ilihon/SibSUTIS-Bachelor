#include "widget_burdukovskiy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget_burdukovskiy w;
    w.show();

    return a.exec();
}
