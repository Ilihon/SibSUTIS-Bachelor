#ifndef CHANGE_COMMAND_WIDGET_H
#define CHANGE_COMMAND_WIDGET_H


#include <QSqlTableModel>
#include <QWidget>
#include "mydatabase.h"

namespace Ui {
class change_command_widget;
}

class change_command_widget : public QWidget
{
    Q_OBJECT

public:
    explicit change_command_widget(QWidget *parent = nullptr);
    ~change_command_widget();

signals:
    void back_to_my_command_widget();
public slots:
    void reicive_id(int id);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::change_command_widget *ui;
    int selected_id;
    QSqlTableModel *model;
    void writeTableThis();
};

#endif // CHANGE_COMMAND_WIDGET_H
