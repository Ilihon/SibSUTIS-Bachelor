#include "myserver.h"

MyServer::MyServer(QWidget *widget, QObject *parent) :QTcpServer(parent)
{
    _widget = widget;
}

bool MyServer::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
        qDebug() << "Server not started at" << addr << ":" << port;
        return false;
    }
    qDebug() << "Server started at" << addr << ":" << port;
    return true;
}

//отправляем на клиенты инфу что кто-то присоеденился
//При рассылке сообщения всем нужно делать проверку авторизован ли текущий пользователь, ибо в массиве _clients, возможно, находятся не авторизованные
void MyServer::doSendToAllUserJoin(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //резервируем 2 байта для размера блока. Класс MyClient используется в реализации сервера, но тут используем статические члены этого класса - константы команд
    //третий байт - команда
    out << (quint16)0 << MyClient::comUserJoin << name;
    //возваращаемся в начало
    out.device()->seek(0);
    //вписываем размер блока на зарезервированное место
    out << (quint16)(block.size() - sizeof(quint16));
    //отправка сообщения всем
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() != name && _clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

//отправляем на клиенты инфу что кто-то отсоединился
void MyServer::doSendToAllUserLeft(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::comUserLeft << name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() != name && _clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}


//отправляем на клиенты сообщение от пользователя
void MyServer::doSendToAllMessage(QString message, QString fromUsername)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::comMessageToAll << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

//отправляем на клиенты приватку от пользователя к выбраным пользователям
void MyServer::doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername)
{
    QByteArray block, blockToSender;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::comMessageToUsers << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //отправка сообщения всем выбранным пользователям (тут отсутствует проверка на авторизацию, ибо все пользователи в users гарантированно авторизованы)
    QDataStream outToSender(&blockToSender, QIODevice::WriteOnly);
    outToSender << (quint16)0 << MyClient::comMessageToUsers << users.join(",") << message;
    outToSender.device()->seek(0);
    outToSender << (quint16)(blockToSender.size() - sizeof(quint16));
    for (int j = 0; j < _clients.length(); ++j)
        if (users.contains(_clients.at(j)->getName()))
            _clients.at(j)->_sok->write(block);
        else if (_clients.at(j)->getName() == fromUsername)
            _clients.at(j)->_sok->write(blockToSender);
}

//отправляем на клиенты сообщение от сервера
void MyServer::doSendToAllServerMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::comPublicServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

//отправляем на клиенты приватку от сервера к выбраным пользователям
void MyServer::doSendServerMessageToUsers(QString message, const QStringList &users)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << MyClient::comPrivateServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //отправка сообщения всем выбранным пользователям (тут отсутствует проверка на авторизацию, ибо все пользователи в users гарантированно авторизованы)
    for (int j = 0; j < _clients.length(); ++j)
        if (users.contains(_clients.at(j)->getName()))
            _clients.at(j)->_sok->write(block);
}


QStringList MyServer::getUsersOnline() const
{
    QStringList l;
    foreach (MyClient * c, _clients)
        if (c->getAutched())
            l << c->getName();
    return l;
}

bool MyServer::isNameValid(QString name) const
{
    if (name.length() > 20 || name.length() < 4)
        return false;
    QRegExp r("[A-Za-z0-9_]+");
    return r.exactMatch(name);
}

bool MyServer::isNameUsed(QString name) const
{
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() == name)
            return true;
    return false;
}

void MyServer::incomingConnection(qintptr handle)
{
   //передаем дескриптор сокета, указатель на сервер (для вызова его методов), и стандартный параметр - parent
    MyClient *client = new MyClient(handle, this, this);
    //подключаем сигналы напрямую к виджету, если его передали в конструктор сервера
    if (_widget != 0)
    {
        connect(client, SIGNAL(addUserToGui(QString)), _widget, SLOT(onAddUserToGui(QString)));
        connect(client, SIGNAL(removeUserFromGui(QString)), _widget, SLOT(onRemoveUserFromGui(QString)));
        connect(client, SIGNAL(messageToGui(QString,QString,QStringList)), _widget, SLOT(onMessageToGui(QString,QString,QStringList)));
    }
    connect(client, SIGNAL(removeUser(MyClient*)), this, SLOT(onRemoveUser(MyClient*)));
    _clients.append(client);
}

void MyServer::onRemoveUser(MyClient *client)
{
    _clients.removeAt(_clients.indexOf(client));
}

void MyServer::onMessageFromGui(QString message, const QStringList &users)
{
    if (users.isEmpty())
        doSendToAllServerMessage(message);
    else
        doSendServerMessageToUsers(message, users);
}
