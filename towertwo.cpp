#include "towertwo.h"

Towertwo::Towertwo(int x1,int y1,int pitx, int pity,int width1,int height1)
{
    this->x=x1;
    this->y=y1;
   this->width=width1;
   this->height=height1;
   this->PitX=pitx;
   this->PitY=pity;
    this->TowerPic= QString(":/Gamepic/turret2.png");

    ShootRange=200;//射程
    //子弹相关
    BulletPic=QString(":/Gamepic/bullet1.png");
    bulletwidth=20;
    bulletheight=20;
    attack=30;
}
