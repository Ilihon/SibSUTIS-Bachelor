#ifndef ZAHAROWA_H
#define ZAHAROWA_H

#include <QWidget>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QAbstractButton>
#include <QFileDialog>
#include <QMessageBox>


namespace Ui {
class Zaharowa;
}
class Zaharowa : public QWidget
{
    Q_OBJECT

public:
    explicit Zaharowa(QWidget *parent = nullptr);
    ~Zaharowa();
private:
    Ui::Zaharowa *ui;
    QString m_strFileName;

public slots:
    void recieveData(QString str);
    void slotSave();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
signals:
    void changeWindowTitle(const QString);

};

#endif // ZAHAROWA_H
