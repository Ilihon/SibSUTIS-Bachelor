#include "zaharowa.h"
#include "ui_zaharowa.h"

Zaharowa::Zaharowa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zaharowa)
{
    ui->setupUi(this);
}

Zaharowa::~Zaharowa()
{
    delete ui;
}
void Zaharowa:: recieveData(QString str)
{
    QStringList lst =str.split("*");
    ui->textEdit->setText(lst.at(1)+"\n"+lst.at(0));
    if (lst.size()>1){
        QImage image(lst.at(0));
        ui->label->setPixmap(QPixmap::fromImage(image));

    }
}

void Zaharowa::slotSave(){
    if(m_strFileName.isEmpty()){
        QString str=QFileDialog::getSaveFileName(nullptr,m_strFileName);
        if (!str.isEmpty()){
            m_strFileName=str;
            slotSave();
        }
        return;
    }
    QFile file(m_strFileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream(&file) << ui->textEdit->toPlainText();
        file.close();
    }
    QMessageBox::information(nullptr,"Информация","Файл сохранён");
}

void Zaharowa::on_buttonBox_clicked(QAbstractButton *button){
    if(button->text()=="Reset"){
        ui->textEdit->clear();
        ui->label->clear();
    }
    if(button->text()=="Save All"){
        QString str = QFileDialog::getSaveFileName(nullptr,m_strFileName);
        if (!str.isEmpty()){
            m_strFileName=str;
            slotSave();
        }
    }
    if(button->text()=="Open"){
        QString str=QFileDialog::getOpenFileName();
        if(str.isEmpty()){
            return;
        }
        QFile file(str);
        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);
            QString line = stream.readAll();
            file.close();
            ui->textEdit->setPlainText(line);
        }
        QStringList inf = ui->textEdit->toPlainText().split("\n");
        QImage image2(inf.at(5));
        ui->label->setPixmap(QPixmap::fromImage(image2));
    }
}
