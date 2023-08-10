#ifndef INPUTDIALOGBURDUKOVSKY_H
#define INPUTDIALOGBURDUKOVSKY_H

#include <QDialog>
#include <QLineEdit>

class QLineEdit;

class InputDialogBurdukovsky: public QDialog
{
    Q_OBJECT
private:
    QLineEdit * m_ptxtFirstname;
    QLineEdit * m_ptxtLastname;
public:
    InputDialogBurdukovsky(QWidget* pwgt = nullptr);
    QString firstName() const;
    QString lastName() const;
};

#endif // INPUTDIALOGBURDUKOVSKY_H
