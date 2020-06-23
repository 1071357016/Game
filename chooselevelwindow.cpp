#include "chooselevelwindow.h"

ChooseLevelwindow::ChooseLevelwindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1365,1024);
    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));

    MyPushButton *level1button=new MyPushButton(":/Gamepic/level.png");
    MyPushButton *level2button=new MyPushButton(":/Gamepic/level2.png");
    MyPushButton *level3button=new MyPushButton(":/Gamepic/level3.png");

    //关卡一
    level1button->setParent(this);
    level1button->move(200,200);
    // Gameworld *gameworld1;

    //点击按键进入游戏世界1
    connect(level1button,&MyPushButton::clicked,this,[=]{
        //切换到选择关卡场景
        //this->hide();
        Gameworld *gameworld1;
        gameworld1=new Gameworld(1);
        gameworld1->show();//展示第一关游戏世界1

    });



    //关卡二
    level2button->setParent(this);
    level2button->move(600,200);
    connect(level2button,&MyPushButton::clicked,this,[=]{
        //切换到选择关卡场景
        //this->hide();
        Gameworld *gameworld2;
        gameworld2=new Gameworld(2);
        gameworld2->show();//展示第一关游戏世界1
    });

    //关卡三
    level3button->setParent(this);
    level3button->move(1000,200);
    connect(level3button,&MyPushButton::clicked,this,[=]{
        //切换到选择关卡场景
        //this->hide();
        Gameworld *gameworld3;
        gameworld3=new Gameworld(3);
        gameworld3->show();//展示第一关游戏世界1
    });

}

void ChooseLevelwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Gamepic/grass2.png");
    painter.drawPixmap(0, 0,this->width(),this->height(), pix);


}
