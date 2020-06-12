#ifndef TOWERTHREE_H
#define TOWERTHREE_H

//防御塔派生类  3级塔
#include"towerparent.h"
class Towerthree:public TowerParent
{
public:
   //构造函数参数为塔图片的坐标，塔图片的宽高，塔坑的原坐标
    Towerthree(int x1,int y1,int pitx, int pity,int width1,int height1);
};

#endif // TOWERTHREE_H
