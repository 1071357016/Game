#include "gameworld.h"
#include"mainwindow.h"


//定义鼠标点击的区域  X Y为区域左上角坐标，width height为区域宽高，有一说一， 这个方法是从网上找的，因为只有一个鼠标点击函数，ev是鼠标
#define ClickRegion(X, Width, Y, Height)    \
(ev->x() >= (X) && ev->x() <= (X) + (Width) && \
 ev->y() >= (Y) && ev->y() <= (Y) + (Height))


Gameworld::Gameworld(int i):level(i){
   //游戏界面图标设置，大小固定设置
    setFixedSize(1040, 640);//为了方便设置地图修改了界面大小
    setWindowIcon(QIcon(":/Gamepic/bgtry.png"));

    //播放背景音乐
    player->setMedia(QUrl("qrc:/Gamepic/Music2.mp3"));
    player->setVolume(100);
    player->play();



    //胜利及失败标签
    QPalette pe3;
    pe3.setColor(QPalette::WindowText,Qt::yellow);
    winlable->setPalette(pe3);
    winlable->move(330, 180);
    winlable->setFont(QFont("华康海报体W12(P)", 110));
    winlable->setText(QString("WIN"));
     winlable->hide();

     pe3.setColor(QPalette::WindowText,Qt::red);
    loselable->setPalette(pe3);
    loselable->move(220, 180);
    loselable->setFont(QFont("华康海报体W12(P)", 110));
    loselable->setText(QString("LOSE"));
    loselable->hide();


    //我方生命值标签
    //QLabel *lifelable = new QLabel(this);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    lifelable->setPalette(pe);
    lifelable->setGeometry(20, 10, 180, 35);
    lifelable->setFont(QFont("华康海报体W12(P)", 20));
    lifelable->setText(QString("生命：%1").arg(mylife));


    //我方金钱标签
   // QLabel *moneylable = new QLabel(this);
    QPalette pe2;
    pe2.setColor(QPalette::WindowText,Qt::yellow);
    moneylable->setPalette(pe2);
    moneylable->setGeometry(700, 10, 210, 35);
    moneylable->setFont(QFont("华康海报体W12(P)", 20));
    moneylable->setText(QString("金钱：%1").arg(money));
    //每时每刻产生构造怪物产生路径并传入怪物,时间间隔控制产生怪物间隔
    //QTimer* timer2 = new QTimer(this);
    timer2->start(3000);

    connect(timer2,&QTimer::timeout,[=]()
    {    //根据关卡地图传入不同路径点
        switch (level) {
        case 1:
        {
            //设置路径点  第一关没有拐弯的地方，第一个拐点就是出发点，最后一个拐点即 家的坐标。
           Point* path1[] = {/*new Point(0,260),*/new Point(960, 280)};
           Point* path2[] = {/*new Point(0,290),*/ new Point(960, 280)};
            //怪物的起始点数组MonsterStart，都规定好的
            Point start1(0,260);
            Point start2(0,290);
            Point MonsterStart[]={start1,start2};

            //每条路径的结点个数,第一关两条路径都是一样的，相当于都是2个拐点
           int PathPoint[2] = {1,1};
           ProduceMonster(path1,path2,MonsterStart,PathPoint);

            break;
        }
        case 2:
        {
            //设置路径点  第一关没有拐弯的地方，第一个拐点就是出发点，最后一个拐点即 家的坐标。
           Point* path1[] = {new Point(140, 140),new Point(140,300),new Point(400,300),new Point(380,160),new Point(740,160),new Point(740,500),new Point(900,500)};
           Point* path2[] = {new Point(380,160),new Point(740,160),new Point(740,500),new Point(900,500)};
            //怪物的起始点数组MonsterStart，都规定好的
            Point start1(0,140);
            Point start2(400,640);
            Point MonsterStart[]={start1,start2};

            //每条路径的结点个数,第一关两条路径都是一样的，相当于都是2个拐点
           int PathPoint[2] = {7,4};
           ProduceMonster(path1,path2,MonsterStart,PathPoint);

            break;
        }
        case 3:
        {
            //设置路径点  第一关没有拐弯的地方，第一个拐点就是出发点，最后一个拐点即 家的坐标。
           Point* path1[] = {new Point(160, 100),new Point(740,100),new Point(740,500),new Point(1000,500)};
           Point* path2[] = {new Point(90,260),new Point(90,540),new Point(380,540),new Point(380,260),new Point(740,260),new Point(740,500),new Point(1000,500)};
            //怪物的起始点数组MonsterStart，都规定好的
            Point start1(160,0);
            Point start2(0,280);
            Point MonsterStart[]={start1,start2};

            //每条路径的结点个数,第一关两条路径都是一样的，相当于都是2个拐点
           int PathPoint[2] = {4,7};
           ProduceMonster(path1,path2,MonsterStart,PathPoint);

            break;
        }

      }
    });



    //每时每刻画怪物+判断怪物进没进入炮塔的攻击区域 进入发射子弹+
    //QTimer* timer3 = new QTimer(this);
    timer3->start(100);

    connect(timer3,&QTimer::timeout,[=]()
    {


        for (auto aMonster=MonsterVec.begin();aMonster!= MonsterVec.end(); aMonster++)
           {
            //判断怪物生命值
            if((*aMonster)->getlife()<=0)
            {
               money=money+(*aMonster)->getvalue();
               moneylable->setText(QString("金钱：%1").arg(money));//刷新标签
               delete *aMonster;
               MonsterVec.erase(aMonster);
               break;
            }
            //通过调用怪物移动函数刷新怪物位置
             if((*aMonster)->MonsterMove()) //怪物闯入家
              {
                      delete *aMonster;
                            MonsterVec.erase(aMonster);         //怪物走到终点则删除这个怪物
                            player2->setMedia(QUrl("qrc:/Gamepic/hurt2.mp3"));
                            player2->setVolume(100);
                            player2->play();
                                this->mylife--;                         //我们的生命数量-1
                               lifelable->setText(QString("生命：%1").arg(mylife));

                               if (mylife<= 0)
                               {
                                    player->stop();
                                   player3->setMedia(QUrl("qrc:/Gamepic/lose.mp3"));
                                   player3->setVolume(100);
                                   player3->play();
                                   MonsterVec.clear();
                                   loselable->show();
                                   flag=1;
                                   timer2->stop();
                                   QTimer* timer4= new QTimer(this);
                                   timer4->start(4000);

                                   connect(timer4,&QTimer::timeout,[=](){

                                       this->close();
                                   }
                                  );  //生命值为0时关闭该窗口
                               }
                break;
               }


          }


        for (auto aTower:TowerVec)      //遍历防御塔
        {
            //先判断若当前防御塔没有目标，则创建目标
            if (aTower->GetAimMonster()==NULL)
            {
                for(int i =MonsterVec.size()- 1;i>=0; i--)
                    //这里以防御塔中心点和怪物中心点判断  且怪物生命值要大于0
                    if (Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,MonsterVec.at(i)->getx()+MonsterVec.at(i)->getwidth()/2,MonsterVec.at(i)->gety()+MonsterVec.at(i)->getheight()/2)<aTower->GetShootrange()+0.1)
                      if(MonsterVec.at(i)->getlife()>0)
                    {
                        aTower->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        qDebug()<<"Aim monster get!";
                        break;  //找到后跳出循环
                    }
            }

            //判断若当前防御塔拥有目标//目标在攻击范围内
           if(aTower->GetAimMonster()!=NULL)
                {
                       //目标在攻击范围内
                   if (Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,aTower->GetAimMonster()->getx()+aTower->GetAimMonster()->getwidth()/2,aTower->GetAimMonster()->gety()+aTower->GetAimMonster()->getheight()/2)<=aTower->GetShootrange())
                                {
                               //拥有目标时一直创建子弹
                                   //qDebug()<<"Bullet is doing";
                                   //  aTower->InsertBullet();
                                       if(aTower->ifTowerAttack())
                                       {
                                           aTower->GetAimMonster()->SetLife(aTower->GetAttack());
                                                if(aTower->GetAimMonster()->getlife()<0)
                                                {
                                                      //MonsterVec.erase(aTower->GetAimMonster());
                                                       aTower->SetAimsMonster(NULL);
                                                }
                                       }

                                 }
                 }
           //判断若当前防御塔拥有目标,超过距离将目标怪物设为空
           if(aTower->GetAimMonster()!=NULL)
                  {
                      if(Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,aTower->GetAimMonster()->getx()+aTower->GetAimMonster()->getwidth()/2,aTower->GetAimMonster()->gety()+aTower->GetAimMonster()->getheight()/2)>aTower->GetShootrange())
                                    aTower->SetAimsMonster(NULL);

                        // }
                  }
           //qDebug()<<"BulletMove";
         // aTower->BulletMove();
        }




       update();

    }
    );

}




//生成怪物事件
void Gameworld::ProduceMonster(Point** Path1,Point** Path2,Point* StartPoint, int* NumOfPoint){

if(level==1)
 {
    if(this->TimeMonsterNum>=0&&this->TimeMonsterNum<=6)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);

    }
    if(this->TimeMonsterNum>6&&this->TimeMonsterNum<=12)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],2);

    }
    if(this->TimeMonsterNum>12&&this->TimeMonsterNum<=17)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],3);

    }
    if(this->TimeMonsterNum>17&&MonsterVec.empty()&&flag==0)
    {
        winlable->show();
        player->stop();
        player4->setMedia(QUrl("qrc:/Gamepic/win.mp3"));
        player4->setVolume(100);
        player4->play();

        QTimer* timer5= new QTimer(this);
        timer5->start(3000);

        connect(timer5, &QTimer::timeout,this,[=](){

            timer2->stop();
            timer3->stop();
         player4->stop();
         this->close();
        }
       ); //关闭窗口

    }
   }

if(level==2)
 {
    if(this->TimeMonsterNum>=0&&this->TimeMonsterNum<=5)
    {
         InsertMonster(Path2,StartPoint[1],NumOfPoint[1],1);
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);

    }
    if(this->TimeMonsterNum>5&&this->TimeMonsterNum<=12)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],3);

    }
    if(this->TimeMonsterNum>12&&this->TimeMonsterNum<=20)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],3);

    }
    if(this->TimeMonsterNum>20&&MonsterVec.empty()&&flag==0)
    {
        winlable->show();
        player->stop();
        player4->setMedia(QUrl("qrc:/Gamepic/win.mp3"));
        player4->setVolume(100);
        player4->play();
        QTimer* timer5= new QTimer(this);
        timer5->start(3000);

        connect(timer5,&QTimer::timeout,this,[=](){
          player4->stop();
          timer2->stop();
          timer3->stop();
            this->close();
        }
       ); //关闭窗口

      }
   }
if(level==3)
 {
    if(this->TimeMonsterNum>=0&&this->TimeMonsterNum<=7)
    {
        //开始游戏怪物数目1~7时，只有一条路产生编号1的小黑黑怪
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);
          InsertMonster(Path2,StartPoint[1],NumOfPoint[1],1);
    }
    if(this->TimeMonsterNum>7&&this->TimeMonsterNum<=14)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],3);

    }
    if(this->TimeMonsterNum>14&&this->TimeMonsterNum<=18)
    {

        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],3);
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],2);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],4);

    }
    if(this->TimeMonsterNum>18&&this->TimeMonsterNum<=24)
    {
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],4);
        InsertMonster(Path2,StartPoint[1],NumOfPoint[1],4);
    }
    if(this->TimeMonsterNum>24&&MonsterVec.empty()&&flag==0)
    {
        winlable->show();
        player->stop();
        player4->setMedia(QUrl("qrc:/Gamepic/win.mp3"));
        player4->setVolume(100);
        player4->play();
        QTimer* timer5= new QTimer(this);
        timer5->start(3000);

        connect(timer5,&QTimer::timeout,this,[=](){
      player4->stop();
      timer2->stop();
      timer3->stop();
         this->close();
        }
       ); //关闭窗口


    }
   }
    TimeMonsterNum++;
    return;



}

//插入怪物事件
void Gameworld::InsertMonster(Point** path,Point& startpoint,int numofguaidian,int Monsterid){

    this->MonsterVec.push_back(new Monster(startpoint.x,startpoint.y,path,numofguaidian,Monsterid));
}

//绘制地图，用不同的三个数组，根据界面大小，一个小格40*40，不同数字载入不同小方块
void Gameworld::paintmap(QPainter &p){
    //地图数组  第一关
    //暂定 0 载入草地  1 载入路  2 载入炮坑 9不载入为了占四个格 3家  4 花花
    int Map1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        4, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 2, 9, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
    };


    int Map2[16][26]={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,
        0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6,
        1, 1, 1, 1, 1, 0, 0, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 2, 9, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 6, 0, 0, 0,
        0, 0, 0, 1, 1, 9, 9, 0, 6, 1, 1, 0, 0, 0, 0, 0, 2, 9, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 6, 0, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 6, 0, 6, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 2, 9, 1, 1, 0, 0, 6, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 6, 0, 0, 0, 6, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 9, 0, 0, 0, 0,
        0, 6, 0, 0, 0, 0, 0, 6, 0, 1, 1, 0, 0, 6, 0, 0, 0, 0, 1, 1, 9, 9, 6, 3, 0, 0,
        0, 0, 6, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 9, 1, 1, 1, 1, 1, 1, 1, 1,
        6, 6, 0, 0, 6, 0, 0, 0, 0, 1, 1, 2, 9, 6, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1,
        6, 6, 0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 9, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        6, 0, 6, 0, 0, 0, 6, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0,
    };

    int Map3[16][26]={
        0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 6, 7, 7, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0,
        0, 0, 0, 1, 1, 6, 6, 0, 6, 0, 0, 7, 7, 0, 0, 6, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,
        6, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 9, 0, 0, 0, 0,
        0, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 6, 0, 0, 6,
        0, 0, 0, 2, 9, 0, 6, 0, 0, 0, 0, 7, 7, 2, 9, 6, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 7, 7, 9, 9, 0, 0, 0, 1, 1, 0, 0, 0, 6, 0, 0,
        1, 1, 1, 1, 0, 0, 0, 2, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 0, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 7, 7, 6, 0, 6, 2, 9, 1, 1, 0, 0, 0, 0, 0, 0,
        6, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 7, 7, 6, 0, 0, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 6, 0, 0, 1, 1, 7, 7, 0, 0, 0, 0, 0, 1, 1, 2, 9, 0, 0, 0, 0,
        0, 6, 1, 1, 2, 9, 0, 6, 0, 1, 1, 2, 9, 7, 0, 0, 0, 0, 1, 1, 9, 9, 6, 3, 0, 0,
        0, 0, 1, 1, 9, 9, 0, 0, 0, 1, 1, 9, 9, 7, 7, 0, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 6, 7, 7, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 6, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        6, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 6, 0, 0, 0, 0, 0,
    };



    //用于拷贝不同的地图，根据关卡变化
    int Map[16][26];    //用于拷贝不同的关卡数组

    //实现
    switch (level)
    {
    case 1:
        memcpy(Map, Map1, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map2,sizeof(Map));
        break;
   case 3:
        memcpy(Map,Map3,sizeof(Map));
        break;
    default:
        break;
    }


    if(level==1)
    {
    for (int j = 0; j < 16; j++)
        for (int i = 0; i<26;i++)
        {
            switch (Map[j][i])
            {
            case 0:     //画上草
                p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/cao.png"));
                break;
            case 1:     //画上路
                p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/road.png"));
                break;
            case 2:     //画上塔坑,同时初始化塔坑数组的一个成员并插入数组
                p.drawPixmap(i * 40, j * 40, 80, 80,QPixmap(":/Gamepic/pit.png"));
                TowerpitVec.push_back(new TowerPit(i * 40, j * 40));
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
    if(level==2)
    {
        for (int j = 0; j < 16; j++)
            for (int i = 0; i<26;i++)
            {
                switch (Map[j][i])
                {
                case 0:     //画上树
                    p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/tree2.png"));
                    break;
                case 1:     //画上路
                    p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/road.png"));
                    break;
                case 2:     //画上塔坑,同时初始化塔坑数组的一个成员并插入数组
                    p.drawPixmap(i * 40, j * 40, 80, 80,QPixmap(":/Gamepic/pit.png"));
                    TowerpitVec.push_back(new TowerPit(i * 40, j * 40));
                    break;

                case 3://记录家的坐标，留到最后画
                    p.drawPixmap(i * 40, j * 40, 80, 80,
                        QPixmap(":/Gamepic/tree.png"));  //暂时画上草，最后添上家 防止背景空白
                    homepos->x=i*40;homepos->y=j*40;
                    break;
                case 4: //画上花花
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/flower.png"));
                    break;
                case 5://画水
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/water.png"));
                    break;
                case 6:
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/tree.png"));
                    break;


                }
            //画上家
                p.drawPixmap(homepos->x, homepos->y, 120, 120, QPixmap(":/Gamepic/home2.png")); //最后画出家
             }

    }
    if(level==3)
    {
        for (int j = 0; j < 16; j++)
            for (int i = 0; i<26;i++)
            {
                switch (Map[j][i])
                {
                case 0:     //画上树
                    p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/snow.png"));
                    break;
                case 1:     //画上路
                    p.drawPixmap(i * 40, j * 40, 40, 40,QPixmap(":/Gamepic/road.png"));
                    break;
                case 2:     //画上塔坑,同时初始化塔坑数组的一个成员并插入数组
                    p.drawPixmap(i * 40, j * 40, 80, 80,QPixmap(":/Gamepic/pit.png"));
                    TowerpitVec.push_back(new TowerPit(i * 40, j * 40));
                    break;

                case 3://记录家的坐标，留到最后画
                    p.drawPixmap(i * 40, j * 40, 80, 80,
                        QPixmap(":/Gamepic/snow.png"));  //暂时画上草，最后添上家 防止背景空白
                    homepos->x=i*40;homepos->y=j*40;
                    break;
                case 4: //画上花花
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/flower.png"));
                    break;
                case 7://画水
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/water.png"));
                    break;
                case 6:
                    p.drawPixmap(i*40,j*40,40,40,QPixmap(":/Gamepic/tree.png"));
                    break;


                }
            //画上家
                p.drawPixmap(homepos->x, homepos->y, 120, 120, QPixmap(":/Gamepic/home3.png")); //最后画出家
             }

    }






}
//画出选塔框
void Gameworld::paintSelectionBox(QPainter &p){
    //如果状态为未显示返回
    if (!Selectbox->Getshow())
        return;


    //画出选择框
    p.drawPixmap(Selectbox->Getx(),Selectbox->Gety(),Selectbox->GetWidth(),Selectbox->GetHeight(),QPixmap(Selectbox->GetPicPath()));

    //画出选择按钮 新定义选择按钮指针 Aselectbut 指向选择框选择按钮数组
    SelectButton* Aselectbut = Selectbox->GetSelectBut();
    for(int i=0;i<=2;i++)
    {
        p.drawPixmap(Aselectbut[i].x,Aselectbut[i].y,Aselectbut[i].SubWidth,Aselectbut[i].SubHeight,QPixmap(Aselectbut[i].SubPicPath));

    }
}
//画出防御塔
void Gameworld::paintTower(QPainter &p){

    for (auto aTower:TowerVec)  //遍历塔数组
    {
         //qDebug()<<"drawTower";
        p.drawPixmap(aTower->GetX(), aTower->GetY(), aTower->GetWidth(), aTower->GetHeight(), QPixmap(aTower->GetTowerPicPath()));
//        if(aTower->GetAimMonster()!=NULL)
//        p.drawEllipse(QPoint(aTower->GetPitX()+40,aTower->GetPitY()+40),aTower->GetShootrange(),aTower->GetShootrange());

        //p.resetTransform();   //重置调整
    }
}
//画出攻击圈
void Gameworld:: paintcircle(QPainter&p){
    for (auto aTower:TowerVec)  //遍历塔数组
    {
      // 如果有目标就画
        if(aTower->GetAimMonster()!=NULL)
        {
            if(aTower->GetId()==1)
                {
                     p.setPen(QPen(Qt::red));  //使用红色画出范围
                     p.drawEllipse(QPoint(aTower->GetPitX()+40,aTower->GetPitY()+40),aTower->GetShootrange(),aTower->GetShootrange());
                 }
            if(aTower->GetId()==2)
                {
                     p.setPen(QPen(Qt::green));  //使用绿色画出范围
                     p.drawEllipse(QPoint(aTower->GetPitX()+40,aTower->GetPitY()+40),aTower->GetShootrange(),aTower->GetShootrange());
                 }
            if(aTower->GetId()==3)
                {
                     p.setPen(QPen(Qt::red));  //使用红色画出范围
                     p.drawEllipse(QPoint(aTower->GetPitX()+40,aTower->GetPitY()+40),aTower->GetShootrange(),aTower->GetShootrange());
                 }
        }
    }
}
//画出升级按钮
void Gameworld::paintupgrade(QPainter &p)
{
    if(UpgradeShow)
    {
        p.drawPixmap(upgradex+10,upgradey-30,65,30,QPixmap(":/Gamepic/update.png"));
    }
    if(warnshow)
    {
        p.drawPixmap(upgradex+30,upgradey-60,20,20,QPixmap(":/Gamepic/warn.png"));
    }
}

void Gameworld::paintlifebar(QPainter &p)
{
    for(auto aMonster:MonsterVec)//遍历怪物数组并画出生命条
    {
        if(aMonster->getlife()>0)
        {
       int barlength=65;//规定血条显示长度为65 要计算出不同生命值怪物的血条比例
       int barheight=7;
      //double unit=aMonster->getfulllife()/65;
      double leftlife1=aMonster->getlife()*65/aMonster->getfulllife();//剩余生命的长度
      int leftlife=leftlife1;
      qDebug()<<leftlife1;
       p.drawPixmap(aMonster->getx()-3+leftlife,aMonster->gety()-9,barlength-leftlife,barheight,QPixmap(":/Gamepic/whitebar.png"));
       p.drawPixmap(aMonster->getx()-3,aMonster->gety()-9,leftlife,barheight,QPixmap(":/Gamepic/greenbar.png"));
      }
    }
}
//画出子弹

//画出怪物
void Gameworld::paintMonster(QPainter&p){
    for(auto aMonster:MonsterVec)//遍历怪物数组并画出
        p.drawPixmap(aMonster->getx(), aMonster->gety(),aMonster->getwidth(),aMonster->getheight(),QPixmap(aMonster->getMonsterPic()));
}
//画图事件
void Gameworld::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    paintmap(painter);
    paintSelectionBox(painter);
    paintTower(painter);
    paintMonster(painter);

    paintcircle(painter);
    paintupgrade(painter);
    paintlifebar(painter);
}

//判断金钱够不够设塔 、升级等等
bool Gameworld::Ifmoneyenough(int mon){
    if(this->money>=mon){
        money=money-mon;

        moneylable->setText(QString("金钱：%1").arg(money));//刷新标签
        return true;
    }
    return false;
}
//鼠标点击事件处理函数
void Gameworld::mousePressEvent(QMouseEvent *ev){
     //限制按左键才有用,别的键没用

    if (ev->button()!=Qt::LeftButton)
        return;



//    if(ClickRegion(0, 500, 0, 500)){

//        qDebug()<<"lllll";
//        update();  //更新界面
//        return;
//    }
    //1.塔升级按钮点击处理 前提是有塔
      if(UpgradeShow)
       {
          if(ClickRegion(upgradex+10,65,upgradey-30,30))
          {
              for (auto aTower: TowerVec)
                  if(aTower->GetPitX()==upgradex&&aTower->GetPitY()==upgradey)
                  {
                      if(Ifmoneyenough(100)&&aTower->GetShootrange()<=230&&aTower->GetAttack()<=40) //升级花费100元
                      {     //升级后塔的攻击半径加7，攻击力加5
                            aTower->SetAttack(5);
                            aTower->SetRange(7);
                            aTower->SetWidthHeight();
                            break;
                      }
                      else{
                          UpgradeShow=false;
                          warnshow=true;
                          return;
                      }
                  }
              UpgradeShow=false;
              update();
              return;
          }
      }


      //2.点击塔坑显示选择框事件处理
    //遍历塔坑Vector，
   for (auto Apit : TowerpitVec)
       //如果点击了这个塔坑的范围，且还没有放置塔，出现选择框
    if(ClickRegion(Apit->GetX(), Apit->GetWidth(), Apit->GetY(), Apit->GetHeight()))
    {

         UpgradeShow=false;//升级按钮不显示
        for (auto aTower: TowerVec)      //遍历塔数组，判断塔坐标和点击坑坐标是否重合，重合说明已经有塔，然后将这个塔的
                                           //升级按钮显示
        {
            if(aTower->GetPitX()==Apit->GetX()&&aTower->GetPitY()==Apit->GetY())
            {

                  upgradex=aTower->GetPitX();
                  upgradey=aTower->GetPitY();
                  warnshowx=upgradex+30;
                  warnshowy=upgradey-30;
                  UpgradeShow=true;//有塔受到点击，升级按钮显示
                  return;
            }
        }


         this->Selectbox->ChooseTower(Apit->GetX(),Apit->GetY()); //显示选择框
        //qDebug()<<"lllll";
          update();
          return;


    }



   //3.出现选择框后选择点击事件处理

   SelectButton* ASelectbut = Selectbox->GetSelectBut();
   for (int i = 0; i < 3; i++)
       //判断如果点击了对应的选择按钮区域
       if (ClickRegion(ASelectbut[i].x, ASelectbut[i].SubWidth, ASelectbut[i].y,ASelectbut[i].SubHeight) && Selectbox->Getshow())
       {
          Selectbox->Setshow(false);      //选择炮塔后选择框消失
           // qDebug()<<"lllll";
           //根据点击的不同的按钮，将不同级别塔插入到防御塔数组TowerVec
           switch (i)
           {
           case 0: //一级炮塔
               if (Ifmoneyenough(300)==false) return;    //扣除金钱
              TowerVec.push_back(new Towerone(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,80,80));
               break;
           case 1: //二级炮塔
               if (Ifmoneyenough(400)==false) return;    //扣除金钱
              TowerVec.push_back(new Towertwo(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,80,80));
               break;
           case 2: //三级炮塔
               if (Ifmoneyenough(500)==false) return;//扣除金钱
              TowerVec.push_back(new Towerthree(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,80,80));
               break;

           default:
               break;
           }

           update();
           return;
       }


   UpgradeShow=false;
   warnshow=false;
   Selectbox->Setshow(false);      //取消显示选择框
   update();



}
//计算两点距离函数
double Gameworld::Distance(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void Gameworld::closeEvent(QCloseEvent *event)
{
   timer2->stop();
   timer3->stop();

    player->stop();
    player2->stop();
    player3->stop();
    player4->stop();
    this->close();
}


Gameworld::~Gameworld(){
  player->stop();
  delete timer2;
  delete timer3;
  delete player;
  delete player2;
  delete player3;
  delete player4;

  delete   this->Selectbox;

  for (auto aTowerPit= TowerpitVec.begin();aTowerPit!= TowerpitVec.end();aTowerPit++)
  {
      delete *aTowerPit;
      *aTowerPit = NULL;
  }

  //释放防御塔父类指针数组DefeTowerVec
  for (auto aTower= TowerVec.begin();aTower!=TowerVec.end();aTower++)
  {
      delete *aTower;
      *aTower = NULL;
  }

  //释放怪物数组MonsterVec
  for (auto aMonster = MonsterVec.begin();aMonster!= MonsterVec.end(); aMonster++)
  {
      delete *aMonster;
      *aMonster=NULL;
  }


}
