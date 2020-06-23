#ifndef TOWERPARENT_H
#define TOWERPARENT_H
//防御塔父类实现

#include<QString>
#include <QObject>
#include<QVector>
#include<QDebug>
#include"monster.h"
#include"Point.h"
class TowerParent
{
protected:

    int x, y;                //记录塔的坐标
    int width, height;        // 记录塔的宽高
    int PitX, PitY;           //防御塔塔坑左上角坐标
    int ShootRange;           //防御塔的射程
    int id;

    //QString TowerBasePic;     //防御塔底座图片路径
    QString TowerPic;        //防御塔图片路径

     Monster* AimMonster= NULL;//记录防御塔的目标怪物



    int breaks=0;          //用于控制塔攻击的间歇
    int attack;             //防御炮塔攻击力



public:


    //TowerParent();
    int GetX() const{return this->x;}       //获取横坐标
    int GetY() const{return this->y;}        //获取纵坐标
    int GetWidth() const{return this->width;}    //获取宽
    int GetHeight() const{return this->height;}  //获取高
    int GetPitX() const{return this->PitX;} //    获取炮塔坑  左上角原横坐标
    int GetPitY() const{return this->PitY;}//     获取炮塔坑 左上角原纵坐标

    QString GetTowerPicPath() const{return this->TowerPic;}  //获取炮塔图片路径

    //6.11
    int GetAttack() const;          //获取炮塔攻击力
    int  GetShootrange()const;  //获取攻击范围半径
    Monster* GetAimMonster() const;//获取当前炮塔的目标怪物



    void SetAimsMonster(Monster*);  //设置当前防御塔的目标怪物



    //6.14改变方向 攻击函数
    //判断是否攻击
    bool ifTowerAttack();
    int GetId();

    //升级重设塔的参数
    void SetAttack(int newattack);            //设置防御塔攻击力
    void SetWidthHeight();  //设置防御塔宽高
    void SetRange(int newrange);                //设置防御塔的攻击范围


};

#endif // TOWERPARENT_H
