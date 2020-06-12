#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include<QString>
//选择框
class SelectButton
{
public:
    int x;           //子按钮的横坐标
    int y;           //子按钮的纵坐标
    int SubWidth = 80;  //根据 选择框图片 固定子按钮宽和高
    int SubHeight = 80;
    QString SubPicPath; //子按钮的图片路径
};
#endif // SELECTBUTTON_H
