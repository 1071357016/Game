#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMainWindow>
#include <QMouseEvent>
#include<QPainter>
#include"mypushbutton.h"
#include<QString>
#include"master.h"
#include<QTimer>
#include"Point.h"
#include"towerparent.h"
#include"towerpit.h"



class Gameworld : public QMainWindow
{
    Q_OBJECT
public:
    //重载构造函数，i为关卡数，根据关卡数设置地图
    Gameworld(int i);
private:


    int level;
    QString bg;
    QTimer *time;
    Point* homepos=new Point(0,0);//城堡的坐标 根据地图变化





    //画图事件 里边画地图 画。。。。。
    void paintEvent(QPaintEvent *);
    //画地图事件
    void paintmap(QPainter&);
    //鼠标点击事件 ，点击防御塔坑，出现选择框，选择放置塔 ；
    void mouseClickEvent(QMouseEvent *);


signals:

protected slots:

};

#endif // GAMEWORLD_H
