#ifndef funnyplace_widget_H
#define funnyplace_widget_H

#include "mydatabase.h"
#include <QWidget>
#include <QtSql>
#include <QStandardItem>

namespace Ui {
class funnyplace_widget;
}

class funnyplace_widget : public QWidget
{
    Q_OBJECT

public:
    explicit funnyplace_widget(QWidget *parent = nullptr);
    ~funnyplace_widget();
     void writeTable();
private:
    Ui::funnyplace_widget *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // LIST_MY_DOCUMENT_WIDGET_H
