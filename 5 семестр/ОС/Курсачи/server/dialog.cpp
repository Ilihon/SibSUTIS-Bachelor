#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("favicon.PNG"));
    //создаем сервер. первый параметр стандартный - parent, второй - передадим ссылку на объект виджета, для подключения сигналов от myclient к нему
    _serv = new MyServer(this, this);

    //подключаем сигналы от виджета к серверу
    connect(this, SIGNAL(messageFromGui(QString,QStringList)), _serv, SLOT(onMessageFromGui(QString,QStringList)));
    connect(_serv, SIGNAL(addLogToGui(QString,QColor)), this, SLOT(onAddLogToGui(QString,QColor)));

    //по умолчанию запускаем сервер на 127.0.0.1:80
    ui->pbStartStop->setChecked(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onAddUserToGui(QString name)
{
    ui->lwUsers->addItem(name);
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+name+" joined");
    ui->lwLog->item(0)->setTextColor(Qt::green);
}

void Dialog::onRemoveUserFromGui(QString name)
{
    for (int i = 0; i < ui->lwUsers->count(); ++i)
        if (ui->lwUsers->item(i)->text() == name)
        {
            ui->lwUsers->takeItem(i);
            ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+name+" left");
            ui->lwLog->item(0)->setTextColor(Qt::green);
            break;
        }
}

void Dialog::onMessageToGui(QString message, QString from, const QStringList &users)
{
    if (users.isEmpty())
        ui->lwLog->insertItem(0, QTime::currentTime().toString()+" message from "+from+": "+message+" to all");
    else
    {
        ui->lwLog->insertItem(0, QTime::currentTime().toString()+" message from "+from+": "+message+" to "+users.join(","));
        ui->lwLog->item(0)->setTextColor(Qt::blue);
    }
}

void Dialog::onAddLogToGui(QString string, QColor color)
{
    addToLog(string, color);
}

void Dialog::on_pbSend_clicked()
{
    QStringList l;
    if (!ui->cbToAll->isChecked())
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
            l << i->text();
    emit messageFromGui(ui->pteMessage->document()->toPlainText(), l);
    ui->pteMessage->clear();
    if (l.isEmpty())
        addToLog(" Sended public server message", Qt::black);
    else
        addToLog(" Sended private server message to "+l.join(","), Qt::black);
}

//меняем режим отправки сообщений
void Dialog::on_cbToAll_clicked()
{
    if (ui->cbToAll->isChecked())
        ui->pbSend->setText("Send");
    else
        ui->pbSend->setText("Send To Selected");
}


void Dialog::on_pbStartStop_toggled(bool checked)
{
    if (checked)
    {
        QHostAddress addr;
        if (!addr.setAddress(ui->leHost->text()))
        {
            addToLog(" invalid address "+ui->leHost->text(), Qt::red);
            return;
        }
        if (_serv->doStartServer(addr,80))
        {
            addToLog(" server started at "+ui->leHost->text()+":80", Qt::green);
            ui->pbSend->setEnabled(true);
            ui->cbToAll->setEnabled(true);
            ui->pbStartStop->setText("Stop server");
        }
        else
        {
            addToLog(" server not started at "+ui->leHost->text()+":80", Qt::red);
            ui->pbStartStop->setText("Reload");
            ui->pbSend->setEnabled(false);
            ui->cbToAll->setEnabled(false);
        }
    }
    else
    {
        addToLog(" server stopped at "+_serv->serverAddress().toString()+":80", Qt::green);
        _serv->close();
        ui->pbSend->setEnabled(false);
        ui->cbToAll->setEnabled(false);
        ui->pbStartStop->setText("Start server");

    }
}

void Dialog::addToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+text);
    ui->lwLog->item(0)->setTextColor(color);
}
