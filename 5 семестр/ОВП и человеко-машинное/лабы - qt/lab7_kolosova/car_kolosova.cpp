#include "car_kolosova.h"

car_kolosova::car_kolosova(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

car_kolosova::~car_kolosova()
{

}

QRectF car_kolosova::boundingRect() const
{
    QImage source;
    source.load("C:\\Users\\yava06\\Desktop\\lab7_kolosova_v2\\car.png");
    QRectF tmp(source.rect());
    return tmp;   /// Ограничиваем область, в которой лежит наша машинка
}

void car_kolosova::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        /*отрисовка машины*/
        QImage source; //объявляем хранилище для картинки
        source.load("C:\\Users\\yava06\\Desktop\\lab7_kolosova_v2\\car.png");//загружаем картнку в нее
        QRect rect(source.rect());
        painter->drawImage(rect, source);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void car_kolosova::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}
void car_kolosova::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void car_kolosova::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
