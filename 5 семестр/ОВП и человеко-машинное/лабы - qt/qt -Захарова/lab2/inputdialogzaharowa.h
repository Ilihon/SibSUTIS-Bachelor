#ifndef INPUTDIALOGZAHAROWA_H
#define INPUTDIALOGZAHAROWA_H

//#include <QAbstractItemModel>
#include <QDialog>
#include <QLineEdit>

class QLineEdit;

class InputDialogZaharowa: public QDialog
{
    Q_OBJECT
private:
    QLineEdit* m_ptxtFirstName;
    QLineEdit* m_ptxtLastName;
public:
    InputDialogZaharowa(QWidget* pwgt =nullptr);
    QString firstName() const;
    QString lastName() const;
};

#endif // INPUTDIALOGZAHAROWA_H
