#include "towerparent.h"

//TowerParent::TowerParent()
//{

//}

//设置目标怪物函数
void TowerParent::SetAimsMonster(Monster* mon){
    this->AimMonster=mon;
}



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

//获取当前炮塔的目标怪物
Monster* TowerParent::GetAimMonster() const{
      return this->AimMonster;
}
//获取攻击范围半径
int  TowerParent::GetShootrange()const{
    return this->ShootRange;
}

//获取塔的类型
int TowerParent::GetId(){
    return this->id;
}
void TowerParent::SetAttack(int newattack){
    this->attack=attack+newattack;
}

void TowerParent::SetWidthHeight()
{
    this->width+=3;
    this->height+=3;
    this->x-=2;
    this->y-=2;
}


void TowerParent::SetRange(int newrange){
    this->ShootRange=ShootRange+newrange;
}
