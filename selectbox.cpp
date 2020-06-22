#include "selectbox.h"


//构造函数实现
SelectBox::SelectBox(QString Path, int width1, int height1):width(width1),height(height1),SelecBoxPicPath(Path) {}

//控制显示选择框
void SelectBox::Setshow(bool setshow){
    this->show=setshow;
}

//选择防御塔函数，传入的参数是每一个塔坑的左上角坐标
void SelectBox::ChooseTower(int x1, int y1){


    //根据塔坑坐标 确定选择框左上角坐标 这个需要计算实验才能完美贴合
     this->x=x1-85;this->y=y1-90;

    //设置子按钮显示的位置
    //上方子按钮位置及对应的大炮图片
    selectbut[0].x=this->x+90,selectbut[0].y =this->y+5;
    selectbut[0].SubPicPath=QString(":/Gamepic/tanzhilang1.png");
    //重复以上过程
    selectbut[1].x=this->x +10,selectbut[1].y =this->y+90;
    selectbut[1].SubPicPath=QString(":/Gamepic/lianzhu1.png");

    selectbut[2].x=this->x+170,selectbut[2].y =this->y+90;
    selectbut[2].SubPicPath=QString(":/Gamepic/yanzhu1.png");

    this->show=true;
}
