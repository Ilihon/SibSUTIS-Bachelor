#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "burdukovskiy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void sendData(QString str);

private slots:
    void onButtonSend();
    void on_pushButton_clicked();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    burdukovskiy *myform;
};

#endif // MAINWINDOW_H
