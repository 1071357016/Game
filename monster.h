#ifndef MONSTER_H
#define MONSTER_H

#include<QString>
#include <QVector>
#include<Point.h>
#include<math.h>

//之前的怪物类名字打错了看着难受，重新开始造
//设想是实现4种怪物，各种属性不一样
class Monster
{
public:
    //怪物类构造函数：怪物初始位置，怪物编号：1~4,怪物要走的路的数组地址，路线转折点个数
    Monster(int x1,int y1,Point** path1,int NumOfPathPoint1,int id);

    //控制怪物移动函数
    bool MonsterMove();

    //获取怪物信息函数

    int getx(){return x;}
    int gety(){return y;}
    int getwidth(){return width;}
    int getheight(){return height;}
    int getvalue(){return value;}
    int getlife(){return life;}
    int getfulllife(){return fulllife;}
    int getfullspeed(){return fullspeed;}
    QString getMonsterPic(){return  MonsterPic;}

    //被击中后重置生命值
    void SetLife(int hurt);
    void SetSpeed(int newspeed);

private:

    int x,y;//初始位置
    int width,height;//怪物图片宽高
    int type;//怪物类别
    QVector<Point*> path;//存储怪物要走的路线
    int NumOfPathPoint;//路线点个数
    QString MonsterPic;//怪物图片
    int value;//击败你能获得的钱
    int life;//生命值
    int fulllife;//完整生命值v 用来画血条
    int speed;//速度
    int fullspeed;//用于记录原始速度
};

#endif // MONSTER_H
