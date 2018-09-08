#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qicon.h"
#include "qaction.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>

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


    // 5.0 代码编写布局管理器
    QPushButton *btn = new QPushButton(this);
    btn->setText(tr("布局管理"));
    QLineEdit *le = new QLineEdit(this);
    QTextEdit *te = new QTextEdit(this);

    //栅格管理器
    QGridLayout *layout = new QGridLayout(this);
    // 从0行0列开始，占据1行1列
    layout->addWidget(btn,0,0,1,1);
    layout->addWidget(le,0,1,1,2);

    // 添加TextEdit部件
    // 若通过ui添加了testEdit部件，则此处的部件te
    // 使用ui->testEdit即可
    layout->addWidget(te,1,0,2,3);
    // 布局
    ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
