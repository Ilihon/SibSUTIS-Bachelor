#include "add.h"
#include "ui_add.h"

add::add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
}

add::~add()
{
    delete ui;
}

void add::on_pushButton_clicked()
{
    QString st = ui->lineEdit->text();
    if (st.trimmed() == "")
        QMessageBox::information(0, "Ошибка", "Поле не заполнено");
    else
        emit sendData(st);
    close();
}

void add::on_pushButton_2_clicked()
{
    close();
}
