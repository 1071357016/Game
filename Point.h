#ifndef POINT_H
#define POINT_H
//自定义point类
class Point{
public:
    int x=0;
    int y=0;
    Point();
    Point(int x1,int y1){x=x1;y=y1;}
    Point(Point & p){x=p.x;y=p.y;}
};

#endif // POINT_H
