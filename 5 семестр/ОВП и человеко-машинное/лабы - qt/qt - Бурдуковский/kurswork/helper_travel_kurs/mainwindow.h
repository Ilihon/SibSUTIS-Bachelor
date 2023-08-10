#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <list_my_document_widget.h>

#include <list_my_item_widget.h>
#include <change_list_my_item_widget.h>

#include <command_widget.h>
#include <change_command_widget.h>

#include <transfer_widget.h>
#include <sleephouse_widget.h>
#include <funnyplace_widget.h>
#include <workplace_widget.h>
#include "hello_box.h"
#include "hello_box_2.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void list_my_docs_menu();
    void list_my_item_menu();

    void list_my_transfer_menu();
    void list_my_sleep_house_menu();
    void list_my_funnyplace_menu();
    void list_my_workplace_menu();
    //функция для открытия окна изменения во втором виджете
    void list_my_item_menu_change();
    void back_to_list_my_item();//выходи из окна изменения списков второго виджета

    void my_command_change();
    void back_to_my_command();

    void helloWindow();
    void helloWindow_2();
    //слоты для подменю ЛИЧНЫХ ДОКОВ


    void on_pushButton_2_clicked();
   // void on_exit_clicked();
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    List_My_Document_Widget *list_my_docs;

    list_my_item_widget *list_my_item;
    change_list_my_item_widget *change_list_my_item;

    command_widget *my_command;
    change_command_widget *change_command;

    transfer_widget *list_my_transfer;
    sleephouse_widget *list_my_sleep_house;

    funnyplace_widget* list_my_funnyplace;
    workplace_widget* list_my_workplace;
    hello_box *helloBox;
    hello_box_2 *helloBox_2;
};
#endif // MAINWINDOW_H
