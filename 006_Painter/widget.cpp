#include "widget.h"
#include "ui_widget.h"
#include "QPainter"
#include "QPointF"
#include "QRectF"
#include "QPen"
#include "QColor"
#include "QRectF"
#include "QFont"
#include "QPainterPath"

#include "QLinearGradient"
#include "QRadialGradient"
#include "QConicalGradient"

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // -----------------------------------------------
    //           ----- 画笔画刷和基本图形 -----
    // 初始化画笔
    QPen pen;
    pen.setColor(QColor(0,0,255));
    pen.setWidth(5);
    pen.setStyle(Qt::DotLine);

    // 初始化画刷
    // 最后一个参数alpha是设置透明度的，取值范围也是0-255,0表示完全透明，而255表示完全不透明。
    QBrush brush(QColor(255,0,0,125));

    // 使用画笔
    painter.setPen(pen);
    painter.drawLine(QPointF(0,0),QPointF(100,100));
    // arc 弧线
    painter.drawArc(QRectF(100,0,100,100),30*16,300*16);
    // 椭圆
    painter.drawEllipse(QRectF(0,100,200,100));
    // 使用画刷
    painter.setBrush(brush);
    painter.drawRect(QRectF(0,100,200,100));
    painter.setPen(Qt::NoPen);



    // -----------------------------------------------
    //           ----- 渐变色操作 -----
    // 第一个点是确认起始点，另一个点可以用来确定渐变方向
    // 1.0 线性渐变色
    QLinearGradient linearGradient(QPoint(300,0),QPoint(300 + 100,100));
    linearGradient.setColorAt(0.2,Qt::white);
    linearGradient.setColorAt(0.4,Qt::green);
    linearGradient.setColorAt(0.6,Qt::yellow);
    linearGradient.setColorAt(1,QColor(255,0,0));
    // 选择扩散方式
    // linearGradient.setSpread(QGradient::RepeatSpread);
    // 扩散方式
    painter.setBrush(linearGradient);
    painter.drawEllipse(QRect(300,0,100,100));

    // 2.0 辐射渐变
    QRadialGradient radialGradient(QPoint(300+50,100+50),50,QPoint(300+50,100+50));
    radialGradient.setColorAt(0.2,Qt::white);
    radialGradient.setColorAt(0.4,Qt::green);
    radialGradient.setColorAt(0.6,Qt::yellow);
    radialGradient.setColorAt(1,QColor(255,0,0));
    painter.setBrush(radialGradient);
    painter.drawEllipse(QRect(300,100,100,100));

    // 3.0 角度渐变
    QConicalGradient conicalGradient(QPoint(300+50,200+50),360);
    conicalGradient.setColorAt(0.2,Qt::white);
    conicalGradient.setColorAt(0.4,Qt::green);
    conicalGradient.setColorAt(0.6,Qt::yellow);
    conicalGradient.setColorAt(1,QColor(255,0,0));
    painter.setBrush(conicalGradient);
    painter.drawEllipse(QRect(300,200,100,100));


    // -----------------------------------------------
    //           ----- 绘制文字 -----
    // 设置文字颜色
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawText(200,50,"Qt绘图练习");

    // 取消pen和Brush的特殊效果
    painter.setBrush(Qt::NoBrush);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    // 在写入内容之前，顺便将字体也配置一下
    QFont font("行楷",10,QFont::Bold,true);
    font.setUnderline(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    painter.setFont(font);

    // 将文件画在指定框内
    QRectF rect(0,200,200,100);
    painter.drawRect(rect);
    painter.drawText(rect,Qt::AlignCenter,"Qt写入特定地址");

    // -----------------------------------------------
    //           ----- 绘制路径 -----
    QPainterPath path;
    path.addRoundRect(QRect(220,100,60,30),50);
    path.addText(QPoint(220+20,100+20),font,"好");
    brush.setColor(Qt::yellow);
    painter.setBrush(brush);
    painter.drawPath(path);

    // 通过路径的方式，可以用来直接复制图形
    QPainterPath path2;
    path2.addPath(path);
    path2.translate(0,100);
    painter.drawPath(path2);

    // 可实现LineTo
    QPainterPath path3;
    path3.moveTo(200,250);
    path3.lineTo(300,300);
    painter.drawPath(path3);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(400,300);
    this->setWindowTitle("Qt绘图");
}

Widget::~Widget()
{
    delete ui;
}
