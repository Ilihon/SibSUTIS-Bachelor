#ifndef COMMAND_WIDGET_H
#define COMMAND_WIDGET_H

#include "mydatabase.h"

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QWidget>
#include <QStandardItem>

namespace Ui {
class command_widget;
}

class command_widget : public QWidget
{
    Q_OBJECT

public:
    explicit command_widget(QWidget *parent = nullptr);
    ~command_widget();
    void writeTable();

private:
    Ui::command_widget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

signals:
    void send_id_selected(int);
    void change_press();
};

#endif // COMMAND_WIDGET_H
