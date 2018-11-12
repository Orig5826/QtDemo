#ifndef WIDGET_H
#define WIDGET_H

// 当在windows上使用Qt的时候，添加如下代码
// 则Qt保存为utf-8文件的时候，生成的程序没有乱码
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QPen>
#include <QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QPixmap pix;
    QPoint lastPoint,endPoint;
    QPen pen;

    QPushButton * clearButton;
    QPushButton * saveButton;

    qreal scale;
    QPushButton * zoomInButton, * zoomOutButton;

    QPixmap tempPix;    //辅助画布
    bool isDrawing;
    QPoint rightStart,rightEnd;
    
    // 按键清空画布
    void clear_paint();
    void save_paint();
    void zoomIn();
    void zoomOut();
    void drawRect();
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
