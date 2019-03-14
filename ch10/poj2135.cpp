//ECUST luoyongjun
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1010;
int dis[N], pre[N], preve[N];
//dis[i]记录起点到i的最短距离。pre和 preve见下面注释
int n, m;
struct edge{
    int to, cost, capacity, rev;        //rev用于记录前驱点
    edge(int to_,int cost_,int c,int rev_){
          to=to_; cost=cost_; capacity=c; rev=rev_;}
};
vector<edge> e[N];           //e[i]：存第i个结点连接的所有的边
void addedge(int from,int to,int cost,int capacity){//把1个有向边再分为2个
    e[from].push_back(edge(to, cost, capacity, e[to].size()));
    e[to].push_back(edge(from, -cost, 0, e[from].size()-1));
}
bool spfa(int s, int t, int cnt){          //套SPFA模板
    bool inq[N];
    memset(pre, -1, sizeof(pre));
    for(int i = 1; i <= cnt; ++i) { dis[i]=INF; inq[i]=false; }
    dis[s] = 0;
    queue <int> Q;
    Q.push(s);
    inq[s] = true;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for(int i=0; i < e[u].size(); i++)
            if(e[u][i].capacity > 0){
                int v = e[u][i].to, cost = e[u][i].cost;
                if(dis[u]+cost < dis[v]){
                    dis[v] = dis[u]+cost;
                    pre[v] = u;        //v的前驱点是u
                    preve[v] = i;      // u的第i个边连接v点
                    if(!inq[v]){
                        inq[v] = true;
                        Q.push(v);
                    }
                }
            }
    }
    return dis[t] != INF;   //s到t的最短距离（或者最小费用）是dis[t]
}
int mincost(int s, int t, int cnt){      //基本上是套最大流模板
    int cost = 0;
    while(spfa(s, t, cnt)){
        int v = t, flow = INF;        //每次增加的流量
        while(pre[v] != -1){          //回溯整个路径，计算路径的流
            int u = pre[v], i = preve[v];
                     //u是v的前驱点，u的第i个边连接v
            flow = min(flow, e[u][i].capacity);
                     //所有边的最小容量就是这条路的流
            v = u;                   //回溯，直到源点
        }
        v = t;
        while(pre[v] != -1){                      //更新残留网络
            int u = pre[v], i = preve[v];
            e[u][i].capacity -= flow;            //正向减
            e[v][e[u][i].rev].capacity += flow;//反向加，注意rev的作用
            v = u;                                   //回退，直到源点
        }
        cost += dis[t]*flow;
                        //费用累加。如果程序需要输出最大流，在这里累加flow
    }
    return cost;                //返回总费用
}
int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0; i < N; i++)  e[i].clear();   //清空待用
        for(int i = 1; i <= m; ++i){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w, 1);        //把1个无向边分为2个有向边
            addedge(v, u, w, 1);
        }
        int s = n+1, t = n+2;
        addedge(s, 1, 0, 2);           //添加源点
        addedge(n, t, 0, 2);           //添加汇点
        printf("%d\n", mincost(s, t, n+2));
    }
    return 0;
}
