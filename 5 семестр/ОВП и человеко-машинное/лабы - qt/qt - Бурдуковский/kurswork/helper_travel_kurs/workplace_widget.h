#ifndef workplace_widget_H
#define workplace_widget_H

#include "mydatabase.h"
#include <QWidget>
#include <QtSql>
#include <QStandardItem>

namespace Ui {
class workplace_widget;
}

class workplace_widget : public QWidget
{
    Q_OBJECT

public:
    explicit workplace_widget(QWidget *parent = nullptr);
    ~workplace_widget();
     void writeTable();
private:
    Ui::workplace_widget *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // LIST_MY_DOCUMENT_WIDGET_H
