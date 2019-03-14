//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int maxn = 104;
const double eps = 1e-8;
int sgn(double x){        //判断x是否等于0
    if(fabs(x) < eps)  return 0;
    else return x<0?-1:1;
}
struct Point{
    double x,y;
    Point(){}
    Point(double x, double y):x(x),y(y){}
    Point operator + (Point B){return Point(x+B.x,y+B.y);}
    Point operator - (Point B){return Point(x-B.x,y-B.y);}
    bool operator == (Point B){return sgn(x-B.x) == 0 && sgn(y-B.y) == 0;}
    bool operator < (Point B){                  //用于sort()排序
        return sgn(x-B.x)<0 || (sgn(x-B.x)==0 && sgn(y-B.y)<0);}
};
typedef Point Vector;
double Cross(Vector A,Vector B){return A.x*B.y - A.y*B.x;} //叉积
double Distance(Point A,Point B){return hypot(A.x-B.x,A.y-B.y);}
//Convex_hull()求凸包。凸包顶点放在ch中，返回值是凸包的顶点数
int Convex_hull(Point *p,int n,Point *ch){
    sort(p,p+n);          //对点排序：按x从小到大排序，如果x相同，按y排序
    n=unique(p,p+n)-p;   //去除重复点
    int v=0;
	//求下凸包。如果p[i]是右拐弯的，这个点不在凸包上，往回退
    for(int i=0;i<n;i++){
        while(v>1 && sgn(Cross(ch[v-1]-ch[v-2],p[i]-ch[v-2]))<=0)
			v--;
        ch[v++]=p[i];
    }
    int j=v;
	//求上凸包
    for(int i=n-2;i>=0;i--){
        while(v>j && sgn(Cross(ch[v-1]-ch[v-2],p[i]-ch[v-2]))<=0)
			v--;
        ch[v++]=p[i];
    }
    if(n>1) v--;
    return v;                   //返回值v是凸包的顶点数
}
int main(){
    int n;
    Point p[maxn],ch[maxn];    //输入点是p[]，凸包顶点放在ch[]中
    while(scanf("%d",&n) && n){
        for(int i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        int v = Convex_hull(p,n,ch);    //返回凸包的顶点数v
        double ans=0;
        if(v==1) ans=0;
        else if(v==2) ans=Distance(ch[0],ch[1]);
        else
            for(int i=0;i<v;i++)          //计算凸包周长
                ans+=Distance(ch[i],ch[(i+1)%v]);
        printf("%.2f\n",ans);
    }
    return 0;
}
