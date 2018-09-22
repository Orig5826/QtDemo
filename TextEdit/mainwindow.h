#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#pragma execution_character_set("utf-8")

/*
 * \breaf 类的前置声明
 *一般用于私有类的方法或者属性，且必须为引用或者指针类型
 */
class QLabel;
class Dialog;
class QLineEdit;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /* 文件操作相关 */
    void FileNew();
    bool FileSave();
    bool FileOpen222();
    bool FileSaveAs();

    void TimeUpdate();

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFind_triggered();

    void showFindText();

private:
    bool FileMaybeSave();
    bool FileSave(const QString &filename);
    bool FileLoad(const QString &filename);
    void SetStatus(const char * status,const bool isInit = false);
    /* 查找对话框 Init*/
    void findDlgInit();
private:
    Ui::MainWindow *ui;
    /* 文件操作相关 */
    bool isUntitled;
    QString curFile;    //!< 当前文件名
    QLabel  * label;    //!<
    QLabel * label2;    //!<
    QLabel * label3;    //!< 3个状态栏

    //!< 查找接口相关
    QLineEdit * findLineEdit;
    QDialog * findDlg;
};

#endif // MAINWINDOW_H
