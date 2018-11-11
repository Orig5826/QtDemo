#include "widget.h"
#include "ui_widget.h"

#include "QPaintEvent"
#include "QPainter"
#include "QPixmap"
#include "QRect"

#include "QPalette"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Qt绘画");
    this->resize(800,600);

    // 修改一下背景色
    this->setPalette(QPalette(QColor(220,220,255)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    /*
     * 另外，这里的this是本窗口实例上进行绘图的
     * 若是采用QPixmap、QImage等的方式，如新建一个QPixmap对象，则绘制的相对坐标是对QPixmap而言的。
     * 因此，若在QPixmap坐标系上发生旋转，则仅仅是针对该画布的，不影响this窗口实例的坐标系。
     */
    QPainter painter(this);
    QPixmap pix;
    // 注意此处的目录为什么要这样写
    // 是因为Qt他执行的时候，是在目录build...下执行的。
    // 因此我们调试的时候，修改为这样的路径。
    // 若发布程序，则按照正常路径(图片路径也需放在合适的路径下)即可
    pix.load("../007_Painter2/res/apaki.jpg");
    painter.drawPixmap(0,0,pix);             // 先看下原像素大小效果

    // 采用QRect的方式，似乎直接就有了缩放的效果
    // 图像大小似乎的Rect有关，自动进行了缩放
    //painter.drawPixmap(QRect(0,0,128,128),pix);

    // 转换坐标系，即将(256,256)设置为当前的原点(0,0)
    painter.translate(128,0);
    painter.drawPixmap(QRect(0,0,128,128),pix);
    // ----------------------------------------------------
    // 实现图像的大小缩放
    qreal width = pix.width();
    qreal height = pix.height();
    pix = pix.scaled(width*0.5,height*0.5,Qt::KeepAspectRatio);
    painter.drawPixmap(128,0,pix);
    // 使得原点复原
    painter.translate(-128,0);

    // ----------------------------------------------------
    // 注意此时的图片已经编程了64*64的了，因为上一步操作将其缩小了
    // 让图片中心作为旋转中心，顺时针旋转
    // 此时坐标系恢复起来很繁琐，需要思考半天。
    // 在这之后，学习了save和restore就明白了。特方便
    painter.translate(0,128);
    painter.translate(32,32);
    painter.rotate(90);
    painter.translate(-32,-32);
    painter.drawPixmap(0,0,pix);
    painter.rotate(-90);
    painter.translate(-64,-128);    // 注意：rotate旋转影响的是坐标轴，因此回到原始起点的方式要注意


    // 扭曲（横向，纵向） shear(sh,sv)
    painter.save();     // 保存坐标系状态,配合restore使用
    painter.translate(64,128);
    painter.shear(1, -1);   //painter.shear(1, 0);
    painter.drawPixmap(0,0,pix);
    // painter.shear(-1, 1);
    // painter.translate(-64,-128);     // 这种比较low的方式，就不使用了
    painter.restore();  // 配合save使用，方便自动恢复到原始坐标系状态

    painter.drawText(0,14,"Qt原点");

    // ----------------------------------------
    // 新建画布作为它独特的坐标系统
    QPixmap drawpix(256,256);
    drawpix.fill(Qt::black);
    QPainter pix_painter(&drawpix); // 以画布drawpix作为坐标系统
    pix_painter.drawPixmap(QRect(64,64,128,128),pix);
    painter.drawPixmap(256,256,drawpix);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}







