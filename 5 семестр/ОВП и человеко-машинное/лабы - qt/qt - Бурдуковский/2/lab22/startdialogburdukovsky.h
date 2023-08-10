#ifndef STARTDIALOGBURDUKOVSKY_H
#define STARTDIALOGBURDUKOVSKY_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <inputdialogburdukovsky.h>

class StartDialogBurdukovsky: public QPushButton
{
    Q_OBJECT
public:
    StartDialogBurdukovsky(QWidget* pwgt = nullptr) : QPushButton ("Нажми", pwgt)
    {
        connect(this,SIGNAL(clicked()), SLOT(slotButtonClicked()));
    }
    public slots:
    void slotButtonClicked()
    {
        InputDialogBurdukovsky* pInputDialogBurdukovsky = new InputDialogBurdukovsky;
        if(pInputDialogBurdukovsky->exec()==QDialog::Accepted){
            QMessageBox::information(nullptr,"Ваша информация: ","Имя: " + pInputDialogBurdukovsky->firstName()+"\nФамилия: "+pInputDialogBurdukovsky->lastName());
        }
        delete pInputDialogBurdukovsky;
    }
};

#endif // STARTDIALOGBURDUKOVSKY_H
