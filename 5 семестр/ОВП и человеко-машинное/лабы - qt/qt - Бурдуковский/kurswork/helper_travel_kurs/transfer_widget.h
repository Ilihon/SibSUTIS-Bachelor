#ifndef transfer_widget_H
#define transfer_widget_WIDGET_H

#include "mydatabase.h"
#include <QWidget>
#include <QTSql>
#include <QStandardItem>

namespace Ui {
class transfer_widget;
}

class transfer_widget : public QWidget
{
    Q_OBJECT

public:
    explicit transfer_widget(QWidget *parent = nullptr);
    ~transfer_widget();
     void writeTable();
private:
    Ui::transfer_widget *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // LIST_MY_DOCUMENT_WIDGET_H
