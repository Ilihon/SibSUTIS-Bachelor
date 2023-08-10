#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include "D:\labs\OS\kurswork\server/myclient.h"
#include <QMessageBox>
class MyClient;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    //определим слоты для обработки сигналов сокета
    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();//сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
    void onSokDisplayError(QAbstractSocket::SocketError socketError);

    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
    void on_cbToAll_clicked();
    void on_pbSend_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket *_sok;   //сокет
    quint16 _blockSize; //текущий размер блока данных
    QString _name;      //имя клиента
    void addToLog(QString text, QColor color = Qt::black);

};

#endif // DIALOG_H
