#include "date.h"
#include "ui_date.h"

date::date(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date)
{
    ui->setupUi(this);

}

date::~date()
{
    delete ui;
}

void date::on_pushButton_clicked()
{
    QString st = ui->dateEdit->text();
    emit sendData(st);
    close();
}

void date::on_pushButton_2_clicked()
{
    close();
}
