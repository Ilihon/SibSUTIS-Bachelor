#include "change_list_my_item_widget.h"
#include "ui_change_list_my_item_widget.h"
#include "list_my_document_widget.h"
#include "list_my_item_widget.h"

#include <QMessageBox>
#include <QSqlTableModel>
#include <iostream>

change_list_my_item_widget::change_list_my_item_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_list_my_item_widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(back_to_list_my_item_widget()));
}

change_list_my_item_widget::~change_list_my_item_widget()
{
    delete ui;
}

void change_list_my_item_widget::reicive_id(int id) {
    QString q = QString::number(id);
    //сохраняем id
    selected_id = id;
    writeTableThis();
}

void change_list_my_item_widget::writeTableThis() {
   QString selected;
    selected.setNum(selected_id);
    model = new QSqlTableModel();
    model->setTable("ListSelfItem");
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    QSqlTableModel *md = new QSqlTableModel();
    md->setTable("SelfItem");
    md->select();
    md->setFilter("id = " + selected);

    QString name;
   // qDebug() << selected_id;
    qDebug() << selected;
    qDebug() << md->rowCount();
    qDebug() << md->index(md->rowCount()-1,1);
    name = md->index(md->rowCount()-1,1).data().toString();
    ui->label->setText(name);

    model->setHeaderData(1, Qt::Horizontal, tr("Список"));
    model->select();
    model->setFilter("idListThings = " + selected);

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(2, true);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void change_list_my_item_widget::on_pushButton_2_clicked() {
    QString newThing = ui->lineEdit->text();
    if(newThing!="") {
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1,1), newThing);
        QString si;
        si.setNum(selected_id);
        model->setData(model->index(model->rowCount() - 1,2), si);
        model->submitAll();
        writeTableThis();
    }
}

void change_list_my_item_widget::on_pushButton_clicked() {
    list_my_item_widget *main = new list_my_item_widget;
    main->writeTable();
}

void change_list_my_item_widget::on_pushButton_3_clicked() {
    int row;
    int id;
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if(select->hasSelection()) {
        row = select->currentIndex().row();
        model->removeRow(row);
        model->submitAll();
        writeTableThis();
    }
}
