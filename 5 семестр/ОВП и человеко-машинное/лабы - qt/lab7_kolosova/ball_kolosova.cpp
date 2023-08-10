#include "ball_kolosova.h"

ball::ball(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    UP = true;
    DOWN = false;
    LEFT = true;
    RIGHT = false;
}

ball::~ball()
{

}

QRectF ball::boundingRect() const
{
    return QRectF(-30,-30,30,30);   /// Ограничиваем область, в которой лежит мячик
}

void ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->setBrush(Qt::red);     /// Устанавливаем кисть, которой будем отрисовывать объект
        painter->drawEllipse(-30, -30, 30, 30);  /// Рисуем мячик
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void ball::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}
void ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
void ball::slotGameTimer()
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
