#ifndef GAMEWORLD_H
#define GAMEWORLD_H
//游戏世界主页面类
#include <QMainWindow>
#include <QMouseEvent>
#include<QPainter>
#include<QDebug>
#include<cmath>
#include"mypushbutton.h"
#include<QString>
#include<QTimer>
#include"Point.h"
#include"towerparent.h"
#include"towerone.h"
#include"towertwo.h"
#include"towerthree.h"
#include"towerpit.h"
#include"Selectbutton.h"
#include"selectbox.h"
#include"monster.h"
#include"Bullet.h"



class Gameworld : public QWidget
{
    //Q_OBJECT
public:
    //重载构造函数，i为关卡数，根据关卡数设置地图
    Gameworld(int i);
private:


    int level;
    int money=700;//金钱 初始值为700
    int mylife=7;//我们的生命值

    int TimeMonsterNum=0;//时间计数，每插入怪物加一，也就是实现游戏时间越长难度越大

    QString bg;
    QTimer *time;
    Point* homepos=new Point(0,0);//城堡的坐标 根据地图变化
    QVector<TowerPit*> TowerpitVec;  //防御塔坑 数组
    QVector<TowerParent*> TowerVec;  //防御塔 数组
    SelectBox* Selectbox= new SelectBox(":/Gamepic/Selectbox.png");//选择框对象
    QVector<Monster *>  MonsterVec;  //怪物  数组




    //画地图事件
    void paintmap(QPainter&);
    //画出选择框事件
    void paintSelectionBox(QPainter&);
    //选择塔后画出塔
    void paintTower(QPainter&);
    //画怪物事件
    void paintMonster(QPainter&);
    //画出子弹
    void paintbullet(QPainter&);
    //整体画图事件 里边画地图 画。。。。。
    void paintEvent(QPaintEvent *);

    //生成怪物事件,参数为 第一条拐点数组 第二条拐点数组  出发点  拐点个数
    void ProduceMonster(Point** Path1,Point** Path2,Point* StartPoint, int* NumOfPoint);
    //插入怪物到怪物数组
    void InsertMonster(Point** path,Point& startpoint,int numofguaidian,int Monsterid);

    //鼠标点击事件 ，点击防御塔坑，出现选择框，选择放置塔 ；
    void mousePressEvent(QMouseEvent *);
    //判断当前金钱值够不够函数
    bool Ifmoneyenough(int mon);
    //计算两点间距离事件
    double Distance(int x1,int y1,int x2,int y2);

signals:

protected slots:

};

#endif // GAMEWORLD_H
