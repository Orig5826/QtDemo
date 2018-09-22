#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    bool FileSaveAs();
private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

private:
    bool FileMaybeSave();
    bool FileSave(const QString &filename);

private:
    Ui::MainWindow *ui;
    /* 文件操作相关 */
    bool isUntitled;
    QString curFile;
};

#endif // MAINWINDOW_H
