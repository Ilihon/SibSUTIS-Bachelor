#ifndef DATE_H
#define DATE_H

#include <QWidget>

namespace Ui {
class date;
}

class date : public QWidget
{
    Q_OBJECT

public:
    explicit date(QWidget *parent = 0);
    ~date();

signals:
    void sendData(QString str);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::date *ui;
};

#endif // DATE_H
