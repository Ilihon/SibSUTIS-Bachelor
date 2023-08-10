#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myform = new burdukovskiy();
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(onButtonSend()));
    connect(this, SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0, "Выберите изображение",
                                    QDir::currentPath(), "*.png *.jpg *.gif *.jpeg");
    ui->lineEdit_4->setText(filename);
    QImage image1(filename);
    ui->label_5->setPixmap(QPixmap::fromImage(image1));
}

void MainWindow::onButtonSend()
{
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "" ||
            (ui->radioButton->isChecked()==false && ui->radioButton_2->isChecked()==false))
    {
        QMessageBox::warning(this, "Error", "Заполните все поля!");
        return;
    }
    myform->show();
    QString st = ui->lineEdit_4->text() + "*" +
            ui->lineEdit->text() + "\n" +
            ui->lineEdit_2->text() + "\n" +
            ui->lineEdit_3->text() + "\n" +
            ui->dateEdit->text();
    if (ui->radioButton->isChecked()==true) st+="\nПол: мужской";
            else st+="\nПол: женский";
    emit sendData(st);
}
