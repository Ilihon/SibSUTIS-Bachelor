#ifndef LIST_MY_ITEM_WIDGET_H
#define LIST_MY_ITEM_WIDGET_H

#include "mydatabase.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QWidget>
#include <QStandardItem>

namespace Ui {
class list_my_item_widget;
}

class list_my_item_widget : public QWidget
{
    Q_OBJECT

public:
    explicit list_my_item_widget(QWidget *parent = nullptr);
    ~list_my_item_widget();
    void writeTable();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::list_my_item_widget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;

signals:
    void send_id_selected(int);
    void change_press();
};

#endif // LIST_MY_ITEM_WIDGET_H
