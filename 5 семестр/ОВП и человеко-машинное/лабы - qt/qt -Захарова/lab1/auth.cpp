#include "auth.h"
#include "ui_auth.h"

auth::auth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);

}

auth::~auth()
{
    delete ui;
}
