#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class add;
}

class add : public QWidget
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = 0);
    ~add();

signals:
    void sendData(QString str);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add *ui;
};

#endif // ADD_H
