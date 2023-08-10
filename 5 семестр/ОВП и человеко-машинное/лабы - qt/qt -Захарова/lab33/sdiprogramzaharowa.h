#ifndef SDIPROGRAMZAHAROWA_H
#define SDIPROGRAMZAHAROWA_H

#include <QMainWindow>
#include "docwindowzaharowa.h"

class SDIProgramZaharowa : public QMainWindow{
    Q_OBJECT
public:
      SDIProgramZaharowa(QWidget *pwgt = nullptr): QMainWindow(pwgt){
        QMenu* pmnuFile= new QMenu("&File");
        QMenu* pmnuHelp = new QMenu("&Help");
        DocWindowZaharowa* pdoc = new DocWindowZaharowa;

        pmnuFile->addAction("&Open...",
                             pdoc,
                             SLOT(slotLoad()),
                            QKeySequence("CTRL+O")
                            );
        pmnuFile->addAction("&Save",
                             pdoc,
                             SLOT(slotSave()),
                             QKeySequence("CTRL+S")
                             );
        pmnuFile->addAction("&Save As...",
                            pdoc,
                             SLOT(slotSaveAs()),
                            QKeySequence("CTRL+SHIFT+S")
                            );
      pmnuFile->addSeparator();
      pmnuFile->addAction("&Quit",
                             qApp,
                             SLOT(quit()),
                             QKeySequence("ESC")
                             );
      pmnuHelp->addAction("&Help",
                           this,
                           SLOT(slotAbout()),
                            QKeySequence("F1")
                          );
      menuBar()->addMenu(pmnuFile);
      menuBar()->addMenu(pmnuHelp);
      setCentralWidget(pdoc);
      connect(pdoc,
              SIGNAL(changeWindowTitle(const QString&)),
              SLOT(slotChangeWindowTitle(const QString&))
              );
      statusBar()->showMessage("Ready",2000);
    }
public slots:
    void slotsAbout(){
        QMessageBox:: about (this,"Автор","Захарова К.Ю.\n.ИП-813");
    }
    void slotChangeWindowTitle(const QString& str){
        setWindowTitle(str);
    }
};

#endif // SDIPROGRAMZAHAROWA_H
