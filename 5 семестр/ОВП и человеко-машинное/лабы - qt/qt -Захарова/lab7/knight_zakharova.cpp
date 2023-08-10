#include "knight_zakharova.h"

knight::knight(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    UP = true;
    DOWN = false;
    LEFT = true;
    RIGHT = false;
}

knight::~knight()
{

}

QRectF knight::boundingRect() const
{
    QImage source;
    source.load("C:\\Users\\zubov\\Documents\\lab7\\knight.png"); //ПУТЬ К КАРТИНКЕ
    QRectF tmp(source.rect());
    return tmp;   /// Ограничиваем область, в которой лежит наша башня
}

void knight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*отрисовка рыцаря*/
    QImage source; //объявляем хранилище для картинки
    source.load("C:\\Users\\zubov\\Documents\\lab7\\knight.png");//ПУТЬ К КАРТИНКЕ
    QRect rect(source.rect());
    painter->drawImage(rect, source);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void knight::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}
void knight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void knight::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
void knight::slotGameTimer()
{
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */

    if(LEFT == true){
        setPos(mapToParent(-5, 0));
    }
    if(RIGHT == true){
        setPos(mapToParent(5, 0));
    }
    if(UP == true){
        setPos(mapToParent(0, -5));     /* Продвигаем объект на 5 пискселей вперёд
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */
    }
    if(DOWN == true){
        setPos(mapToParent(0, 5));      /* Продвигаем объект на 5 пискселей назад
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */
    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад, сменяя направление полёта через булевские переменные
     * */
    if(this->x() - 10 < -250){
        this->setX(-240);// слева
        LEFT = false;
        RIGHT = true;
    }
    if(this->x() + 10 > 250){
        this->setX(240);        // справа
        RIGHT = false;
        LEFT = true;
    }

    if(this->y() - 10 < -250){
        this->setY(-240);       // сверху
        UP = false;
        DOWN = true;

    }
    if(this->y() + 10 > 250){
        this->setY(240);        // снизу
        UP = true;
        DOWN = false;
    }
}
