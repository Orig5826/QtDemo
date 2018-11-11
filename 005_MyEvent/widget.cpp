#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QKeyEvent>

#include <QTimer>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    TimerInit();
    ui->label->setText("时间和日期");
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TimerInit()
{
    TimerID1 = startTimer(5000);
    TimerID2 = startTimer(3000);
    TimerID3 = startTimer(2000);

    // 若仅仅需要少量的定时器，可以通过信号和槽来处理
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::timerUpdate);
    timer->start(1000);
}

void Widget::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label->setText(str);
    ui->label->setAlignment(Qt::AlignCenter);

    // 将显示时间和日期的标签，随机给定一个位置(^.^)
    int x = qrand()%100;
    int y = qrand()%100 + 100;
    ui->label->move(x,y);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    ui->pushButton->setText(tr("坐标:(%1,%2)").arg(e->x()).arg(e->y()));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    int x = ui->pushButton->x();
    int y = ui->pushButton->y();
    switch(e->key())
    {
    case Qt::Key_W:
    {
        ui->pushButton->move(x,y-10);
    }break;
    case Qt::Key_S:
    {
        ui->pushButton->move(x,y+10);
    }break;
    case Qt::Key_A:
    {
        ui->pushButton->move(x-10,y);
    }break;
    case Qt::Key_D:
    {
        ui->pushButton->move(x+10,y);
    }break;
    default:
        break;
    }
}

void Widget::timerEvent(QTimerEvent * event)
{
    if(event->timerId() == TimerID1)
    {
        ui->lineEdit->setText("Timer_1.1.1");
    }
    else if(event->timerId() == TimerID2)
    {
        ui->lineEdit->setText("Timer_2.2.2");
    }
    else if(event->timerId() == TimerID3)
    {
        ui->lineEdit->setText("Timer_3.3.3");
    }
    else
    {
        qApp->quit();
    }
}
