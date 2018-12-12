#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QUrl>
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wee=new QWebEngineView();
    edzu=new CodeEditor(ui->mdiArea);

    edzu->appendPlainText("<html>\n"
                          "<head>\n"
                          "<style type=""text/css"">\n"
                          "</style>\n"
                          "<script type=""text/JavaScript"">\n"
                          "</script>\n"
                          "</head>\n"
                          "<body>\n"
                          "</body>\n"
                          "</html>");
    edzu->document()->setModified(false);
    chdzu= ui->mdiArea->addSubWindow(edzu);
    //titlenum[index]=index;
    chdzu->setWindowTitle(QStringLiteral("new-file"));
    chdzu->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 显示子窗口
    //child->showMaximized();
    chdzu->showMaximized();
    newpath="";
    this->setWindowTitle(tr("%1[*] - %2").arg("untitled.html", QCoreApplication::applicationName()));
    this->setWindowModified(false);
    pan=true;
/************************************///添加工具栏。代码能添加多个工具栏
    tb =new QToolBar(this);
    zur=new clicklabel(this);
    zur->setText("URL:");
    tb->addWidget(zur);
    zl=new QLineEdit(this);
    zl->setReadOnly(pan);
    tb->addWidget(zl);
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    this->addToolBarBreak(Qt::TopToolBarArea);
    this->addToolBar(tb);

    connect(zur,SIGNAL(Clicked()),this,SLOT(labe_click()));


    ui->dockWidget->close();
    QLabel *permanent = new QLabel(this);
    // 标签样式
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    // 显示信息
    permanent->setText("version_1.0  Z-Pike  2017.09.26");
    permanent->setStatusTip(QStringLiteral("版本 作者 完成时间"));
    // 将标签设置为永久部件
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
    wee->close();
}

void MainWindow::on_actionQuit_triggered()//quit
{
    qApp->quit();
}

void MainWindow::on_actionShowdock_triggered()//显示助手
{
    ui->dockWidget->show();
}

void MainWindow::on_actionnew_triggered()//new file  暂时设计为只单编辑框
{
    if (maybeSave()) {
        edzu->clear();
        setCurrentFileName(QString());
    }
}
void MainWindow::on_actionOpen_triggered()//打开文档
{
    QString tat;
    if (maybeSave())
    {
        // edzu->clear();
        tat = QFileDialog::getOpenFileName(this,QStringLiteral("打开文档"),"",tr("webpage(*.html *.js *.css);;TXT(*.txt)"));
        if(tat!="")
        {
            newpath=tat;
        }
        if (load(newpath))
        {
            ui->statusBar->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(newpath)));
            zl->setText(newpath);
        }
        else
            ui->statusBar->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(newpath)));
    }

}
bool MainWindow::maybeSave()
{
    if (!edzu->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}
void MainWindow::setCurrentFileName(const QString &fileName)
{
    newpath = fileName;
    edzu->document()->setModified(false);

    QString shownName;
    if (newpath.isEmpty())
        shownName = "untitled.html";
    else
        shownName = QFileInfo(fileName).fileName();

    this->setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    this->setWindowModified(false);
}
bool MainWindow::fileSave()
{
    if (newpath.isEmpty())
        return fileSaveAs();
    if (newpath.startsWith(QStringLiteral(":/")))
        return fileSaveAs();
    QFile file(newpath);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
    }
    //QTextStream in(&file);
    //in << edzu->document()->toPlainText();
    file.resize(0);//清空原文件  消除原文件内容的干扰
    file.write( edzu->document()->toPlainText().toLocal8Bit().data(),edzu->document()->toPlainText().toLocal8Bit().length());
    file.close();
    //qDebug()<<edzu->document()->toPlainText();
    //bool success = writer.write((edzu->document()));
    bool success = true;
    if (success)
    {
        edzu->document()->setModified(false);
        statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(newpath)));
    }
    else
    {
        statusBar()->showMessage(tr("Could not write to file \"%1\"")
                                 .arg(QDir::toNativeSeparators(newpath)));
    }
    return success;
}
bool MainWindow::fileSaveAs()//文件原本不存在 创建文件再用save
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
//    QStringList mimeTypes;
//    mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
//    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.setNameFilter(tr("webpage (*.html *.js *.css);; text (*.txt);; All files (*.*)"));
//    fileDialog.setDefaultSuffix("html");
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    zl->setText(fn);
    return fileSave();
}
bool MainWindow::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QString str = QString::fromLocal8Bit(data);
    edzu->setPlainText(str);

    setCurrentFileName(f);
    return true;
}
void MainWindow::on_actionSave_triggered()//save覆盖源文件
{
    fileSave();
}

void MainWindow::on_actionsaveanother_triggered()//另存为
{
    fileSaveAs();
}

void MainWindow::on_actionqian_triggered()
{
    edzu->undo();
}

void MainWindow::on_actionhou_triggered()
{
    edzu->redo();
}

void MainWindow::on_actionexecu_triggered()//展示webpage
{
    if (edzu->document()->isModified())//文档已变动 需要存储 默认存
    {
        fileSave();
        if(zl->text()=="")
        {
            QMessageBox::warning(this, QCoreApplication::applicationName(),
                                 tr("No Target!\n"),
                                 QMessageBox::Ok);
            return;
        }
        wee->load(QUrl(zl->text()));
        //wee->raise();
        wee->activateWindow();
        wee->showNormal();
    }else
    {
        if(zl->text()=="")
        {
            QMessageBox::warning(this, QCoreApplication::applicationName(),
                                 tr("No Target!\n"),
                                 QMessageBox::Ok);
            return;
        }
        wee->load(QUrl(zl->text()));
        //wee->raise();
        wee->activateWindow();
        wee->showNormal();
    }
}
void MainWindow::labe_click()
{
    pan=!pan;
    zl->setReadOnly(pan);

}
