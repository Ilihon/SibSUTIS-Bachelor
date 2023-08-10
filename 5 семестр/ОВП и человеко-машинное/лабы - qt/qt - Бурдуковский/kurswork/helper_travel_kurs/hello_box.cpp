#include "hello_box.h"
#include "ui_hello_box.h"
#include <QFile>
hello_box::hello_box(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hello_box)
{
    ui->setupUi(this);
   // QFile *File = new QFile("D:\\QT_LAB\\Travel_guide\\Helper\\helper.html");
    QFile *File = new QFile("D:\\labs\\qt\\kurswork\\helper_travel_kurs\\Helper\\index.html");
    File->open(QFile::ReadOnly | QFile::Text);
    QString html = File->readAll();
    ui->textBrowser->setHtml(html);
    ui->textBrowser->setOpenLinks(false);
    ui->textBrowser->setOpenExternalLinks(false);
    File->close();
    connect(ui->textBrowser, SIGNAL(anchorClicked(QUrl)),this, SLOT(onAnchorClicked(QUrl)));

}
void hello_box::onAnchorClicked(const QUrl &link) {
        QString str = link.toString();
        str.replace("%5C", "\\");
        QFile *File= new QFile(str);
        File->open(QFile::ReadOnly|QFile::Text);
        QString html = File->readAll();
        ui->textBrowser->setHtml(html);
        File->close();
    }
hello_box::~hello_box()
{
    delete ui;
}
