#include "funnyplace_widget.h"
#include "ui_funnyplace_widget.h"

#include <QMessageBox>
#include <QAbstractItemView>
#include <QSqlQuery>

funnyplace_widget::funnyplace_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::funnyplace_widget)
{
    ui->setupUi(this);
    myDataBase *mdb = new myDataBase();
    db = mdb->mydb;
    this->writeTable();
}

void funnyplace_widget::writeTable() {
    model = new QSqlTableModel();
    model->setTable("funnyplace");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, tr("Что делаем?"));
    model->setHeaderData(2, Qt::Horizontal, tr("Адрес"));;

    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0,true);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
}

void funnyplace_widget::on_pushButton_clicked() {//добавить новую запись
    model->sort(0, Qt::AscendingOrder);
    int size = model->rowCount();
    model->insertRow(size);
}
void funnyplace_widget::on_pushButton_2_clicked() {//сохранить изменения
        model->submitAll();
}
void funnyplace_widget::on_pushButton_3_clicked() {//отменить изменения
     model->revertAll();
}

void funnyplace_widget::on_pushButton_5_clicked() {
    //Диалоговое окно подтверждающее удаление выделенного элемента
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
funnyplace_widget::~funnyplace_widget()
{
    delete ui;
}
