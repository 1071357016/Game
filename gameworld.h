#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMainWindow>
#include<QPainter>
#include"mypushbutton.h"
#include<QString>
#include"master.h"
#include<QTimer>
class Gameworld : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gameworld(QWidget *parent = nullptr);
    //重载构造函数，第一个参数是背景图片路径，第二个是关卡
    Gameworld(QString bgpic,int i);
    void paintEvent(QPaintEvent *);

private:
    int level;
    QString bg;
    QTimer *time;
signals:

protected slots:
    void paintmaster();//绘制怪物槽函数
};

#endif // GAMEWORLD_H
