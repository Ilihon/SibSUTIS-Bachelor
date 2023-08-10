#ifndef HELLO_BOX_H
#define HELLO_BOX_H

#include <QWidget>

namespace Ui {
class hello_box;
}

class hello_box : public QWidget
{
    Q_OBJECT

public:
    explicit hello_box(QWidget *parent = nullptr);
    ~hello_box();
public slots:
    void onAnchorClicked(const QUrl &link);
private:
    Ui::hello_box *ui;
};

#endif // HELLO_BOX_H
