//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
#define eps 1e-8
const int maxn = 505;
int sgn(double x){
    if(fabs(x) < eps)  return 0;
    else return x<0?-1:1;
}
struct Point{
    double x, y;
};
double Distance(Point A, Point B){return hypot(A.x-B.x,A.y-B.y);}
//求三角形abc的外接圆的圆心：
Point circle_center(const Point a, const Point b, const Point c){
    Point center;
    double a1=b.x-a.x, b1=b.y-a.y, c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x, b2=c.y-a.y, c2=(a2*a2+b2*b2)/2;
    double d =a1*b2-a2*b1;
    center.x =a.x+(c1*b2-c2*b1)/d;
    center.y =a.y+(a1*c2-a2*c1)/d;
    return center;
}
//求最小覆盖圆，返回圆心c，半径r：
void min_cover_circle(Point *p, int n, Point &c, double &r){
    random_shuffle(p, p + n);  //随机函数，打乱所有点。这一步很重要
    c=p[0]; r=0;                  //从第1个点p0开始。圆心为p0，半径为0
    for(int i=1;i<n;i++)         //扩展所有点
        if(sgn(Distance(p[i],c)-r)>0){ //点pi在圆外部
            c=p[i]; r=0;                   //重新设置圆心为pi，半径为0
            for(int j=0;j<i;j++)         //重新检查前面所有的点。
                if(sgn(Distance(p[j],c)-r)>0){   //两点定圆
                    c.x=(p[i].x + p[j].x)/2;
                    c.y=(p[i].y + p[j].y)/2;
                    r=Distance(p[j],c);
                    for(int k=0;k<j;k++)
                        if (sgn(Distance(p[k],c)-r)>0){//两点不能定圆，就三点定圆
                            c=circle_center(p[i],p[j],p[k]);
                            r=Distance(p[i], c);
                        }
                }
        }
}
int main(){
    int n;                //点的个数
    Point p[maxn];      //输入点
    Point c; double r;  //最小覆盖圆的圆心和半径
    while(~scanf("%d",&n) && n){
        for(int i=0;i<n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
        min_cover_circle(p,n,c,r);
        printf("%.2f %.2f %.2f\n",c.x,c.y,r);
    }
    return 0;
}
