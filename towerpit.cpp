#include "towerpit.h"


//构造函数 传入坐标和宽高
TowerPit::TowerPit(int x1, int y1, int width1, int height1):x(x1),y(y1),width(width1),height(height1){}

//以下为获得坐标及宽高的函数
int TowerPit:: GetX() const{
    return this->x;
}
int TowerPit::GetY() const{
    return this->y;
}
int TowerPit::GetWidth() const{
    return this->width;
    }
int TowerPit::GetHeight() const{

    return this->height;
    }
