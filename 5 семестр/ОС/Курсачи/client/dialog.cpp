#include "dialog.h"
#include "ui_dialog.h"

#include <QtGui>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :QDialog(parent),ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("favicon.PNG"));
    _name = "";
    //создаем сокет
    _sok = new QTcpSocket(this);
    //подключаем сигналы
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        ui->pbConnect->setEnabled(true);
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        ui->pbConnect->setEnabled(true);
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+_sok->errorString());
        ui->pbConnect->setEnabled(true);
        break;
    }
}

void Dialog::onSokReadyRead()
{
    //обрабатываем данные от сервера
    QDataStream in(_sok);
    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch (command)
    {
        //если удачно прошла авторизация, включаем кнопку отправки сообщения и обновляем лог
        case MyClient::comAutchSuccess:
        {
            ui->pbSend->setEnabled(true);
            addToLog("Enter as "+_name,Qt::green);
        }
        break;

        //сервер отправит список пользователей, если авторизация пройдена, в таком случае третий байт равен константе MyClient::comUsersOnline
        case MyClient::comUsersOnline:
        {
            addToLog("Received user list "+_name,Qt::green);
            ui->pbSend->setEnabled(true);
            ui->cbToAll->setEnabled(true);
            QString users;
            in >> users;
            if (users == "")
                return;

            //сервер передает имена через запятую, как строку (хотя можно писать в поток и объект QStringList)
            QStringList l =  users.split(",");
            //обновляем гуи
            ui->lwUsers->addItems(l);
        }
        break;
        //общее сообшение от пользователя
        case MyClient::comMessageToAll:
        {
            //считываем и добавляем в лог
            QString user;
            in >> user;
            QString message;
            in >> message;
            addToLog("["+user+"]: "+message);
        }
        break;
        //ЛС от пользователя к пользователю
        case MyClient::comMessageToUsers:
        {
            //считываем и добавляем в лог
            QString user;
            in >> user;
            QString message;
            in >> message;
            addToLog("["+user+"](private): "+message, Qt::blue);
        }
        break;
        //общее сообщение от сервера
        case MyClient::comPublicServerMessage:
        {
            //считываем и добавляем в лог
            QString message;
            in >> message;
            addToLog("[Server]: "+message, Qt::red);
        }
        break;
        //ЛС от серва к пользователю
        case MyClient::comPrivateServerMessage:
        {
            QString message;
            in >> message;
            addToLog("[Server](private) : "+message, Qt::darkMagenta);
        }
        break;
        //Пользователь присоеденился
        case MyClient::comUserJoin:
        {
            QString name;
            in >> name;
            ui->lwUsers->addItem(name);
            addToLog(name+" joined", Qt::green);
        }
        break;
        //Пользователь ливнул
        case MyClient::comUserLeft:
        {
            QString name;
            in >> name;
            for (int i = 0; i < ui->lwUsers->count(); ++i)
                if (ui->lwUsers->item(i)->text() == name)
                {
                    ui->lwUsers->takeItem(i);
                    addToLog(name+" left", Qt::green);
                    break;
                }
        }
        break;
        //Если ник плохой
        case MyClient::comErrNameInvalid:
        {
            QMessageBox::information(this, "Error", "This name is invalid.");
            _sok->disconnectFromHost();
        }
        break;
        //Если ник занят
        case MyClient::comErrNameUsed:
        {
            QMessageBox::information(this, "Error", "This name is already used.");
            _sok->disconnectFromHost();
        }
        break;
    }
}

//когда подключились
void Dialog::onSokConnected()
{
    ui->pbConnect->setEnabled(false);   //отрубаем кнопку подсоединения
    ui->leName->setEnabled(false);      //вырубаем возможность менять ник
    ui->leHost->setEnabled(false);      //вырубаем возможность менять IP
    ui->pbDisconnect->setEnabled(true); //врубаем кнопку отсоединения
    _blockSize = 0;
    addToLog("Connected to"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()),Qt::green); //выводим сообщенеие о подключении

    //после подключения следует отправить запрос на авторизацию
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //резервируем 2 байта для размера блока. Класс MyClient используется в реализации сервера,
    //но тут используем статические члены этого класса - константы команд
    //третий байт - команда
    out << (quint16)0;
    out << (quint8)MyClient::comAutchReq;
    out << ui->leName->text();
    _name = ui->leName->text();

    //возваращаемся в начало
    out.device()->seek(0);
    //вписываем размер блока на зарезервированное место
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

//когда отключились
void Dialog::onSokDisconnected()
{
    ui->pbDisconnect->setEnabled(false);
    ui->pbSend->setEnabled(false);
    ui->cbToAll->setEnabled(false);
    ui->pbConnect->setEnabled(true);
    ui->leName->setEnabled(true);
    ui->leHost->setEnabled(true);
    ui->lwUsers->clear();
    addToLog("Disconnected from"+_sok->peerAddress().toString()+":80", Qt::green);
}

//по нажатию кнопки подключаемся к серверу
//connectToHost() возвращает тип void, потому что это асинхронный вызов и в случае ошибки будет вызван слот onSokDisplayError
void Dialog::on_pbConnect_clicked()
{
    ui->pbConnect->setEnabled(false);
    _sok->connectToHost(ui->leHost->text(), 80);
}

//по нажатию кнопки отключаемся от сервера
void Dialog::on_pbDisconnect_clicked()
{
    _sok->disconnectFromHost();
}

//меняем режим отправки сообщений
void Dialog::on_cbToAll_clicked()
{
    if (ui->cbToAll->isChecked())
        ui->pbSend->setText("Send");
    else
        ui->pbSend->setText("Send To Selected");
}

//отправляем сообщение
void Dialog::on_pbSend_clicked()
{
    //отправляем запрос на сообщение
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //резервируем 2 байта для размера блока. Класс MyClient используется в реализации сервера, но тут используем статические члены этого класса - константы команд
    //третий байт - команда
    out << (quint16)0;
    if (ui->cbToAll->isChecked())
        out << (quint8)MyClient::comMessageToAll;
    else
    {
        out << (quint8)MyClient::comMessageToUsers;
        //записываем всех пользователей кому отправляем
        QString s;
        foreach (QListWidgetItem *i, ui->lwUsers->selectedItems())
            s += i->text()+",";
        s.remove(s.length()-1, 1);
        out << s;
    }
    //записываем сообщение
    out << ui->pteMessage->document()->toPlainText();
    //возваращаемся в начало
    out.device()->seek(0);
    //вписываем размер блока на зарезервированное место
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
    //очищаем поле сообщения
    ui->pteMessage->clear();
}

//выписываем в лог с нужным цветом
void Dialog::addToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);
    ui->lwLog->item(0)->setTextColor(color);
}
