#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "author.h"
#include "ui_author.h"
#include "QFileDialog"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "QTextDocumentWriter"

void MainWindow::About_Lab1()
{
    author *dg = new author();
    dg->show();
}

void MainWindow::slotOpen()
{
    QString filename = QFileDialog::getOpenFileName(0, "Открыть файл", QDir::currentPath(), "*.cpp *.txt");
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        ui->textEdit->setPlainText(file.readAll());
}

void MainWindow::slotSave()
{
    QString filename = QFileDialog::getOpenFileName(0, "Сохранить файл", QDir::currentPath(), "*.cpp *.txt");
    QTextDocumentWriter writer;
    writer.setFileName(filename);
    writer.write(ui->textEdit->document());
}

void MainWindow::slotClear()
{
    QTextDocumentWriter clear;
    ui->textEdit->clear();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action, SIGNAL(triggered()), this, SLOT(About_Lab1()));

    QAction* pactOpen = new QAction("file open action", 0);
    pactOpen->setText("&Открыть");
    pactOpen->setShortcut(QKeySequence("CTRL+O"));
    pactOpen->setToolTip("Открытие документа");
    pactOpen->setStatusTip("Открыть файл");
    pactOpen->setWhatsThis("Открыть файл");
    pactOpen->setIcon(QPixmap("1.png"));
    connect(pactOpen, SIGNAL(triggered()), SLOT(slotOpen()));
    //QMenu* pmnuFile=new QMenu("&Файл");

    QAction* pactSave = new QAction("file save action", 0);
    pactSave->setText("&Сохранить");
    pactSave->setShortcut(QKeySequence("CTRL+S"));
    pactSave->setToolTip("Сохранение документа");
    pactSave->setStatusTip("Сохранить файл");
    pactSave->setWhatsThis("Сохранить файл");
    pactSave->setIcon(QPixmap("1.png"));
    connect(pactSave, SIGNAL(triggered()), SLOT(slotSave()));

    QAction* pactClear = new QAction("file clear", 0);
    pactClear->setText("&Очистить");
    pactClear->setShortcut(QKeySequence("CTRL+D"));
    pactClear->setToolTip("Очистка документа");
    pactClear->setStatusTip("Очистить файл");
    pactClear->setWhatsThis("Очистить файл");
    pactClear->setIcon(QPixmap("1.png"));
    connect(pactClear, SIGNAL(triggered()), SLOT(slotClear()));
/*
    pmnuFile->addAction(pactOpen);
    pmnuFile->addAction(pactSave);
    pmnuFile->addAction(pactClear);
    menuBar()->addMenu(pmnuFile);
*/
    ui->mainToolBar->addAction(pactOpen);
    ui->mainToolBar->addAction(pactSave);
    ui->mainToolBar->addAction(pactClear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

