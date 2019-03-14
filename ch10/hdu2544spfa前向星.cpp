//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int INF = INT_MAX / 10;
const int NUM = 1000005;     //一百万个点,一百万个边
struct Edge{   //边：edge[i]的i就是起点，终点to，权值w。下一个边next
int to, next, w;
}edge[NUM];
int n, m, cnt;
int head[NUM];
int dis[NUM];            //记录所有结点到起点的距离
bool inq[NUM];           //inq[i] = true 表示结点i在队列中
int Neg[NUM];            //判断负圈(Negative loop)
int pre[NUM];             //记录前驱结点。
void print_path(int s,int t) {   //打印从s到t的最短路径
   ;         //内容与Bellman-Ford程序中的print_path()完全一样
}
void init(){
    for(int i = 0; i < NUM; ++i){
        edge[i].next = -1;
        head[i] = -1;
    }
    cnt = 0;
}
void addedge(int u, int v, int w){      //前向星存图
   edge[cnt].to = v;
   edge[cnt].w = w;
   edge[cnt].next = head[u];
   head[u] = cnt++;
}
int spfa(int s) {
    memset(Neg, 0, sizeof(Neg));
    Neg[s] = 1;
    for(int i=1; i<=n; i++) { dis[i]=INF;  inq[i]=false; }   //初始化
    dis[s] = 0;             //起点到自己的距离是0
    queue<int> Q;
    Q.push(s);
    inq[s] = true;           //起点进队列

    while(!Q.empty()) {
        int u = Q.front(); Q.pop();    //队头出队
        inq[u] = false;
        for(int i=head[u]; ~i; i = edge[i].next) {//~i也可以写成 i!=-1
            int v = edge[i].to, w = edge[i].w;
            if (dis[u]+w < dis[v]) {
//u的第i个邻居v，它借道u，到s更近
                dis[v] = dis[u]+w;   //更新第i个邻居到s的距离
                pre[v] = u;           //如果有需要，记录路径
                if(!inq[v]) {
            //邻居v更新状态了，但是它不在队列中，把它放进队列
                    inq[v] = true;
                    Q.push(v);
                    Neg[v]++;
                    if(Neg[v] > n) return 1;    //出现负圈
                }
            }
        }
    }
    printf("%d\n",dis[n]);  //从s的n的最短距离
    // print_path(s,n);     //如果有需要，打印路径
    return 0;
}
int main() {
    while(~scanf("%d%d",&n,&m)) {
init();
       	if(n==0 && m==0) return 0;
       	while(m--) {
            int u,v,w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u,v,w);
            addedge(v,u,w);
       	}
       	spfa(1);
    }
    return 0;
}
