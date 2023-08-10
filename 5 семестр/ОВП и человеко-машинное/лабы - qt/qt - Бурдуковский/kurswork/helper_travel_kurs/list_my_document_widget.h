#ifndef LIST_MY_DOCUMENT_WIDGET_H
#define LIST_MY_DOCUMENT_WIDGET_H

#include "mydatabase.h"
#include <QWidget>
#include <QTSql>
#include <QStandardItem>

namespace Ui {
class List_My_Document_Widget;
}

class List_My_Document_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit List_My_Document_Widget(QWidget *parent = nullptr);
    ~List_My_Document_Widget();
     void writeTable();
private:
    Ui::List_My_Document_Widget *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // LIST_MY_DOCUMENT_WIDGET_H
