#ifndef WIDGET_BURDUKOVSKIY_H
#define WIDGET_BURDUKOVSKIY_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include "ball.h"
#include "car.h"

QT_BEGIN_NAMESPACE
namespace Ui { class widget_burdukovskiy; }
QT_END_NAMESPACE

class widget_burdukovskiy : public QWidget
{
    Q_OBJECT

public:
   explicit widget_burdukovskiy(QWidget *parent = 0);
    ~widget_burdukovskiy();

private:
    Ui::widget_burdukovskiy *ui;
    QGraphicsScene          *scene;
    ball                    *Ball;
    car                     *Car;
    QTimer                  *timer;

};
#endif // WIDGET_BURDUKOVSKIY_H
