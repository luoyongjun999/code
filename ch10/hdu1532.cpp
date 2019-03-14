//ECUST luoyongjun
#include<bits/stdc++.h>
const int INF = 1e9;
const int maxn = 300;
using namespace std;
int n, m, map_[maxn][maxn], pre[maxn];
    // map_[][]不仅记录图，还是残留网络
int bfs(int s,int t){
    int flow[maxn];
    memset(pre,-1,sizeof pre);
    flow[s]=INF; pre[s] = 0;            //初始化起点
    queue<int> Q;  Q.push(s);           //起点入栈，开始bfs
    while(!Q.empty()){
        int u = Q.front();  Q.pop();
        if(u==t) break;                  //搜到一个路径，这次bfs结束
        for(int i=1; i<=m; i++){        //bfs所有的点
            if(i!=s && map_[u][i]>0 && pre[i]==-1){
                pre[i] = u;  		    //记录路径
                Q.push(i);
                flow[i] = min(flow[u], map_[u][i]); //更新结点流量
            }
        }
    }
    if(pre[t]==-1) return -1;           //没有找到新的增广路
    return flow[t];                       //返回这个增广路的流量
}
int maxflow(int s, int t){
    int Maxflow = 0;
    while(1){
        int flow = bfs(s,t);
//执行一次bfs，找到一条路径，返回路径的流量
        if(flow == -1) break;             //没有找到新的增广路，结束
        int cur = t;                        //更新路径上的残留网络
        while(cur!=s){                      //一直沿路径回溯到起点
            int father = pre[cur];        //pre[]记录路径上的前一个点
            map_[father][cur] -= flow;    //更新残留网络：正向减
            map_[cur][father] += flow;    //更新残留网络：反向加
            cur = father;
        }
        Maxflow += flow;
    }
    return Maxflow;
}
int main(){
    while(~scanf("%d%d",&n,&m)){
        memset(map_,0,sizeof map_);
        for(int i=0; i<n; i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            map_[u][v]+=w;            //可能有重边
        }
        printf("%d\n",maxflow(1,m));
    }
    return 0;
}
