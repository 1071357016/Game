#include "mypushbutton.h"

//自定义button类完成一系列操作


MyPushButton::MyPushButton(QString normalimg,QString pressimg){
    //传入图片路径
    this->normalimgPath=normalimg;
    this->pressimgPath=pressimg;
    QPixmap pix;
    pix.load(normalimg);
//    bool ret=pix.load(normalimg);
//    if(!ret){
//        cout<<"图片加载失败";
//        return;
//    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式,这里有参考
    this->setStyleSheet("QPushButton(border:Opx:)");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//void MyPushButton::mousePressEvent(QMouseEvent *event){


//    if(this->pressimgPath !=""){

//        QPixmap pix;
//        pix.load(pressimgPath);
//    //复制上述代码
//        //设置图片固定大小
//        this->setFixedSize(pix.width(),pix.height());
//        //设置不规则图片样式,这里有参考
//        this->setStyleSheet("QPushButton(border:Opx:)");
//        //设置图标
//        this->setIcon(pix);
//        //设置图标大小
//        this->setIconSize(QSize(pix.width(),pix.height()));
//    }
//    //给父类处理
//    return QPushButton::mousePressEvent(event);
//}
