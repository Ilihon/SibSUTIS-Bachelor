#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMenu>
#include "mydatabase.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDataBase *mdb = new myDataBase();
    mdb->Connection();
    QMenu* pm_first = new QMenu(ui->pushButton);

    pm_first->addAction("Список ЛИЧНЫХ документов в поездку", this, SLOT(list_my_docs_menu()));
    pm_first->addAction("Список ЛИЧНЫХ вещей в поездку", this, SLOT(list_my_item_menu()));
    ui->pushButton->setMenu(pm_first);

    helloBox = new hello_box(this);
    ui->stackedWidget_2->addWidget(helloBox);

    helloBox_2 = new hello_box_2(this);
    ui->stackedWidget_2->addWidget(helloBox_2);


    list_my_docs = new List_My_Document_Widget();
    ui->stackedWidget->addWidget(list_my_docs);

    list_my_item = new list_my_item_widget();
    ui->stackedWidget->addWidget(list_my_item);

    change_list_my_item = new change_list_my_item_widget();
    ui->stackedWidget->addWidget(change_list_my_item);

    my_command = new command_widget();
    ui->stackedWidget->addWidget(my_command);

    change_command = new change_command_widget();
    ui->stackedWidget->addWidget(change_command);

    QMenu* pm_third = new QMenu(ui->pushButton_3);
    pm_third->addAction("Трансфер", this, SLOT(list_my_transfer_menu()));
    ui->pushButton_3->setMenu(pm_third);

    list_my_transfer = new transfer_widget();
    ui->stackedWidget->addWidget(list_my_transfer);

    pm_third->addAction("Ночлег", this, SLOT(list_my_sleep_house_menu()));
    ui->pushButton_3->setMenu(pm_third);

    list_my_sleep_house = new sleephouse_widget();
    ui->stackedWidget->addWidget(list_my_sleep_house);

    pm_third->addAction("Адреса по работе", this, SLOT(list_my_workplace_menu()));
    ui->pushButton_3->setMenu(pm_third);

    list_my_workplace = new workplace_widget();
    ui->stackedWidget->addWidget(list_my_workplace);

    pm_third->addAction("Досуг", this, SLOT(list_my_funnyplace_menu()));
    ui->pushButton_3->setMenu(pm_third);

    list_my_funnyplace = new funnyplace_widget();
    ui->stackedWidget->addWidget(list_my_funnyplace);

    connect(list_my_item, SIGNAL(change_press()), this, SLOT(list_my_item_menu_change()));
    connect(change_list_my_item, SIGNAL(back_to_list_my_item_widget()), this, SLOT(back_to_list_my_item()));
    connect(list_my_item, SIGNAL(send_id_selected(int)), change_list_my_item, SLOT(reicive_id(int)));
    /*--*/
    //connect(my_command, SIGNAL(change_press()), this, SLOT(my_command_change()));
    //connect(change_command, SIGNAL(back_to_my_command_widget()), this, SLOT(back_to_my_command()));
    //connect(my_command, SIGNAL(send_id_selected(int)), change_command , SLOT(reicive_id(int)));
}



void MainWindow::helloWindow() {
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::helloWindow_2() {
    ui->stackedWidget_2->setCurrentIndex(1);
}
/*-------------*/
void MainWindow::list_my_docs_menu() {
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::list_my_item_menu() {
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::list_my_item_menu_change() {
    ui->stackedWidget->setCurrentIndex(2);
}

/*-------------*/
void MainWindow::on_pushButton_2_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::my_command_change() {
    //ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::list_my_transfer_menu() {
ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::list_my_sleep_house_menu() {
ui->stackedWidget->setCurrentIndex(6);
}
void MainWindow::list_my_funnyplace_menu() {
ui->stackedWidget->setCurrentIndex(8);
}
void MainWindow::list_my_workplace_menu() {
    ui->stackedWidget->setCurrentIndex(7);
}
/*-------------*/
void MainWindow::back_to_list_my_item() {
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::back_to_my_command() {
    ui->stackedWidget->setCurrentIndex(3);
}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox ms;

    QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
    QAbstractButton *no = ms.addButton("Нет",QMessageBox::NoRole);
    ms.setText("Уверены?");
    ms.exec();
    if(ms.clickedButton() == yes) event->accept();

}


