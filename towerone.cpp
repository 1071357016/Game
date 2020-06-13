#include "towerone.h"
//一级炮塔
Towerone::Towerone(int x1,int y1,int pitx, int pity,int width1,int height1)
{
       this->x=x1;
       this->y=y1;
    this->width=width1;
    this->height=height1;
    this->PitX=pitx;
    this->PitY=pity;
    this->TowerPic= QString(":/Gamepic/turret1.png");
   id=1;

      ShootRange=120;//射程
    //子弹相关
    BulletPic=QString(":/Gamepic/bullet2.png");
    bulletwidth=20;
    bulletheight=20;
    attack=10;

}
