#ifndef MASTER_H
#define MASTER_H
#include<QString>
#include<QPainter>
#include<QImage>
#include<gameworld.h>
//个人疏忽把monster打成了master 一失足千古恨 就不改了先
//怪物大类
class Master
{
public:
    Master(int x,int y, QString pa);
    //显示函数
    void show();
    QString  getpath(){return path;}
    int getx(){return posx;}
    int gety(){return posy;}
protected:
    QString path;//图片路径传入
    int posx,posy;//初始位置
   // Gameworld world;
};

#endif // MASTER_H
