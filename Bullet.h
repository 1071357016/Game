#ifndef BULLET_H
#define BULLET_H


//实现对炮塔发射子弹的封装的类
#include"Point.h"

class Bullet{
public:
    int x;int y;
    Bullet(int x1,int y1):x(x1),y(y1){};

    Bullet(Bullet &bullet)
    {
            k=bullet.k;
            b=bullet.b;
            x=bullet.Getx();
            y=bullet.Gety();
            direction=bullet.direction;
    }
    double k=0,b=0;           //用于计算出子弹路径函数y=kx+b， 为子弹和目标怪物之间的直线
    bool direction=false;   //移动方向标识根据其判断向左向右
    //获取子弹坐标
    //Point BulletPos;       //子弹坐标

    int Getx()const
    {
        return x;
    }

    int Gety() const
    {
        return y;
    }
};

#endif // BULLET_H
