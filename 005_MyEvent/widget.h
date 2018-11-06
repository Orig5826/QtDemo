#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#pragma execution_character_set("utf-8")


class QMouseEvent;
class QKeyEvent;
class QTimerEvent;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    int TimerID1,TimerID2,TimerID3;
    void TimerInit();
    void timerUpdate();

protected:
    /* 鼠标和按键 */
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    /*
     * \breaf 定时器
     * 定时器事件
     * 若想开启少量的定时器，也可以使用信号和槽
     * 见 timerUpdate
     */
    void timerEvent(QTimerEvent *);
    /* 随机数 */
};

#endif // WIDGET_H
