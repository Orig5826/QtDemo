#ifndef WIDGET_H
#define WIDGET_H

// 当在windows上使用Qt的时候，添加如下代码
// 则Qt保存为utf-8文件的时候，生成的程序没有乱码
#pragma execution_character_set("utf-8")

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
