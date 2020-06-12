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
    //绘图刷新
//    QTimer* timer1 = new QTimer(this);
//    timer1->start(8000);
//    connect(timer1,&QTimer::timeout,[=](){
//        update();
//    });

    //每时每刻产生构造怪物产生路径并传入怪物,时间间隔控制产生怪物间隔
    QTimer* timer2 = new QTimer(this);
    timer2->start(3000);

    connect(timer2,&QTimer::timeout,[=]()
    {    //根据关卡地图传入不同路径点
        switch (level) {
        case 1:
        {
            //设置路径点  第一关没有拐弯的地方，第一个拐点就是出发点，最后一个拐点即 家的坐标。
           Point* path1[] = {new Point(0,280), new Point(960, 280)};
           Point* path2[] = {new Point(0,280), new Point(960, 280)};
            //怪物的起始点数组MonsterStart，都规定好的
            Point start1(0,280);
            Point MonsterStart[]={start1};
           //CoorStr staco[] = {CoorStr(8, 0), CoorStr(20, 0), CoorStr(8, -1), CoorStr(20, -1)};

            //每条路径的结点个数,第一关两条路径都是一样的，相当于都是2个拐点
           int PathPoint[2] = {2,2};
           ProduceMonster(path1,path2,MonsterStart,PathPoint);
           // IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案

            break;
        }

      }
    });


    //每时每刻画怪物+判断怪物进没进入炮塔的攻击区域 进入发射子弹+
    QTimer* timer3 = new QTimer(this);
    timer3->start(100);

    connect(timer3,&QTimer::timeout,[=]()
    {

        //通过调用怪物移动函数刷新怪物位置
        for (auto aMonster=MonsterVec.begin();aMonster!= MonsterVec.end(); aMonster++)
            if((*aMonster)->MonsterMove()) //怪物闯入家
            {
                delete *aMonster;
                MonsterVec.erase(aMonster);         //怪物走到终点则删除这个怪物

                this->mylife--;                         //我们的生命数量-1
               // lifelable->setText(QString("生命：%1").arg(life));

                if (mylife<= 0) this->close();   //生命值为0时关闭该窗口

                break;
            }





        for (auto aTower:TowerVec)      //遍历防御塔
        {
            //先判断若当前防御塔没有目标，则创建目标
            if (aTower->GetAimMonster()==NULL)
            {
                for(int i =MonsterVec.size()- 1;i>=0; i--)
                    //这里以防御塔中心点和怪物中心点判断
                    if (Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,MonsterVec.at(i)->getx()+MonsterVec.at(i)->getwidth()/2,MonsterVec.at(i)->gety()+MonsterVec.at(i)->getheight()/2)<=aTower->GetShootrange())
                    {
                        aTower->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        qDebug()<<"Aim monster get!";
                        break;  //找到后跳出循环
                    }
            }

            //在判断若当前防御塔拥有目标
           if(aTower->GetAimMonster()!=NULL)
                {
                       //目标在攻击范围内
                         if (Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,aTower->GetAimMonster()->getx()+aTower->GetAimMonster()->getwidth()/2,aTower->GetAimMonster()->gety()+aTower->GetAimMonster()->getheight()/2)<=aTower->GetShootrange())
                                {
                               //拥有目标时一直创建子弹
                                   qDebug()<<"Bullet is doing";
                                   aTower->InsertBullet();
                                 }


                        // if (Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,MonsterVec.at(i)->getx()+MonsterVec.at(i)->getwidth()/2,MonsterVec.at(i)->gety()+MonsterVec.at(i)->getheight()/2)>aTower->GetShootrange())
                          if(Distance(aTower->GetPitX()+40,aTower->GetPitY()+40,aTower->GetAimMonster()->getx()+aTower->GetAimMonster()->getwidth()/2,aTower->GetAimMonster()->gety()+aTower->GetAimMonster()->getheight()/2)>aTower->GetShootrange())
                                    aTower->SetAimsMonster(NULL);     //超过距离将目标怪物设为空

                        // }
                  }
           qDebug()<<"BulletMove";
          aTower->BulletMove();
        }

       update();

    }
    );

}


//生成怪物事件
void Gameworld::ProduceMonster(Point** Path1,Point** Path2,Point* StartPoint, int* NumOfPoint){


    if(this->TimeMonsterNum>=0&&this->TimeMonsterNum<=10)
    {
        //开始游戏怪物数目1~10时，只有一条路产生编号1的小黑黑怪
        InsertMonster(Path1,StartPoint[0],NumOfPoint[0],1);

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


        //p.resetTransform();   //重置调整
    }
}
//画出子弹
void Gameworld::paintbullet(QPainter &p){
    for (auto aTower:TowerVec)  //遍历塔数组
    {
        qDebug()<<" zhunbei   draw   bullet";
        //for(int i=aTower->BulletVec.size()-1;i>=0; i--)
        for(auto abullet : aTower->BulletVec)
        {
         qDebug()<<"!!! jinru   draw bullet";
         p.drawPixmap(abullet->Getx(),abullet->Gety(),aTower->GetBulletWidth(),aTower->GetBulletHeight(),QPixmap(aTower->GetBulletPic()));
           //p.drawPixmap(aTower->BulletVec.at(i)->Getx(),aTower->BulletVec.at(i)->Gety(),aTower->GetBulletWidth(),aTower->GetBulletHeight(),QPixmap(aTower->GetBulletPic()));
         }

    }
}
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
    paintbullet(painter);
}

//判断金钱够不够
bool Gameworld::Ifmoneyenough(int mon){
    if(this->money>=mon){
        money=money-mon;
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

    //1.点击塔坑显示选择框事件处理
    //遍历塔坑Vector，
   for (auto Apit : TowerpitVec)
       //如果点击了这个塔坑的范围，且还没有放置塔，出现选择框
    if(ClickRegion(Apit->GetX(), Apit->GetWidth(), Apit->GetY(), Apit->GetHeight()))
    {

        for (auto aTower: TowerVec)      //遍历塔数组，判断塔坐标和点击坑坐标是否重合，重合说明已经有塔，则返回
            if(aTower->GetPitX()==Apit->GetX()&&aTower->GetPitY()==Apit->GetY())
            {
//                      //显示防御塔攻击范围
                return;
            }
        this->Selectbox->ChooseTower(Apit->GetX(),Apit->GetY()); //显示选择框
        qDebug()<<"lllll";
        update();  //更新界面
        return;
    }



   //2.出现选择框后选择点击事件处理

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
               if (Ifmoneyenough(100)==false) return;    //扣除金钱
              TowerVec.push_back(new Towerone(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,86,86));
               break;
           case 1: //二级炮塔
               if (Ifmoneyenough(200)==false) return;    //扣除金钱
              TowerVec.push_back(new Towertwo(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,86,86));
               break;
           case 2: //三级炮塔
               if (Ifmoneyenough(300)==false) return;//扣除金钱
              TowerVec.push_back(new Towerthree(Selectbox->Getx()+87, Selectbox->Gety()+90,
                                     Selectbox->Getx()+85, Selectbox->Gety()+90,86,86));
               break;

           default:
               break;
           }

           update();
           return;
       }

   //3.


   Selectbox->Setshow(false);      //取消显示选择框
   update();



}
//计算两点距离函数
double Gameworld::Distance(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
