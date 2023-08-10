#ifndef DOCWINDOWZAHAROWA_H
#define DOCWINDOWZAHAROWA_H

#include<QTextEdit>
#include<QFileDialog>
#include<QTextStream>
#include<QColorDialog>
#include<QtWidgets>

class DocWindowZaharowa : public QTextEdit
{
    Q_OBJECT
private:
    QString m_strFileName;
public:
    DocWindowZaharowa(QWidget* pwgt = nullptr);
signals:
    void changeWindowTitle(const QString&);
public slots:
    void slotSave();
    void slotLoad();
    void slotSaveAs();
};

#endif // DOCWINDOWZAHAROWA_H
