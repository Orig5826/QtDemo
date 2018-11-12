#include "widget.h"
#include "ui_widget.h"

#include "QPixmap"
#include "QPoint"
#include "QMouseEvent"
#include "QPainter"

#include "QFileDialog"
#include "QMessageBox"
#include "QString"
#include "QPalette"
#include "QRect"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{    
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("涂鸦板");
    // 设置控件颜色
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,Qt::gray);
     palette.setColor(QPalette::ButtonText,Qt::red);
    this->setPalette(palette);

    // -------------------------------------
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
    // 保存画布的按键
    saveButton = new QPushButton(this);
    saveButton->move(650,400);
    saveButton->resize(100,60);
    saveButton->setText(("保存涂鸦板"));
    connect(saveButton,&QPushButton::clicked,this,&Widget::save_paint);

    scale = 1;
    // 放大画布的按键
    zoomInButton = new QPushButton(this);
    zoomInButton->move(650,50);
    zoomInButton->resize(100,60);
    zoomInButton->setText(("放大"));
    connect(zoomInButton,&QPushButton::clicked,this,&Widget::zoomIn);
    // 缩小画布的按键
    zoomOutButton = new QPushButton(this);
    zoomOutButton->move(650,150);
    zoomOutButton->resize(100,60);
    zoomOutButton->setText(("缩小"));
    connect(zoomOutButton,&QPushButton::clicked,this,&Widget::zoomOut);
    
    // 绘制矩形
    isDrawing = false;
}

Widget::~Widget()
{
    delete clearButton;
    delete saveButton;
    delete zoomInButton;
    delete zoomOutButton;
    
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
#if 0
    // 在指定的画布上根据鼠标前后两点绘制直线
    QPainter painter_pix(&pix);
    painter_pix.setPen(pen);
    if(lastPoint != endPoint)
    {
        /*
         *  1.0 通过缩放窗口坐标系实现
            要注意的是，窗口坐标扩大了。则会出现坐标鼠标和绘制位置不一样的情况。
            因此，放大/缩小窗口坐标，则画布坐标也需要做相应修改
            若难以理解，可以想象(1,1)坐标的缩放情况。
            原始情况，鼠标在(1,1)附近作图。当窗口放大为原来的2倍时，则内容相对于窗口而言，
            相当于是(2,2)的位置，现在想要接着作图，在(2,2)处绘制，注意，此时画布的坐标系并没有改变，
            相当于是在画布的(2,2)作图，因此在窗口的显示上应该在(4,4)处显示了现在画的内容。
            所以，应该缩小画布坐标系
        */
        
        // 解决方法：窗口坐标
        painter_pix.scale(1/scale,1/scale);
        painter_pix.drawLine(lastPoint,endPoint);
        // 绘制完毕，给前一个坐标赋值为后一个坐标，作为新的起点坐标
        lastPoint = endPoint;
    }
    // 在窗口中进行绘制
    QPainter painter(this);
    // 在此处添加缩放功能
    painter.scale(scale,scale);
    painter.drawPixmap(0,0,pix);
#else
    /*
     * 缓冲画布操作方式
     * 这种临时保存的方式有弊端。
     */ 
    if(scale != 1)
    {
        // 临时画布，大小变化了scale
        QPixmap copyPix(pix.size()*scale);
        QPainter pter(&copyPix);
        pter.scale(scale,scale);
        // 将以前画布的内容，绘制到当前画布
        pter.drawPixmap(0,0,pix);
        // 将放大后的内容再复制回原来的画布
        pix = copyPix;
        scale = 1;
    }
    
    // 在指定的画布上根据鼠标前后两点绘制直线
    QPainter painter_pix(&pix);
    painter_pix.setPen(pen);
    
    // 解决方法：窗口坐标
    painter_pix.scale(scale,scale);
    if(lastPoint != endPoint)
    {
        /*
         *  2.0 通过缩放画布坐标系实现
            要注意的是，窗口坐标扩大了。则会出现坐标鼠标和绘制位置不一样的情况。
            因此，放大/缩小窗口坐标，则画布坐标也需要做相应修改
            若难以理解，可以想象(1,1)坐标的缩放情况。
            原始情况，鼠标在(1,1)附近作图。当窗口放大为原来的2倍时，则内容相对于窗口而言，
            相当于是(2,2)的位置，现在想要接着作图，在(2,2)处绘制，注意，此时画布的坐标系并没有改变，
            相当于是在画布的(2,2)作图，因此在窗口的显示上应该在(4,4)处显示了现在画的内容。
            所以，应该缩小画布坐标系
        */
        painter_pix.drawLine(lastPoint,endPoint);
        // 绘制完毕，给前一个坐标赋值为后一个坐标，作为新的起点坐标
        lastPoint = endPoint;
    }
  
#if 0
    // 在窗口中进行绘制
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
#else
    
    /*
     * 矩形的实现，在缩放的时候有问题，暂不知该如何修改。
     * 很尴尬...
     * 另外我本来想要实现，绘制矩形的时候出现轨迹，但始终不对。
     * 结果意外发现，我把MouseMoveEvent中的
     * if(event->buttons() & Qt::RightButton)
     * 错用为了
     * if(event->button() & Qt::RightButton)
     * 这么细节的东西，错了。复制过来就没有详细检查
     */
    // 使用鼠标右键绘制矩形
    // 缓冲技术
    int x,y,w,h;
    x = rightStart.x()/scale;
    y = rightStart.y()/scale;
    w = (rightEnd.x() - rightStart.x())/scale;
    h = (rightEnd.x() - rightStart.x())/scale;
    
    // 在窗口中进行绘制
    QPainter painter(this);
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,tempPix);
    }
    else
    {
        painter_pix.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,pix);
    }
#endif
#endif
}

void Widget::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        endPoint = lastPoint;
    }
    if(event->button() == Qt::RightButton)
    {
        rightStart = event->pos();
        rightEnd = rightStart;
        isDrawing = true;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint = event->pos();
        update();
    }
    
    if(event->buttons() & Qt::RightButton)
    {
        rightEnd = event->pos();
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
    if(event->button() == Qt::RightButton)
    {
        rightEnd = event->pos();
        isDrawing = false;
        update();
    }
}

void Widget::clear_paint()
{
    pix.fill(Qt::black);
    rightEnd = rightStart;
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

void Widget::zoomIn()
{
    scale *= 2;
    update();
}

void Widget::zoomOut()
{
    scale /= 2;
    update();
}

void Widget::drawRect()
{
    
}
