#include "gameworld.h"

//Gameworld::Gameworld(QWidget *parent) : QMainWindow(parent)
//{
//    setFixedSize(1365,1024);
//    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));
//}
Gameworld::Gameworld(QString bgpic,int i):level(i),bg(bgpic){
   //常规图标设置，大小设置
    setFixedSize(1365,1024);
    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));
    //this->paintmaster();



//    time=new QTimer(this);
//    connect(time,QTimer::timeout(),this,[=](){
//     update();
//    });
//    time->start(50);
//    time->setInterval(500);




}


void Gameworld::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    QPixmap pix;
//    pix.load(bg);
//    painter.drawPixmap(0, 0,this->width(),this->height(), pix);

    Master mm1(30,300,":/Gamepic/master00.gif");
    QPixmap  pix2;
    pix2.load(mm1.getpath());
    painter.drawPixmap(0,200,pix2.width(),pix2.height(),pix2);
}

//显示怪物函数
void Gameworld::paintmaster(){
    QPainter painter(this);
    //载入一个怪物并显示
    Master mm1(30,300,":/Gamepic/master00.gif");
    QPixmap  pix;
    pix.load(mm1.getpath());
    painter.drawPixmap(0,200+rand(),pix.width(),pix.height(),pix);
    this->repaint();

}
