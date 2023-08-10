#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ball_kolosova.h"
#include "car_kolosova.h"
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
   explicit widget(QWidget *parent = 0);
    ~widget();

private:
    Ui::widget      *ui;
    QGraphicsScene  *scene;
    ball            *Ball;
    car_kolosova    *Car;
    QTimer          *timer;

};
#endif // WIDGET_H
