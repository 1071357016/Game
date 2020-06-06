#ifndef TOWERPARENT_H
#define TOWERPARENT_H
//防御塔父类实现

#include<QString>
#include <QObject>


class TowerParent
{
protected:

    int x, y;                //记录塔的坐标
    int width, height;        // 记录塔的宽高
    int RotatAngle = 0;       //防御塔旋转角度
    int PitX, PitY;           //防御塔塔坑左上角坐标
    int ShootRange;           //防御塔的射程


    QString TowerBasePic;     //防御塔底座图片路径
    QString TowerPic;        //防御塔图片路径

    //Monster* aimsmon = NULL;//记录防御塔的目标怪物


public:
    TowerParent();
    int GetX() const{return this->x;}       //获取横坐标
    int GetY() const{return this->y;}        //获取纵坐标
    int GetWidth() const{return this->width;}    //获取宽
    int GetHeight() const{return this->height;}  //获取高
    int GetRotatAngle() const{return this->RotatAngle;}      //旋转角度
    int GetPitX() const{return this->PitX;} //    获取防御塔坑  左上角原横坐标
    int GetPitY() const{return this->PitY;}//     获取防御塔坑 左上角原纵坐标


    QString GetBaseImgPath() const; //获取底座图片路径
    QString GetDefImgPath() const{return this->TowerPic;}  //获取防御塔图片路径
};

#endif // TOWERPARENT_H
