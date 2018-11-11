#ifndef WIDGET_H
#define WIDGET_H

// 当在windows上使用Qt的时候，添加如下代码
// 则Qt保存为utf-8文件的时候，生成的程序没有乱码
#pragma execution_character_set("utf-8")


#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
/*
 * 为了更加放便的使用坐标系，我们添加的Debug方式。用来随时调试显示坐标
 * 注意这种坐标的显示，都显示的是相对于窗口中绘图的界面而言的
 */

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
