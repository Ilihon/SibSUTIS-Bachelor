#include "author.h"
#include "ui_author.h"

author::author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::author)
{
    ui->setupUi(this);
}

author::~author()
{
    delete ui;
}
