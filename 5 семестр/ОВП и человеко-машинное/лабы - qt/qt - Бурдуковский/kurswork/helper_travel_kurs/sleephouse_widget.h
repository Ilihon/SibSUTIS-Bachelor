#ifndef sleephouse_widget_H
#define sleephouse_widget_H

#include "mydatabase.h"
#include <QWidget>
#include <QtSql>
#include <QStandardItem>

namespace Ui {
class sleephouse_widget;
}

class sleephouse_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sleephouse_widget(QWidget *parent = nullptr);
    ~sleephouse_widget();
     void writeTable();
private:
    Ui::sleephouse_widget *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // LIST_MY_DOCUMENT_WIDGET_H
