#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qicon.h"
#include "qaction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction * openAction = new QAction(tr("打开&(O)"),this);
    QIcon icon(":/myimages/images/fileopen.png");
    // 添加图标
    openAction->setIcon(icon);
    // 设置快捷键
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    // 在文件菜单中设置重新打开的动作
    ui->menu_F->addAction(openAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
