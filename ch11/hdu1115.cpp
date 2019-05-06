//ECUST luoyongjun
#include <bits/stdc++.h>
struct Point{
    double x,y;
    Point(double X=0,double Y=0){x=X,y=Y;}
    Point operator + (Point B){return Point (x+B.x,y+B.y);}
    Point operator - (Point B){return Point (x-B.x,y-B.y);}
    Point operator * (double k){return Point (x*k,y*k);}
    Point operator / (double k){return Point (x/k,y/k);}
};
typedef Point Vector;
double Cross(Vector A,Vector B){return A.x*B.y - A.y*B.x;}
double Polygon_area(Point *p, int n){    //求多边形面积
    double area = 0;
    for(int i = 0;i < n;i++)
        area += Cross(p[i],p[(i+1)%n]);
    return area/2;                            //面积有正负，不能取绝对值
}
Point Polygon_center(Point *p, int n){    //求多边形重心
    Point ans(0,0);
    if(Polygon_area(p,n)==0) return ans;
    for(int i = 0;i < n;i++)
        ans = ans+(p[i]+p[(i+1)%n])*Cross(p[i],p[(i+1)%n]);
    return ans/Polygon_area(p,n)/6;
}
int main(){
    int t,n,i;
    Point center;          //重心坐标
    Point p[100000];
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(i=0;i<n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
        center=Polygon_center(p,n);
        printf("%.2f %.2f\n",center.x,center.y);//注意这里输出用%f，不是%lf
    }
    return 0;
}
