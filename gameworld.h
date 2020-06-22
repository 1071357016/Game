#ifndef GAMEWORLD_H
#define GAMEWORLD_H
//游戏世界主页面类
#include <QMainWindow>
#include <QMouseEvent>
#include<QLabel>
#include<QPalette>
#include<QPainter>
#include<QDebug>
#include<QMediaPlayer>
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
#include <stdlib.h>



class Gameworld : public QWidget
{
    //Q_OBJECT
public:
    //重载构造函数，i为关卡数，根据关卡数设置地图
    Gameworld(int i);
    ~Gameworld();
private:
    //游戏胜利和失败的标签
     QLabel *winlable = new QLabel(this);
     QLabel *loselable = new QLabel(this);
     int flag=0;//防止出现胜利失败同时展现的局面
    int level;
    int money=800;//金钱 初始值为700
    QLabel *moneylable = new QLabel(this);   //金钱标签控件,声明在此因为多个函数用到

    int mylife=7;//我们的生命值
    QLabel *lifelable = new QLabel(this);   //显示生命标签控件

    int TimeMonsterNum=0;//时间计数，每插入怪物加一，也就是实现游戏时间越长难度越大

    //升级按钮显示依据
    bool UpgradeShow=false;
    int upgradex,upgradey;//记录要升级的塔的坐标
    bool warnshow=false;
    int warnshowx,warnshowy;
     //音乐播放器
    QMediaPlayer * player = new QMediaPlayer;//背景音
    QMediaPlayer * player2 = new QMediaPlayer;//受到伤害音效
    QMediaPlayer * player3= new QMediaPlayer;//失败音效
    QMediaPlayer * player4 = new QMediaPlayer;//胜利音效



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
    //画出攻击圈
    void paintcircle(QPainter&);
    //画出升级按钮（点击塔时）
    void paintupgrade(QPainter&);
    //画出怪物生命条
    void paintlifebar(QPainter&);
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
    //关闭窗口事件
    void closeEvent(QCloseEvent *event);
signals:

protected slots:

};

#endif // GAMEWORLD_H
