#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "dialog.h"
#include "myclient.h"
class MyClient;

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QWidget *widget = 0, QObject *parent = 0);
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name);	//уведомить о новом пользователе
    void doSendToAllUserLeft(QString name);
    void doSendToAllMessage(QString message, QString fromUsername);	//разослать сообщение
    void doSendToAllServerMessage(QString message);	//серверное сообщение
    void doSendServerMessageToUsers(QString message, const QStringList &users);	//приватное серверное сообщение
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    QStringList getUsersOnline() const;	//узнать список пользователей
    bool isNameValid(QString name) const;	//проверить имя
    bool isNameUsed(QString name) const;	//проверить используется ли имя

signals:
    void addLogToGui(QString string, QColor color = Qt::black);
    void addUserToGui(QString);
    void removeUserFromGui(QString);

public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(MyClient *client);

protected:
    void incomingConnection(qintptr handle);

private:
    QList<MyClient *> _clients;	//список пользователей
    QWidget *_widget;	//ссылка на виджет для подключения к нему сигналов от myclient

};

#endif // MYSERVER_H
