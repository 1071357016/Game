#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypushbutton.h"
#include<QPainter>
MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //固定窗口大小和显示图标
    setFixedSize(1365,1024);
    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));
    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });
    //开始按钮实现
    MyPushButton *startbutton=new MyPushButton(":/Gamepic/knife.png");
    startbutton->setParent(this);
      //设置位置
    //startbutton->move(625,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置背景
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Gamepic/grass.png");
    painter.drawPixmap(0, 0,this->width(),this->height(), pix);
}


