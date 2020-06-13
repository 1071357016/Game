#include "monster.h"
//之前的怪物类名字打错了看着难受，重新开始造

Monster::Monster(int x1,int y1,Point** path1,int NumOfPathPoint1,int id):x(x1),y(y1),type(id),NumOfPathPoint(NumOfPathPoint1)
{
    //首先将传入的path1 push_back到怪物路径数组
    for(int i=0;i<NumOfPathPoint;i++)
    {
        this->path.push_back(path1[i]);
    }

    //根据怪物型号确定不同属性
    switch (type)
    {case 1:
        //一级怪 生命值50 大小40*40 打死获得金钱50块 速度为5慢慢慢
        this->life=50;
        this->width=50;
        this->height=60;
        this->value=50;
        this->speed=5;
        MonsterPic=":/Gamepic/master1.png";
        break;
    case 2:
            //二级怪 生命值80 大小50*50 打死获得金钱100块
            this->life=80;
            this->width=50;
            this->height=50;
            this->value=100;
             this->speed=7;
            MonsterPic=":/Gamepic/master2.png";
            break;
    case 3:
            //三级怪爆爆雪人 生命值180 大小60*60 打死获得金钱180块
            this->life=180;
            this->width=60;
            this->height=60;
            this->value=180;
            this->speed=10;
            MonsterPic=":/Gamepic/master3.png";
            break;
    case 4:
            //四级怪超级紫色暴王龙 生命值300 大小80*80 打死获得金钱300块
            this->life=300;
            this->width=80;
            this->height=80;
            this->value=300;
            this->speed=10;
            MonsterPic=":/Gamepic/master4.png";
            break;
    }

}



//怪物坐标按路径移动
bool Monster::MonsterMove(){
    //路径点空了就是走到了
    if(path.empty())
        return true;

    //如果第一个路径点的y大于怪物原本的路径点y，则怪物向上走
    if (path.at(0)->y<y) //上
    {
        y=y-speed;
        return false;
    }
    if (path.at(0)->x>x) //右
    {
        x=x+speed;
        return false;
    }
    //同理
    if (path.at(0)->y>y) //下
    {
        y=y+speed;
        return false;
    }
    //不上不下再看左右
    if (path.at(0)->x<x) //左
    {
        x=x-speed;
        return false;
    }



     //重合则删除此路径点
    if (path.at(0)->y==this->y && path.at(0)->x==this->x)
    {
        path.erase(path.begin());

    }
    return false;
}
//受伤害重置生命值
void Monster::SetLife(int hurt){
    this->life=this->life-hurt;
}




