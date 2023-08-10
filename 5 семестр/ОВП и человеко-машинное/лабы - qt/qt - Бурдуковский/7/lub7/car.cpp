#include "car.h"

car::car(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

car::~car()
{

}

QRectF car::boundingRect() const
{
    QImage source;
    source.load("D:\\labs\\qt\\7\\lub7\\car.png");
    QRectF tmp(source.rect());
    return tmp;   /// Ограничиваем область, в которой лежит наша машинка
}

void car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        /*отрисовка машины*/
        QImage source;
        source.load("D:\\labs\\qt\\7\\lub7\\car.png");
        QRect rect(source.rect());
        painter->drawImage(rect, source);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void car::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}
void car::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void car::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
