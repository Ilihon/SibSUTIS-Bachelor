#include "docwindowburdukovskiy.h"

void DocWindowBurdukovskiy::slotLoad()
{
    QString str = QFileDialog::getOpenFileName();
    if (str.isEmpty()){
        return;
    }
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        m_strFilename = str;
        emit changeWindowTitle(m_strFilename);
    }
}

void DocWindowBurdukovskiy::slotSaveAs()
{
    QString str = QFileDialog::getSaveFileName(0, m_strFilename);
    if (!str.isEmpty()){
        m_strFilename=str;
        slotSave();
    }
}

void DocWindowBurdukovskiy::slotSave()
{
    if (m_strFilename.isEmpty()){
        slotSaveAs();
        return;
    }
    QFile file(m_strFilename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream(&file)<<toPlainText();
        file.close();
        emit changeWindowTitle(m_strFilename);
    }
}

DocWindowBurdukovskiy::DocWindowBurdukovskiy(QWidget *pwgt): QTextEdit(pwgt){}
