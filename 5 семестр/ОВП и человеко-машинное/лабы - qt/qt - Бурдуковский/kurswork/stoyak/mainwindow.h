#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "add.h"
#include "date.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeTable();

private slots:
    void on_start_clicked();

    void on_exit_clicked();

    void recieveData(QString str);


private:
    add *form;
    date *form2;
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
