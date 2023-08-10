#ifndef SDIPROGRAMBURDUKOVSKIY_H
#define SDIPROGRAMBURDUKOVSKIY_H

#include <QMainWindow>
#include <QtWidgets>
#include <docwindowburdukovskiy.h>
#include <sdiprogramburdukovskiy.h>

class SDIProgramBurdukovskiy : public QMainWindow
{
    Q_OBJECT

public:
    SDIProgramBurdukovskiy(QWidget *pwgt =0): QMainWindow(pwgt){
        QMenu* pmnuFile = new QMenu("&File");
        QMenu* pmnuHelp = new QMenu("&Help");
        DocWindowBurdukovskiy* pdoc = new DocWindowBurdukovskiy;

        pmnuFile->addAction("&Open...", pdoc, SLOT(slotLoad()),QKeySequence("CTRL+O"));
        pmnuFile->addAction("&Save...", pdoc, SLOT(slotSave()),QKeySequence("CTRL+S"));
        pmnuFile->addAction("&Save As...", pdoc, SLOT(slotSaveAs()),QKeySequence("CTRL+Shift+O"));
        pmnuFile->addSeparator();
        pmnuFile->addAction("&Quit...", qApp, SLOT(quit()),QKeySequence("ESC"));
        pmnuHelp->addAction("&Help...", this, SLOT(slotAbout()),QKeySequence("F1"));

        menuBar()->addMenu(pmnuFile);
        menuBar()->addMenu(pmnuHelp);
        setCentralWidget(pdoc);
        connect(pdoc,SIGNAL(changeWindowTitle(const QString&)),SLOT(slotChangeWindowTitle(const QString&)));
        statusBar()->showMessage("Ready",2000);

    }
public slots:
    void slotAbout(){
        QMessageBox:: about(this,"Автор","Бурдуковский И.А.\nИП-813");
    }
    void slotChangeWindowTitle(const QString& str){
        setWindowTitle(str);
    }
};

#endif // SDIPROGRAMBURDUKOVSKIY_H
