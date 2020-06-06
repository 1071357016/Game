#ifndef TOWERPIT_H
#define TOWERPIT_H
//设计此防御塔坑类，为了方便鼠标点击时的范围判断

class TowerPit
{
private:
    const int x, y;           //塔坑位置坐标
    const int width, height;  //塔坑宽高

public:
    //构造函数    传入的是 防御塔坑坐标、宽高（默认80两个格子)
     TowerPit(int x1, int y1, int width1 = 80, int height1 = 80);
    int GetX() const;     //获取横坐标
    int GetY() const;     //获取横坐标
    int GetWidth() const; //获取宽
    int GetHeight() const;//获取高

};

#endif // TOWERPIT_H
