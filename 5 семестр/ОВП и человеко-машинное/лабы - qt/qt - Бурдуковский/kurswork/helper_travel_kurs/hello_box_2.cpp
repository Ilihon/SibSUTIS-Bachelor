#include "hello_box_2.h"
#include "ui_hello_box_2.h"

hello_box_2::hello_box_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hello_box_2)
{
    ui->setupUi(this);
}

hello_box_2::~hello_box_2()
{
    delete ui;
}
