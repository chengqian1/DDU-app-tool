#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QAction"
#include "QMessageBox"
#include "QFileDialog"
#include "QDebug"
#include <QProcess>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectFile()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp *.tar.gz)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    QString filen;
    for(auto tmp:fileNames)
    {
        qDebug()<<tmp<<endl;
        filen=filen+tmp;
    }
    qDebug()<<filen;
    ui->lineEdit->setText(filen);
}

void MainWindow::on_pushButton_clicked()
{
    selectFile();
}

void MainWindow::on_pushButton_2_clicked()//登录
{
    QString BatchFile = "login.bat "+ui->lineEdit_2->text()+" "+ui->lineEdit_3->text();
    QString Command = "cmd.exe /C "+BatchFile;
    QByteArray ba = Command.toLatin1();
    const char *c_str = ba.data();
    int value;
    value=system(c_str);

    if(value == 11)
    {
        qDebug()<<"log in failed";
        ui->textEdit->setText("登录失败，IP或密码错误");
    }
    else if(value == 22)
    {
        qDebug()<<"log in success";
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        ui->textEdit->setText("登录成功");
    }
}

void MainWindow::on_pushButton_3_clicked()//退出
{
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setReadOnly(false);
    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->label_3->clear();
}

void MainWindow::on_pushButton_4_clicked()//上传
{
    QString filename;
    filename=QDir::toNativeSeparators(ui->lineEdit->text());
    qDebug()<<"filename="<<filename;
    QString BatchFile = "download.bat "+ui->lineEdit_2->text()+" "+ui->lineEdit_3->text()+" "+filename; // Access path to the batch file.
    QString Command = "cmd.exe /C "+BatchFile;
    QByteArray ba = Command.toLatin1();
    const char *c_str = ba.data();
    int value;
    value=system(c_str);
    if(value == 1)
    {
        qDebug()<<"download failed";
        ui->label_3->setText("下载失败");
    }
    else if(value == 2)
    {
        qDebug()<<"download success";
        ui->label_3->setText("下载成功");
    }
}
