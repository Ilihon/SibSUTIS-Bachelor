#include "inputdialogburdukovsky.h"
#include <QLabel>
#include <QLayout>
#include <QString>
#include <QPushButton>

InputDialogBurdukovsky :: InputDialogBurdukovsky(QWidget* pwgt): QDialog (pwgt){

    m_ptxtFirstname  = new QLineEdit;
    m_ptxtLastname = new QLineEdit;
    QLabel* plblFirstName= new QLabel("&Имя");
    QLabel* plblLastName= new QLabel("&Фамилия");

    plblFirstName->setBuddy(m_ptxtFirstname);
    plblLastName->setBuddy(m_ptxtLastname);

    QPushButton* pcmdOk = new QPushButton("ok");
    QPushButton* pcmdCancel = new QPushButton("Cancel");

    connect(pcmdOk, SIGNAL(clicked()),SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()),SLOT(reject()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblFirstName,0,0);
    ptopLayout->addWidget(plblLastName,1,0);
    ptopLayout->addWidget(m_ptxtFirstname,0,1);
    ptopLayout->addWidget(m_ptxtLastname,1,1);
    ptopLayout->addWidget(pcmdOk,2,0);
    ptopLayout->addWidget(pcmdCancel,2,1);
    setLayout(ptopLayout);
}
QString InputDialogBurdukovsky:: firstName() const{
    return m_ptxtFirstname->text();
}
QString InputDialogBurdukovsky:: lastName() const{
    return m_ptxtLastname->text();
}
