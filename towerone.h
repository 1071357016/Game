#ifndef TOWERONE_H
#define TOWERONE_H
//防御塔派生类  1级塔
#include"towerparent.h"
class Towerone:public TowerParent
{
public:
   //构造函数参数为塔图片的坐标，塔图片的宽高，塔坑的原坐标
    Towerone(int x1,int y1,int pitx, int pity,int width1,int height1);
};

#endif // TOWERONE_H
