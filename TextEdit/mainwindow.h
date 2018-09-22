#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#pragma execution_character_set("utf-8")

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

private:
    bool FileMaybeSave();
    bool FileSave(const QString &filename);
    bool FileLoad(const QString &filename);
    void SetStatus(const char * status,const bool isInit = false);

private:
    Ui::MainWindow *ui;
    /* 文件操作相关 */
    bool isUntitled;
    QString curFile;
    QLabel  * label;
    QLabel * label2;
    QLabel * label3;
};

#endif // MAINWINDOW_H
