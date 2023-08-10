#ifndef HELLO_BOX_2_H
#define HELLO_BOX_2_H

#include <QWidget>

namespace Ui {
class hello_box_2;
}

class hello_box_2 : public QWidget
{
    Q_OBJECT

public:
    explicit hello_box_2(QWidget *parent = nullptr);
    ~hello_box_2();

private:
    Ui::hello_box_2 *ui;
};

#endif // HELLO_BOX_2_H
