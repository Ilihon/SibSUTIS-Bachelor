#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThreadPool>
#include <QtGui>
#include <QRegExp>
#include "dialog.h"
#include "myserver.h"
class MyServer;

class MyClient : public QObject
{
    friend class MyServer;
    Q_OBJECT

public:
    static const QString constNameUnknown;
    static const quint8 comAutchReq = 1;
    static const quint8 comUsersOnline = 2;
    static const quint8 comUserJoin = 3;
    static const quint8 comUserLeft = 4;
    static const quint8 comMessageToAll = 5;
    static const quint8 comMessageToUsers = 6;
    static const quint8 comPublicServerMessage = 7;
    static const quint8 comPrivateServerMessage = 8;
    static const quint8 comAutchSuccess = 9;
    static const quint8 comErrNameInvalid = 201;
    static const quint8 comErrNameUsed = 202;

    explicit MyClient(int desc, MyServer *serv, QObject *parent = 0);
    ~MyClient();
    void setName(QString name) {_name = name;}
    QString getName() const {return _name;}
    bool getAutched() const {return _isAutched;}
    void doSendCommand(quint8 comm) const;
    void doSendUsersOnline() const;

signals:
//сигналы для обновления гуи
    void addUserToGui(QString name);
    void removeUserFromGui(QString name);
//сигнал удаления пользователя из QList
    void removeUser(MyClient *client);
    void messageToGui(QString message, QString from, const QStringList &users);
//cлоты для работы с сокетом
private slots:
    void onConnect();
    void onDisconnect();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError) const;

private:
    QTcpSocket *_sok;	//сокет
    MyServer *_serv;	//ccылка на сервер
    quint16 _blockSize;	//текущей размер блока
    QString _name;		//имя
    bool _isAutched;	//флаг авторизации

};

#endif // MYCLIENT_H
