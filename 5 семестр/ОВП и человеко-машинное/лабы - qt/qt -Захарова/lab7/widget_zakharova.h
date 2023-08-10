#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "knight_zakharova.h"
#include "tower_zakharova.h"
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
   explicit widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widget      *ui;
    QGraphicsScene  *scene;
    knight          *Knight;
    tower           *Tower;
    QTimer          *timer;

};
#endif // WIDGET_H
