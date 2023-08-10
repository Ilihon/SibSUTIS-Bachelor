#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    database *mdb = new database();
    mdb->Connection();

    ui->setupUi(this);
    form = new add();
    form2 = new date();
    ui->stackedWidget->setCurrentIndex(0);
    this->resize(370, 250);
    this->setFixedHeight(250);
    this->setFixedWidth(370);
    db = mdb->mydb;
    this->writeTable();
    qDebug() << QDir::currentPath();
    connect(ui->start, SIGNAL(clicked()), this, SLOT(on_start_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), form, SLOT(show()));
    connect(ui->pushButton_2, SIGNAL(clicked()), form2, SLOT(show()));
    connect(form2, SIGNAL(sendData(QString)), this, SLOT(recieveData(QString)));
    connect(form, SIGNAL(sendData(QString)), this, SLOT(recieveData(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeTable(){
    model = new QSqlTableModel();
    model->setTable("ip813");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(1, Qt::Horizontal, tr("Студент"));
    model->setHeaderData(2, Qt::Horizontal, tr("Отстающий?"));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0,true);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
}

void MainWindow::on_start_clicked()
{
    if (ui->fio->text().trimmed() == "" )
    {

        ui->error->setText("Введите ФИО!");
    }
    else
    {
        this->resize(1200, 800);
        this->setFixedHeight(800);
        this->setFixedWidth(1200);
        ui->stackedWidget->setCurrentIndex(1);
        ui->prepod->setText(ui->fio->text());
        ui->error->clear();
        this->writeTable();
    }

}

void MainWindow::recieveData(QString str)
{
    ui->prepod->setText(str);
    qDebug() << str;
}

void MainWindow::on_exit_clicked()
{
    this->resize(370, 250);
    this->setFixedHeight(250);
    this->setFixedWidth(370);
    ui->stackedWidget->setCurrentIndex(0);
}

