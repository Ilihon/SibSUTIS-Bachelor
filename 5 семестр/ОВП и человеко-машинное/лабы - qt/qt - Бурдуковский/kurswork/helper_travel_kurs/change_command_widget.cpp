#include "change_command_widget.h"
#include "ui_change_command_widget.h"

#include "list_my_document_widget.h"
#include "list_my_item_widget.h"
#include "command_widget.h"

#include <QMessageBox>
#include <QSqlTableModel>
#include <iostream>

change_command_widget::change_command_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_command_widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(back_to_my_command_widget()));

}

void change_command_widget::reicive_id(int id) {
    QString q = QString::number(id);
    selected_id = id;
    writeTableThis();
}

void change_command_widget::writeTableThis() {
    QString selected;
     selected.setNum(selected_id);
     model = new QSqlTableModel();
     model->setTable("myCommand");
     model->setEditStrategy(QSqlTableModel::OnRowChange);

     QSqlTableModel *md = new QSqlTableModel();
     md->setTable("HumanDocument");
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

void change_command_widget::on_pushButton_clicked() {
    command_widget *main = new command_widget;
    main->writeTable();
}

void change_command_widget::on_pushButton_2_clicked() {
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


void change_command_widget::on_pushButton_3_clicked() {
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

change_command_widget::~change_command_widget()
{
    delete ui;
}
