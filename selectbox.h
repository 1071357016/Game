#ifndef SELECTBOX_H
#define SELECTBOX_H
#include<QMediaPlayer>
#include<QString>
#include"Selectbutton.h"  //包含进子按钮类

//选择框类实现，在框中将出现三大炮

class SelectBox
{
private:
    int x = 0, y = 0;         //最左上角坐标，初始化为0
    int width, height;        //选择框宽高
    QString SelecBoxPicPath;  //选择框图片路径
    SelectButton  selectbut[3];     //三个选择子按钮
    bool show=false;           //选择框显示默认为不显示

public:
    //构造函数 传入选择框图片 和 设置好宽高
    SelectBox(QString Path, int width1=250, int height1=250);

    //一系列获取选择框信息的函数

    int Getx()const     //获取横坐标
    {
        return x;
    }
    int Gety()const     //获取横坐标
    {
        return y;
    }
    int GetWidth() const //获取宽
    {
        return width;
    }
    int GetHeight() const //获取高
    {
        return height;
    }
    SelectButton* GetSelectBut()  //获取选择按钮数组
    {
        return this->selectbut;
    }
    QString GetPicPath() const    //返回选择框图片路径
    {
        return SelecBoxPicPath;
    }
    bool Getshow() const          //获取显示状态
    {
        return this->show;
    }


    //设置选择框显示函数
    void Setshow(bool setshow);
   //选择防御塔函数，传入的参数是每一个塔坑的左上角坐标
    void ChooseTower(int x1, int y1);
};

#endif // SELECTBOX_H
