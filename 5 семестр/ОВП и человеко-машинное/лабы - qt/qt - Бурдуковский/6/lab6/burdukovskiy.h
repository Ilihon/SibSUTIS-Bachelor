#ifndef BURDUKOVSKIY_H
#define BURDUKOVSKIY_H

#include <QWidget>
#include <QAbstractButton>


namespace Ui {
class burdukovskiy;
}

class burdukovskiy : public QWidget
{
    Q_OBJECT

public slots:
    void recieveData(QString str);

public:
    explicit burdukovskiy(QWidget *parent = 0);
    ~burdukovskiy();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::burdukovskiy *ui;
};

#endif // BURDUKOVSKIY_H
