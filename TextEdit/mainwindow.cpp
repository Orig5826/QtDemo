#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 状态栏显示内容
    QLabel * label = new QLabel(this);
    label->setText("   欢迎使用 Apaki记事本！ ");
    ui->statusBar->addWidget(label);
    setStatusBar(ui->statusBar);

    // --------------------------------------------
    //              文件操作相关
    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名"
    curFile = "未命名";
    // 初始化窗口标题为文件名
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
