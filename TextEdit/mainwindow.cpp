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
    label->setText(tr("   欢迎使用 Apaki记事本！"));
    ui->statusBar->addWidget(label);
    setStatusBar(ui->statusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}
