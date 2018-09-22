#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QAbstractButton>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>

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

void MainWindow::FileNew()
{

}

bool MainWindow::FileMaybeSave()
{
    // 如果文件被修改
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle("提示");
        box.setText(curFile + "尚未保存，是否保存？");
        QAbstractButton *ABT_yes,*ABT_no;
        // 这样不会有问题吗？
        box.addButton(ABT_yes,QMessageBox::YesRole);
        box.addButton(ABT_no,QMessageBox::RejectRole);

        if(box.clickedButton() == ABT_yes)
        {
            return FileSave();
        }
        else
        {
            return false;
        }
    }
    // 如果文档没有被修改，那么返回true
    return true;
}

bool MainWindow::FileSave()
{
    if(isUntitled)
    {
        return FileSaveAs();
    }
    else
    {
        return FileSave(curFile);
    }
    return true;
}

bool MainWindow::FileSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this,"另存为",curFile);
    if(filename.isEmpty())
    {
        return false;
    }
    return FileSave(filename);
}

bool MainWindow::FileSave(const QString &filename)
{
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"写入警告",
                             tr("无法写入文件%1：/n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    // 鼠标等待图标
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<< ui->textEdit->toPlainText();
    // 鼠标恢复
    QApplication::restoreOverrideCursor();
    // 获取文件标准路径
    isUntitled = false;
    curFile = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(filename);
}

void MainWindow::on_actionNew_triggered()
{
    FileNew();
}

void MainWindow::on_actionSave_triggered()
{
    FileSave();
}

void MainWindow::on_actionSaveAs_triggered()
{
    FileSaveAs();
}
