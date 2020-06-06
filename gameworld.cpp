#include "gameworld.h"
#include"mainwindow.h"


//定义鼠标点击的区域，有一说一 这个方法是从网上找的，ev
#define ClickRegion(X, Width, Y, Height)    \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
 ev->y() >= (Y) && ev->y() <= (Y) + (Height))


Gameworld::Gameworld(int i):level(i){
   //游戏界面图标设置，大小固定设置
    setFixedSize(1040, 640);//为了方便设置地图修改了界面大小
    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));






//    time=new QTimer(this);
//    connect(time,QTimer::timeout(),this,[=](){
//     update();
//    });
//    time->start(50);
//    time->setInterval(500);




}

//绘制地图，用不同的三个数组，根据界面大小，一个小格40*40，不同数字载入不同小方块
//暂定 0 载入草地  1 载入路  2 载入炮坑 9不载入为了占四个格 3家  4 花花
void Gameworld::paintmap(QPainter&p){
    //地图数组  第一关
    int Map1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        4, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
    };


    int Map[16][26];    //用于拷贝不同的地图，根据关卡变化
    //实现
    switch (level)
    {
    case 1:
        memcpy(Map, Map1, sizeof(Map));
        break;

    default:
        break;
    }

    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:     //画上草
                p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/cao.png"));
                break;
            case 1:     //画上路
                p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/road.png"));
                break;
            case 2:     //画上塔坑
                p.drawPixmap(i * 40, j * 40, 80, 80,QPixmap(":/Gamepic/pit.png"));
                break;

            case 3://记录家的坐标，留到最后画
                p.drawPixmap(i * 40, j * 40, 80, 80,
                    QPixmap(":/Gamepic/road.png"));  //暂时画上草，最后添上家 防止背景空白
                homepos->x=i*40;homepos->y=j*40;
                break;
            case 4: //画上花花
                p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/flower.png"));
                break;
            }
        //画上家
            p.drawPixmap(homepos->x, homepos->y, 120, 120, QPixmap(":/Gamepic/home.png")); //最后画出家
         }
}

//绘制怪物

//void Gameworld::paintmaster(){
//    QPainter painter(this);
//    //载入一个怪物并显示
//    Master mm1(30,300,":/Gamepic/master00.gif");
//    QPixmap  pix;
//    pix.load(mm1.getpath());
//    painter.drawPixmap(0,200+rand(),pix.width(),pix.height(),pix);
//    this->repaint();

//}

void Gameworld::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    paintmap(painter);


}

//鼠标点击事件处理函数
void Gameworld::mouseClickEvent(QMouseEvent *ev){
     //按左键才有用,别的键没用
    if (ev->button() != Qt::LeftButton)
        return;

     //



}

