#ifndef car_kolosova_H
#define car_kolosova_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QPixmap>
/* Подключаем библиотеку, отвечающую за использование WinAPI
 * Данная библиотека необходима для асинхронной проверки состояния клавиш
 * */
#include <windows.h>

class car_kolosova : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit car_kolosova(QObject *parent = 0);
    ~car_kolosova();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // car_kolosova_H
