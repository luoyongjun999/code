//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const double INF = 1e12;
const double pi = acos(-1.0);
const double eps = 1e-8;
int sgn(double x){
    if(fabs(x) < eps)  return 0;
    else return x<0?-1:1;
}
struct Point{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    Point operator + (Point B){return Point(x+B.x,y+B.y);}
    Point operator - (Point B){return Point(x-B.x,y-B.y);}
    Point operator * (double k){return Point(x*k,y*k);}
};
typedef Point Vector;
double Cross(Vector A,Vector B){return A.x*B.y - A.y*B.x;} //叉积
struct Line{
	Point p;
	Vector v;
	double ang;
	Line(){};
	Line(Point p,Vector v):p(p),v(v){ang=atan2(v.y,v.x);}
	bool operator < (Line &L){return ang<L.ang;}     //用于极角排序
};
//点p在线L左边，即点p在线L在外面：
bool OnLeft(Line L,Point p){return sgn(Cross(L.v,p-L.p))>0;}
Point Cross_point(Line a,Line b){    //两直线交点
    	Vector u=a.p-b.p;
		double t=Cross(b.v,u)/Cross(a.v,b.v);
		return a.p+a.v*t;
}
vector<Point> HPI(vector<Line> L){     //求半平面交，返回图多边形
	int n=L.size();
	sort(L.begin(),L.end());//将所有半平面按照极角排序。
	int first,last;       //指向双端队列的第一个和最后一个元素
	vector<Point> p(n);  //两个相邻半平面的交点
	vector<Line> q(n);   //双端队列
	vector<Point> ans;   //半平面交形成的凸包
	q[first=last=0]=L[0];
	for(int i=1;i<n;i++){
		//情况1：删除尾部的半平面
		while(first<last && !OnLeft(L[i], p[last-1])) last--;
		//情况2：删除首部的半平面：
		while(first<last && !OnLeft(L[i], p[first]))  first++;
		q[++last]=L[i];     //将当前的半平面加入双端队列尾部
		//极角相同的两个半平面，保留左边：
		if(fabs(Cross(q[last].v,q[last-1].v)) < eps){
			last--;
			if(OnLeft(q[last],L[i].p)) q[last]=L[i];
		}
		//计算队列尾部半平面交点：
		if(first<last) p[last-1]=Cross_point(q[last-1],q[last]);
	}
	//情况3：删除队列尾部的无用半平面
	while(first<last && !OnLeft(q[first],p[last-1])) last--;
	if(last-first<=1) return ans;   //空集
	p[last]=Cross_point(q[last],q[first]);  //计算队列首尾部的交点。
	for(int i=first;i<=last;i++)  ans.push_back(p[i]);   //复制。
	return ans;               //返回凸多边形
}
int main(){
     int T,n;
		cin>>T;
		while(T--){
			cin>>n;
		    vector<Line> L;
		   //加一个半平面F:反向y轴
         L.push_back(Line(Point(0,0),Vector(0,-1)));
			//加一个半平面E:y极大的向左的直线
		    L.push_back(Line(Point(0,INF),Vector(-1,0)));
  	    while(n--){
				double a,b;
				scanf("%lf%lf",&a,&b);
			 	L.push_back(Line(Point(0,a),Vector(1,b)));
		 }
		 vector<Point> ans=HPI(L);        //得到凸多边形
		 printf("%d\n",ans.size()-2);    //去掉人为加的两个点
	 }
     return 0;
}
