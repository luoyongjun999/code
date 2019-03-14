//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e6;
const int NUM = 105;
struct edge{
int from, to, w;
//边：起点from，终点to，权值w。from并没有用到，e[i]的i就是from
    edge(int a, int b,int c){from=a; to=b; w=c;}
};
vector<edge> e[NUM];       //e[i]：存第i个结点连接的所有的边
int n, m;
int pre[NUM];
 //记录前驱结点。pre[x]=y，在最短路径上，结点x的前一个结点是y
void print_path(int s,int t) {    //打印从s到t的最短路径
   ;       //内容与Bellman-Ford程序中的print_path()完全一样
}
int spfa(int s){
    int dis[NUM];      //记录所有结点到起点的距离
    bool inq[NUM];     //inq[i] = true 表示结点i在队列中
    int Neg[NUM];      //判断负圈,Negative loop
    memset(Neg, 0, sizeof(Neg));
    Neg[s] = 1;
    for(int i=1;i<=n;i++) { dis[i]=INF;  inq[i]=false; }   //初始化
    dis[s] = 0;          //起点到自己的距离是0
    queue<int> Q;
    Q.push(s);
    inq[s] = true;        //起点进队列
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();           //队头出队
        inq[u] = false;
        for(int i=0; i < e[u].size(); i++) {    //检查结点u的所有邻居
            int v = e[u][i].to, w = e[u][i].w;
            if (dis[u]+w < dis[v])  {
//u的第i个邻居v，它借道u，到s更近
               dis[v] = dis[u]+w; //更新第i个邻居到s的距离
                pre[v] = u;        //如果有需要，记录路径
                if(!inq[v]) {
//第i个邻居更新状态了，但是它不在队列中，把它放进队列
                    inq[v] = true;
                    Q.push(v);
                    Neg[v]++;
                    if(Neg[v] > n) return 1;  //出现负圈
                }
            }
        }
    }
    printf("%d\n",dis[n]);
    //print_path(s,n);   //如果有需要，打印路径
return 0;
}
int main(){
    while(~scanf("%d%d",&n,&m)) {
        if(n==0 && m==0)     return 0;
        for(int i=1; i<=n; i++)   e[i].clear();
        while(m--) {
            int a,b,c;
            scanf("%d%d%d", &a, &b, &c);
            e[a].push_back(edge(a,b,c));
//结点a的邻居，都放在node[a]里
            e[b].push_back(edge(b,a,c));
        }
        spfa(1);    //起点是1
    }
    return 0;
}
