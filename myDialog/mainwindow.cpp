#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QPalette>
#include <QFileDialog>
#include <QPicture>
#include <QPixmap>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    errordlg = new QErrorMessage(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QColor color = QColorDialog::getColor(Qt::red,this,tr("颜色对话框"),QColorDialog::ShowAlphaChannel);
//    qDebug()<<"color:"<<color;

    QColorDialog dialog(Qt::red,this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    dialog.exec();
    QColor color = dialog.currentColor();
    qDebug()<<"color:"<<color;

    QPalette pal = ui->pushButton->palette();
    pal.setColor(QPalette::Button,color);
    ui->pushButton->setPalette(pal);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("文件对话框"),"/home/gzb",tr("图片文件(*png *jpg)"));
    qDebug()<<"fileName:"<<filename;
    ui->label->setText(filename);

    QPixmap px;
    px.load(filename);
    ui->label_2->setPixmap(px);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->pushButton_3->setFont(font);
    }else{
        qDebug()<<tr("没有选择字体！");
    }


}

void MainWindow::on_pushButton_4_clicked()
{
    bool ok;
    QString string = QInputDialog::getText(this,
                tr("输入字符串对话框"),tr("请输入用户名"),QLineEdit::Normal,tr("admin"),&ok);
    if(ok){
        qDebug()<<"string:"<<string;
    }

    int value = QInputDialog::getInt(this,
                tr("输入整数对话框"),tr("请输入-1000到1000之间的数值"),100,-1000,1000,2,&ok);
    if(ok){
        qDebug()<<"value:"<<value;
    }

    double value2 = QInputDialog::getDouble(this,
                tr("输入浮点数对话框"),tr("请输入-1000到1000之间数值"),0.00,-1000,1000,2,&ok);
    if(ok){
        qDebug()<<"value2:"<<value2;
    }

    QStringList items;
    items << tr("num1")<< tr("num2");
    QString item = QInputDialog::getItem(this,
                tr("输入条目对话框"),tr("请选择或输入一个条目"),items,0,true,&ok);
    if(ok){
        qDebug()<<"item:"<<item;
    }

}



void MainWindow::on_pushButton_5_clicked()
{
    int ret1 = QMessageBox::question(this,tr("问题对话框"),tr("了解Qt吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ret1 == QMessageBox::Yes){
        qDebug()<<tr("问题！");
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    QProgressDialog dialog(tr("文件复制进度"),tr("取消"),0,500000,this);
    dialog.setWindowTitle(tr("进度对话框"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();
    for(int i=0; i<500000;i++){
        dialog.setValue(i);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled()){
            break;
        }
    }
    dialog.setValue(500000);
    qDebug()<<tr("复制结束！");

}

void MainWindow::on_pushButton_7_clicked()
{
    errordlg->setWindowTitle(tr("错误信息对话框"));
    errordlg->showMessage(tr("这里是出错信息！"));
}

QWizardPage *MainWindow::createPage1(){
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("介绍"));
    return page;
}

QWizardPage *MainWindow::createPage2(){
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("用户选择信息"));
    return page;
}

QWizardPage *MainWindow::createPage3(){
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("结束"));
    return page;
}



void MainWindow::on_pushButton_8_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("向导对话框"));
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.addPage(createPage3());
    wizard.exec();
}







