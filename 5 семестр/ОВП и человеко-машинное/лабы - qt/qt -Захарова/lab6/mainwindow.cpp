#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zaharowa.h"
#include <QFileDialog>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: blue;");
    myform=new Zaharowa();
    connect(ui->pushButton,SIGNAL(clicked()),myform, SLOT(show()));
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(onButtonSend()));
    connect(this,SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename= QFileDialog::getOpenFileName(nullptr,"Выберите изображение",QDir::currentPath(),"*.png *.jpg *.gif *jpeg");
 //   ui->lineEdit_3->setText(filename);
    QImage image(filename);
    ui->label_5->setPixmap(QPixmap::fromImage(image));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

QString st=ui->lineEdit_3->text()+"*"+ui->lineEdit->text()+"\n"+ui->lineEdit_2->text()+"\n"+
        ui->dateEdit->text()+"\n";
if(ui->radioButton->isChecked()==true) st="\nпол: мужской";
else  st+="\nпол:женский";
if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()==""){
    QMessageBox::information(nullptr,"Ошибка","некоторые поля не заполнены");
}
else {
    emit sendData(st);
}
}
