#include "docwindowzaharowa.h"


void DocWindowZaharowa::slotLoad(){
    QString str = QFileDialog:: getOpenFileName();
    if(str.isEmpty()){
        return;
    }
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        m_strFileName=str;
        emit changeWindowTitle(m_strFileName);
    }
}

void DocWindowZaharowa::slotSaveAs(){
    QString str = QFileDialog::getSaveFileName(nullptr, m_strFileName);
    if(!str.isEmpty()){
        m_strFileName = str;
        slotSave();
    }
}
void DocWindowZaharowa::slotSave(){
                    if(m_strFileName.isEmpty()){
                        slotSaveAs();
                        return;
                    }
                    QFile file(m_strFileName);
                    if(file.open(QIODevice::WriteOnly)){
                        QTextStream(&file)<<toPlainText();
                                            file.close();
                        emit changeWindowTitle(m_strFileName);
                    }
                 }
DocWindowZaharowa::DocWindowZaharowa(QWidget *pwgt): QTextEdit(pwgt){}
