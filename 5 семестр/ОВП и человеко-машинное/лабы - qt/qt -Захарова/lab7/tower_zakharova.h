#ifndef tower_zakharova_H
#define tower_zakharova_H

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

class tower : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit tower(QObject *parent = nullptr);
    ~tower();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // tower_zakharova_H
