#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include<QMdiSubWindow>
#include<QFileDialog>
#include<QMessageBox>
#include<QtWebEngineWidgets>
#include<QWebChannel>
#include"clicklabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool load(const QString &f);
private slots:
    void on_actionQuit_triggered();//退出应用
    void on_actionShowdock_triggered();//显示dock
    void on_actionnew_triggered();//新建文档（尚未存储）
    void on_actionOpen_triggered();//打开现有
    bool fileSave();
    bool fileSaveAs();

    void on_actionSave_triggered();

    void on_actionsaveanother_triggered();

    void on_actionqian_triggered();

    void on_actionhou_triggered();

    void on_actionexecu_triggered();
    void labe_click();

private:
    Ui::MainWindow *ui;
    QString newpath;
    CodeEditor *edzu;
    QMdiSubWindow *chdzu;
    QWebEngineView * wee;

    QToolBar *tb;
    clicklabel * zur;
    QLineEdit *zl;
    bool pan;

    bool MainWindow::maybeSave();//判别是否需要存  有变动就存
    void setCurrentFileName(const QString &fileName);
};

#endif // MAINWINDOW_H
