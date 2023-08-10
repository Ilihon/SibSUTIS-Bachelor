#ifndef DOCWINDOWBURDUKOVSKIY_H
#define DOCWINDOWBURDUKOVSKIY_H

#include <QTextEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QtWidgets>

class DocWindowBurdukovskiy : public QTextEdit
{
    Q_OBJECT
private:
    QString m_strFilename;
public:
    DocWindowBurdukovskiy(QWidget* pwgt =0);
signals:
    void changeWindowTitle(const QString&);
public slots:
    void slotSave();
    void slotLoad();
    void slotSaveAs();
};

#endif // DOCWINDOWBURDUKOVSKIY_H
