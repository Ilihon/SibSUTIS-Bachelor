#ifndef CHANGE_LIST_MY_ITEM_WIDGET_H
#define CHANGE_LIST_MY_ITEM_WIDGET_H

#include <QSqlTableModel>
#include <QWidget>
#include "mydatabase.h"

namespace Ui {
class change_list_my_item_widget;
}

class change_list_my_item_widget : public QWidget
{
    Q_OBJECT

public:
    explicit change_list_my_item_widget(QWidget *parent = nullptr);
    ~change_list_my_item_widget();

private:
    Ui::change_list_my_item_widget *ui;
    int selected_id;
    QSqlTableModel *model;
    void writeTableThis();

signals:
    void back_to_list_my_item_widget();

public slots:
    void reicive_id(int id);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // CHANGE_LIST_MY_ITEM_WIDGET_H
