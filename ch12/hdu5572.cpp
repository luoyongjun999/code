//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;  //本题如果设定eps=1e-10，会Wrong Answer
int sgn(double x){         //判断x是否等于0
    if(fabs(x) < eps)  return 0;
    else return x<0?-1:1;
}
struct Point{               //定义点和基本运算
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    Point operator + (Point B){return Point(x+B.x,y+B.y);}
    Point operator - (Point B){return Point(x-B.x,y-B.y);}
    Point operator * (double k){return Point(x*k,y*k);}
    Point operator / (double k){return Point(x/k,y/k);}
};
typedef Point Vector;                          //定义向量
double Dot(Vector A,Vector B){return A.x*B.x + A.y*B.y;} //点积
double Len(Vector A){return sqrt(Dot(A,A));}   //向量的长度
double Len2(Vector A){return Dot(A,A);}         //向量长度的平方
double Cross(Vector A,Vector B){return A.x*B.y - A.y*B.x;} //叉积
double Distance(Point A, Point B){return hypot(A.x-B.x,A.y-B.y);}
struct Line{
    Point p1,p2;
    Line(){}
    Line(Point p1,Point p2):p1(p1),p2(p2){}
};
typedef Line Segment;             //定义线段，两端点是p1,p2
int Point_line_relation(Point p,Line v){
    int c = sgn(Cross(p-v.p1,v.p2-v.p1));
    if(c < 0)return 1;       //1：p在v的左边
    if(c > 0)return 2;       //2：p在v的右边
    return 0;                 //0：p在v上
}
double Dis_point_line(Point p, Line v){ //点到直线的距离
    return fabs(Cross(p-v.p1,v.p2-v.p1))/Distance(v.p1,v.p2);
}
//点到线段的距离
double Dis_point_seg(Point p, Segment v){
    if(sgn(Dot(p- v.p1,v.p2-v.p1))<0 || sgn(Dot(p- v.p2,v.p1-v.p2))<0)
        return min(Distance(p,v.p1),Distance(p,v.p2));
    return Dis_point_line(p,v);
}
//点在直线上的投影
Point Point_line_proj(Point p, Line v){
    double k=Dot(v.p2-v.p1,p-v.p1)/Len2(v.p2-v.p1);
    return v.p1+(v.p2-v.p1)*k;
}
//点p对直线v的对称点
Point Point_line_symmetry(Point p, Line v){
    Point q = Point_line_proj(p,v);
    return Point(2*q.x-p.x,2*q.y-p.y);
}
struct Circle{
    Point c;       //圆心
    double r;      //半径
    Circle(){}
    Circle(Point c,double r):c(c),r(r){}
    Circle(double x,double y,double _r){c=Point(x,y);r = _r;}
};
//线段和圆的关系：0 线段在圆内, 1 线段和圆相切, 2 线段在圆外
int Seg_circle_relation(Segment v,Circle C){
    double dst = Dis_point_seg(C.c,v);
    if(sgn(dst-C.r) < 0) return 0;
    if(sgn(dst-C.r) ==0) return 1;
    return 2;
}
//直线和圆的关系：0 直线在圆内, 1 直线和圆相切, 2 直线在圆外
int Line_circle_relation(Line v,Circle C){
    double dst = Dis_point_line(C.c,v);
    if(sgn(dst-C.r) < 0) return 0;
    if(sgn(dst-C.r) ==0) return 1;
    return 2;
}
//直线和圆的交点，pa, pb是交点。返回值是交点个数
int Line_cross_circle(Line v,Circle C,Point &pa,Point &pb){
    if(Line_circle_relation(v, C)==2) return 0;    //无交点
    Point q = Point_line_proj(C.c,v);        //圆心在直线上的投影点
    double d = Dis_point_line(C.c,v);        //圆心到直线的距离
    double k = sqrt(C.r*C.r-d*d);
    if(sgn(k) == 0){                             //1个交点，直线和圆相切
        pa = q;   pb = q;  return 1;
    }
    Point n=(v.p2-v.p1)/ Len(v.p2-v.p1);  //单位向量
    pa = q + n*k;
    pb = q - n*k;
    return 2;                                   //2个交点
}
int main() {
    int T; scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        Circle O; Point A,B,V;
        scanf("%lf%lf%lf", &O.c.x, &O.c.y, &O.r);
        scanf("%lf%lf%lf%lf", &A.x, &A.y, &V.x, &V.y);
        scanf("%lf%lf", &B.x, &B.y);
        Line l(A, A+V);      //射线
        Line t(A, B);
            //情况（1）直线和圆不相交，而且直线经过点
        if(Point_line_relation(B,l)==0
            && Seg_circle_relation(t,O)>=1 && sgn(Cross(B-A,V))==0)
            printf("Case #%d: Yes\n", cas);
        else{
            Point pa, pb;         //直线和圆的交点
           //情况（2）直线和圆相切，不经过点
           if(Line_cross_circle(l,O,pa,pb) != 2)
				printf("Case #%d: No\n",cas);
           //情况（3）直线和圆相交
           else{
                Point cut; //直线和圆的碰撞点
                if(Distance(pa,A) > Distance(pb,A)) cut = pb;
                else cut = pa;
                Line mid(cut, O.c); //圆心到碰撞点的的直线;
                Point en = Point_line_symmetry(A,mid);  //镜像点
                Line light(cut, en);                       //反射线
                if(Distance(light.p2,B) > Distance(light.p1,B))
				  swap(light.p1, light.p2);                							 	  if(sgn(Cross(light.p2-light.p1,
							    Point(B.x-cut.x,B.y-cut.y)))== 0)
                printf("Case #%d: Yes\n", cas);
                else
				   printf("Case #%d: No\n", cas);
            }
        }
    }
    return 0;
}
