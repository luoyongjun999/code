//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const int MAXN = 100010;
const double INF = 1e20;
int sgn(double x){
    if(fabs(x) < eps)  return 0;
    else return x<0?-1:1;
}
struct Point{
    double x,y;
 };
double Distance(Point A, Point B){return hypot(A.x-B.x,A.y-B.y);}
bool cmpxy(Point A,Point B){     //排序：先对横坐标x排序，再对y排序
	return sgn(A.x-B.x)<0 || (sgn(A.x-B.x)==0 && sgn(A.y-B.y)<0);
}
bool cmpy (Point A,Point B){return sgn(A.y-B.y)<0;}//只对y坐标排序
Point p[MAXN],tmp_p[MAXN];
double Closest_Pair(int left,int right){
    double dis = INF;
    if(left == right) return dis;      //只剩1个点
    if(left + 1 == right)                //只剩2个点
        return Distance(p[left], p[right]);
    int mid = (left+right)/2;           //分治
    double d1 = Closest_Pair(left,mid);      //求s1内的最近点对
    double d2 = Closest_Pair(mid+1,right);  //求s2内的最近点对
    dis = min(d1,d2);
    int k = 0;
    for(int i=left;i<=right;i++)       //在s1和s2中间附近找可能的最小点对
        if(fabs(p[mid].x - p[i].x) <= dis)  //按x坐标来找
            tmp_p[k++] = p[i];
	sort(tmp_p,tmp_p+k,cmpy);//按y坐标排序，用于剪枝。这里不能按x坐标排序
    for(int i=0;i<k;i++)
        for(int j=i+1;j<k;j++){
            if(tmp_p[j].y - tmp_p[i].y >= dis)  break;    //剪枝
            dis = min(dis,Distance(tmp_p[i],tmp_p[j]));
        }
	return dis;  //返回最小距离
}
int main(){
    int n;
    while(~scanf("%d",&n) && n){
        for(int i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        sort(p,p+n,cmpxy);                          //先排序
        printf("%.2f\n",Closest_Pair(0,n-1)/2); //输出最短距离的一半
    }
    return 0;
}
