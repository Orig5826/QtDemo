#include "mainwindow.h"
#include <QApplication>
#include "logindlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 利用Accepted返回值判断按钮是否被按下
    LoginDlg  dlg;
    // 利用Accepted返回值判断按钮是否被按下
    if(dlg.exec() == QDialog::Accepted)
    {
        w.show();
        // 程序一直执行，直到主窗口关闭
        return a.exec();
    }
    else
    {
        //如果没有被按下，则不会进入主窗口，整个程序结束运行
        return 0;
    }
}
