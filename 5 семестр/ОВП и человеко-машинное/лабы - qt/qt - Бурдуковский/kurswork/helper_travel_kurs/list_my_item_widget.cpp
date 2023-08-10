#include "list_my_item_widget.h"
#include "ui_list_my_item_widget.h"
#include <QMessageBox>
#include <QDebug>
list_my_item_widget::list_my_item_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_my_item_widget)
{
    ui->setupUi(this);
    myDataBase *mdb = new myDataBase();
    db = mdb->mydb;
    this->writeTable();

    //Сигнал смены меню
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SIGNAL(change_press()));
}

void list_my_item_widget::writeTable() {
    model = new QSqlTableModel();
    model->setTable("SelfItem");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, tr("Название документа"));
    model->setHeaderData(2, Qt::Horizontal, tr("Пометка:"));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
}

void list_my_item_widget::on_pushButton_clicked()//Добавить новый
{
    model->sort(0, Qt::AscendingOrder);
    int size = model->rowCount();
    model->insertRow(size);
}

void list_my_item_widget::on_pushButton_2_clicked()//Сохранить изменения
{
    model->submitAll();
}

void list_my_item_widget::on_pushButton_3_clicked()//Отменить изменения
{
    model->revertAll();
}

void list_my_item_widget::on_pushButton_4_clicked()//изменить
{
    int row = 0;
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if(select->hasSelection()) {
        row = select->currentIndex().row();
        qDebug() << "rowIF" <<row;
    }
    row = ui->tableView->model()->index(row,0).data().toInt();
    qDebug() << "rowTable" << row;
    emit send_id_selected(row);
}

void list_my_item_widget::on_pushButton_5_clicked()//удалить
{
    //Диалоговое окно подтверждающее удаление выделенного элемента
    QMessageBox ms;

    if(ui->tableView->selectionModel()->hasSelection()) {
    QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
    QAbstractButton *no = ms.addButton("Нет",QMessageBox::NoRole);




    ms.setText("Уверены, что хотите удалить выбранную запись?");
    ms.setIcon(QMessageBox::Warning);
    ms.exec();
    if(ms.clickedButton() == yes)
    {
       int row;
       int id;
       QItemSelectionModel *select = ui->tableView->selectionModel();
       if(select->hasSelection()){
           row = select->currentIndex().row();
           model->removeRow(row);
           model->submitAll();
           id = ui->tableView->model()->index(row,0).data().toInt();
           QSqlTableModel *mod = new QSqlTableModel();
           mod->setTable("ListSelfItem");
           int n = mod->rowCount();
           for (int i = 0; i<n; i++){
               if(mod->index(i,2).data().toInt() == id){
                   mod->removeRow(i);
                   i--;
                   n--;
               }
           }
           mod->submitAll();
           writeTable();
       }
   }
    } else {
        ms.setText("Вы не выбрали нужную ячейки или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::ApplyRole);
        ms.exec();
    }
}
list_my_item_widget::~list_my_item_widget()
{
    delete ui;
}
