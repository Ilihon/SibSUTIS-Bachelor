#include "widget_burdukovskiy.h"
#include "ui_widget_burdukovskiy.h"

widget_burdukovskiy::widget_burdukovskiy(QWidget *parent) : QWidget(parent), ui(new Ui::widget_burdukovskiy)
{
    ui->setupUi(this);
    this->resize(530,530);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(530,530);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену
    Ball = new ball();      /// Инициализируем мяч
    Car = new car(); ///Инициализируем машину

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены
    /* Дополнительно нарисуем органичение территории в графической сцене */
    scene->addLine(-250,-250, 250,-250, QPen(Qt::black));
    scene->addLine(-250, 250, 250, 250, QPen(Qt::black));
    scene->addLine(-250,-250,-250, 250, QPen(Qt::black));
    scene->addLine( 250,-250, 250, 250, QPen(Qt::black));

    scene->addItem(Ball);   /// Добавляем на сцену мяч
    scene->addItem(Car);   ///Добавляем на сцену машину
    Ball->setPos(200,0);      /// Устанавливаем мяч в центр сцены
    Car->setPos(0, 0);      /// Устанавливаем машину в центр сцены

    /* Инициализируем таймер и вызываем слот обработки сигнала таймера
     * у мяча 20 раз в секунду.
     * Управляя скоростью отсчётов, соответственно управляем скоростью
     * изменения состояния графической сцены. Все это нужно для автоматического движения.
     * */
    timer = new QTimer();
    connect(timer, &QTimer::timeout, Ball, &ball::slotGameTimer);
    timer->start(1000 / 50);
}

widget_burdukovskiy::~widget_burdukovskiy()
{
    delete ui;
}
