#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QFrame>
#include <QMessageBox>
#include <QPushButton>
#include <QAbstractButton>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QStringList>
#include <QDateTime>
#include <QTimer>

#define APP_NAME    "Apaki 记事本"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 关闭状态栏
    // ui->statusBar->close();
    // 临时提示到底应该怎么用，为什么有时不能正常显示？
    // 问题好像是ui->statusBar->addWidget();不能正常显示导致的？
    // ui->statusBar->showMessage("欢迎使用 Apaki记事本!",1000);


    SetStatus("欢迎使用 Apaki记事本!",true);

    // --------------------------------------------
    //              文件操作相关
    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名"
    curFile = APP_NAME;
    // 初始化窗口标题为文件名
    setWindowTitle(curFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetStatus(const char * status,const bool isInit)
{
    // 状态栏显示内容
    if(isInit)
    {
        // Label1
        label = new QLabel(this);
        label->setText(status);
        label->setFrameStyle(QFrame::Box | QFrame::Sunken);
        label->setAlignment(Qt::AlignHCenter);

        // Label2
        label2 = new QLabel(this);
        label2->setText("<a href=\"https://www.baidu.com\">百度一下</a>");
        label2->setOpenExternalLinks(true);         //设置可以打开网页链接
        label2->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
        label2->setAlignment(Qt::AlignHCenter);

        // Lebel3
        label3 = new QLabel(this);
        label3->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
        label3->setAlignment(Qt::AlignHCenter);
        label3->setText("等待...");

        ui->statusBar->addPermanentWidget(label3,2);
        ui->statusBar->addPermanentWidget(label,4);
        ui->statusBar->addPermanentWidget(label2,2);
        setStatusBar(ui->statusBar);

        ui->statusBar->setSizeGripEnabled(false);
    }
    else
    {
        label3->setText(status);
        ui->statusBar->showMessage(status,2000);
    }
}

void MainWindow::FileNew()
{
    if(FileMaybeSave())
    {
        isUntitled = true;
        curFile = "未命名";
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::FileMaybeSave()
{
    // 如果文件被修改
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle("提示");
        box.setText(curFile + "尚未保存，是否保存？");
        QPushButton * BT_yes = box.addButton("是",QMessageBox::YesRole);
        QPushButton * BT_no = box.addButton("否",QMessageBox::RejectRole);

        if(box.clickedButton() == BT_yes)
        {
            return FileSave();
        }
        else if(box.clickedButton() == BT_no)
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
    // 设置文件过滤器
    QString filters("Text (*.txt);;"
                    "Python (*.py);;"
                    "Markdown (*.md);;"
                    "All (*.*)");
    QString filename = QFileDialog::getSaveFileName(this,"另存为",curFile,filters);
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
    QTextStream out(&file);

    // 鼠标等待图标
    QApplication::setOverrideCursor(Qt::WaitCursor);

    out<< ui->textEdit->toPlainText();
    // 鼠标恢复
    QApplication::restoreOverrideCursor();

    // 显示标题
    isUntitled = false;
    curFile = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(filename);
}

bool MainWindow::FileLoad(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"读取文件失败",
                             tr("无法读取文件%1：/n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // 读取文件的全部内容，并添加到编辑器中
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    // 显示标题
    curFile = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(filename);
    return true;
}


bool MainWindow::FileOpen222()
{
    // 打开文件选择对话框
    QFileDialog * fileDialog = new QFileDialog(this);
    // 配置标题为“选择文件”
    fileDialog->setWindowTitle("选择文件");
    // 设置当前路径为默认路径
    fileDialog->setDirectory(".");
    // 设置文件过滤器
    QStringList filters;
    filters << "Text (*.txt)"
            << "Python (*.py)"
            << "Markdown (*.md)"
            << "All (*.*)";
    fileDialog->setNameFilters(filters);
    // 设置是否可以选择多个文件，默认单个文件
    // 暂定先配置为单文件
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    // 设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);

    // 选择特定的文件
    QStringList filenames;
    if(fileDialog->exec())
    {
        filenames = fileDialog->selectedFiles();
    }

    // 打开文件
    if(!filenames.isEmpty())
    {
        QString filename = filenames.first();

        QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"读取文件失败",
                                 tr("无法读取文件%1：/n %2").arg(filename).arg(file.errorString()));
            return false;
        }

        QTextStream in(&file);
        ui->textEdit->setPlainText(in.readAll());

        // 显示标题
        isUntitled = false;
        curFile = QFileInfo(filename).canonicalFilePath();
        setWindowTitle(filename);

        ui->textEdit->setVisible(true);
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::on_actionNew_triggered()
{
    FileNew();
    SetStatus("文件新建成功");
}

void MainWindow::on_actionSave_triggered()
{
    FileSave();
    SetStatus("文件保存成功");
}

void MainWindow::on_actionSaveAs_triggered()
{
    FileSaveAs();
    SetStatus("文件另存为成功");
}

void MainWindow::on_actionOpen_triggered()
{
#if 0
    // 自己从网上学的方法，但并没有专业的严谨
    FileOpen222();
#else
    if(FileMaybeSave())
    {
        QString filename = QFileDialog::getOpenFileName(this);
        if(!filename.isEmpty())
        {
            isUntitled = false;
            FileLoad(filename);
            ui->textEdit->setVisible(true);
        }
    }
#endif
    SetStatus("文件打开成功");
}

void MainWindow::on_actionClose_triggered()
{
    if(FileMaybeSave())
    {
        ui->textEdit->setVisible(false);
    }

    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名"
    curFile = APP_NAME;
    // 初始化窗口标题为文件名
    setWindowTitle(curFile);

    // 退出状态
    SetStatus("文件关闭");
}

void MainWindow::on_actionExit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
    SetStatus("撤销");
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
    SetStatus("重做");
}
