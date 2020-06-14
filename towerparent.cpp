#include "towerparent.h"

//TowerParent::TowerParent()
//{

//}

//设置目标怪物函数
void TowerParent::SetAimsMonster(Monster* mon){
    this->AimMonster=mon;
}

//插入子弹同时确定子弹路径
//void TowerParent::InsertBullet(){

//    //子弹发射间隙控制器
//    breaks++;

//    if( breaks<=6||AimMonster==NULL)      //控制发射子弹间隙为6个刷新时，或者无目标怪物
//        return;

//    //向子弹数组中插入子弹

//    Bullet *aBullet=new Bullet(this->PitX,this->PitY);
//     aBullet->x= PitX+40;
//     aBullet->y= PitY+40;


//    //计算子弹的路径 用公式y=kx+b 当斜率存在时
//      if(abs(AimMonster->getx()-aBullet->Getx())>60)
//    {
//     aBullet->k=(AimMonster->gety()-aBullet->Gety())/(AimMonster->getx()-aBullet->Getx());
//     aBullet->b=AimMonster->gety()-AimMonster->gety()*aBullet->k;
//     }
//    else{
//          delete aBullet;
//          breaks= 0;    //计数器重置为0
//          return ;
//    }

//      // qDebug()<<"insert bullet";
//      this->BulletVec.push_back(aBullet);

//      if(AimMonster->getx()<=this->PitX+40)  //怪兽在在塔坑中心左边为真
//          aBullet->direction=true;
//       breaks=0;
//     // return;

//}

//void TowerParent::BulletMove(){
//    //子弹移动

//    for(auto aBullet: BulletVec)
//    {
//        int speed=20;              //子弹移动速度

//        if(aBullet->direction==true)    //怪兽在在子弹左边
//            aBullet->x-=speed;        //根据移动方向标记判断每颗子弹的移动方向
//        else
//             aBullet->x+=speed;       //怪兽在在子弹右边
//     //根据算出的y=kx+b   计算子弹移动到的点
//        aBullet->y=aBullet->k*aBullet->x+aBullet->b;    //子弹纵坐标改变
//    }
//     //控制子弹在游戏界面内

//    for(auto aBullet=BulletVec.begin();aBullet!=BulletVec.end(); aBullet++)
//    {if((*aBullet)->Getx()>1040||(*aBullet)->Getx()< 0||(*aBullet)->Gety()>640||(*aBullet)->Gety()< 0)
//        {
//            BulletVec.erase(aBullet);
//            break;
//        }

//    }

//}

bool TowerParent::ifTowerAttack()
{

    //攻击间隙控制器
    breaks++;
    //控制攻击间隙为6个刷新（时），或者无目标怪物返回
    if( breaks<=6||AimMonster==NULL)
        return false;


     breaks=0;
     return true;
}


//获取攻击力
int TowerParent::GetAttack() const{
    return this->attack;
}
 //获取子弹的宽度
int TowerParent::GetBulletWidth() const{
    return this->bulletwidth;
}

int TowerParent::GetBulletHeight() const{
     return this->bulletheight;
}
//获取当前炮塔的目标怪物
Monster* TowerParent::GetAimMonster() const{
      return this->AimMonster;
}
//获取攻击范围半径
int  TowerParent::GetShootrange()const{
    return this->ShootRange;
}
//返回防御塔子弹图片路径
QString TowerParent::GetBulletPic() const{
    return this->BulletPic;
}
//获取子弹数组
QVector<Bullet*> TowerParent::GetBulletVec()const{
      return this->BulletVec;
}
//获取塔的类型
int TowerParent::GetId(){
    return this->id;
}
