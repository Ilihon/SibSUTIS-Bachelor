#include "tower_zakharova.h"

tower::tower(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

tower::~tower()
{

}

QRectF tower::boundingRect() const
{
    QImage source;
    source.load("C:\\Users\\zubov\\Documents\\lab7\\tower.png");
    QRectF tmp(source.rect());
    return tmp;   /// Ограничиваем область, в которой лежит наша башня
}

void tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        /*отрисовка башни*/
        QImage source; //объявляем хранилище для картинки
        source.load("C:\\Users\\zubov\\Documents\\lab7\\tower.png");//загружаем картнку в нее
        QRect rect(source.rect());
        painter->drawImage(rect, source);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void tower::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}
void tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void tower::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
