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
    //菜单栏退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });
    //尝试使用我自己的button类实现开始按钮
      MyPushButton *startbutton=new MyPushButton(":/Gamepic/begin.tga");
      startbutton->setParent(this);
      //设置位置
      startbutton->move(625,300);
      choosescene=new ChooseLevelwindow;


      connect(startbutton,&MyPushButton::clicked,this,[=]{
          //切换到选择关卡场景
          //this->hide();
          choosescene->show();
      });

    //Qpushbutton方法设置开始按键
//        QPushButton *beginbtn = new QPushButton;//创建按钮对象
//        beginbtn->setParent(this);//在当前窗口显示
//        beginbtn->move(630,600);
//        //beginbtn->setStyleSheet(rgb(255, 128, 64));
//        //beginbtn->setStyleSheet(":/Gamepic/begin.tga");
//        beginbtn->setText("BEDIN");
//        beginbtn->setFixedSize(200,50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置进入时的游戏背景
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Gamepic/grass.png");
    painter.drawPixmap(0, 0,this->width(),this->height(), pix);
    //粘贴标题
    QPixmap pix2;
    pix2.load(":/Gamepic/BIGTITLE.png");
    painter.drawPixmap(350,600,700,200,pix2);

}


