#ifndef knight_zakharova_H
#define knight_zakharova_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class knight : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit knight(QObject *parent = nullptr);
    ~knight();

signals:

public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения мячика

protected:
    QRectF boundingRect() const; // получение квадрата мячика
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//отрисовка мячика
private:
    bool LEFT; //состояния полёта
    bool RIGHT;
    bool UP;
    bool DOWN;
    QRect rect;
    QTimer *timer;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);//методы для пермещения мячика мышкой
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif // knight_zakharova_H
