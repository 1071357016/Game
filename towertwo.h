#ifndef TOWERTWO_H
#define TOWERTWO_H


//防御塔派生类 2级塔
#include"towerparent.h"
class Towertwo:public TowerParent
{
public:
     //构造函数参数为塔图片的坐标，塔图片的宽高，塔坑的原坐标
    Towertwo(int x1,int y1,int pitx, int pity,int width1,int height1);
};


#endif // TOWERTWO_H
