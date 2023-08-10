#ifndef STARTDIALOGZAHAROWA_H
#define STARTDIALOGZAHAROWA_H

//#include <QAbstractItemModel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <inputdialogzaharowa.h>

class StartDialogZaharowa: public QPushButton{
    Q_OBJECT
public:
    StartDialogZaharowa(QWidget* pwgt = nullptr) : QPushButton ("Нажми",pwgt)
    {
        connect(this,SIGNAL(clicked()),SLOT(slotButtonClicked()));
    }
    public slots:
    void slotButtonClicked()
    {
        InputDialogZaharowa* pInputDialogZaharowa = new InputDialogZaharowa;
        if(pInputDialogZaharowa->exec()==QDialog::Accepted){
             QMessageBox::information(nullptr,"Выша информация: ","Имя: " +pInputDialogZaharowa->firstName()+"\nФамилия: "+pInputDialogZaharowa->lastName());
        }
        delete pInputDialogZaharowa;
    }
};


#endif // STARTDIALOGZAHAROWA_H
