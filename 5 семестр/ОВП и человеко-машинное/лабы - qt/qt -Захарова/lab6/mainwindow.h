#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "zaharowa.h"


#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Zaharowa *myform;
    Ui::MainWindow *ui;
signals:
    void sendData(QString str);
private slots:
   // void onButtonSend();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
