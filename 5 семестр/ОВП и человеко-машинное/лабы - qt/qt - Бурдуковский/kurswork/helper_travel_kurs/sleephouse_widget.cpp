#include "sleephouse_widget.h"
#include "ui_sleephouse_widget.h"

#include <QMessageBox>
#include <QAbstractItemView>
#include <QSqlQuery>

sleephouse_widget::sleephouse_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sleephouse_widget)
{
    ui->setupUi(this);
    myDataBase *mdb = new myDataBase();
    db = mdb->mydb;
    this->writeTable();
}

void sleephouse_widget::writeTable() {
    model = new QSqlTableModel();
    model->setTable("sleepHouse");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, tr("Город"));
    model->setHeaderData(2, Qt::Horizontal, tr("Адрес"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата засления"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата выселения"));
    model->setHeaderData(5, Qt::Horizontal, tr("Сколько человек"));

    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0,true);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Stretch);
}

void sleephouse_widget::on_pushButton_clicked() {//добавить новую запись
    model->sort(0, Qt::AscendingOrder);
    int size = model->rowCount();
    model->insertRow(size);
}
void sleephouse_widget::on_pushButton_2_clicked() {//сохранить изменения
        model->submitAll();
}
void sleephouse_widget::on_pushButton_3_clicked() {//отменить изменения
     model->revertAll();
}

void sleephouse_widget::on_pushButton_5_clicked() {
    //Диалоговое окно подтверждающее удаление выделенного элемента
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
sleephouse_widget::~sleephouse_widget()
{
    delete ui;
}
