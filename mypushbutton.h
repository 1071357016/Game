#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //自行定义构造函数,参数一 正常显示图片路径 参数二 按下按钮后显示的图片路径
    MyPushButton(QString normalimg, QString pressimg="");
    //成员属性 保存切换前，切换后图片路径
    QString normalimgPath;
    QString pressimgPath;

};

#endif // MYPUSHBUTTON_H
