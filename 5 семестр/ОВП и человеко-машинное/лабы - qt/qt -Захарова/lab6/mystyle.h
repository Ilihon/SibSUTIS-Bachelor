#ifndef MYSTYLE_H
#define MYSTYLE_H
#include <QWidget>

namespace Ui {
class mystyle;
}

class mystyle : public QWidget
{
    Q_OBJECT

public:
    explicit mystyle(QWidget *parent = nullptr);
    ~mystyle();

private slots:
    // Слот обработчик клика кнопки для установки тёмного оформления
    void on_darkPushButton_clicked();
    // Слот обработчик клика кнопки для установки светлого оформления
    void on_lightPushButton_clicked();

private:
    Ui::mystyle *ui;
};
#endif
