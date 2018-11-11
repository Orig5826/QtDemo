#include "widget.h"
#include "ui_widget.h"

#include "QPixmap"
#include "QPoint"
#include "QMouseEvent"
#include "QPainter"

#include "QFileDialog"
#include "QMessageBox"
#include "QString"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("涂鸦板");

    pix = QPixmap(600,600);
    pix.fill(Qt::black);

    pen.setColor(Qt::white);
    pen.setWidth(5);

    // 在窗口中添加按键清空画布的按键
    clearButton = new QPushButton(this);
    clearButton->move(650,500);
    clearButton->resize(100,60);
    clearButton->setText(("清空涂鸦板"));
    connect(clearButton,&QPushButton::clicked,this,&Widget::clear_paint);

    saveButton = new QPushButton(this);
    saveButton->move(650,400);
    saveButton->resize(100,60);
    saveButton->setText(("保存涂鸦板"));
    connect(saveButton,&QPushButton::clicked,this,&Widget::save_paint);
}

Widget::~Widget()
{
    delete clearButton;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    // 在指定的画布上根据鼠标前后两点绘制直线
    QPainter painter_pix(&pix);
    painter_pix.setPen(pen);
    if(lastPoint != endPoint)
    {
        painter_pix.drawLine(lastPoint,endPoint);

        // 绘制完毕，给前一个坐标赋值为后一个坐标，作为新的起点坐标
        lastPoint = endPoint;
    }

    // 在窗口中进行绘制
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

void Widget::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
    }
    endPoint = lastPoint;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint = event->pos();
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        update();
    }
}

void Widget::clear_paint()
{
    pix.fill(Qt::black);
    update();
}

void Widget::save_paint()
{
    QString name = "随手涂鸦.png";
    // 设置文件过滤器
    QString filters("Image (*.png *.jpg *.jpeg *.bmp);;"
                    "All (*.*)");
    QString filename = QFileDialog::getSaveFileName(this,"保存涂鸦",name,filters);
    pix.save(filename);
}
