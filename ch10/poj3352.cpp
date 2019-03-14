//ECUST luoyongjun
#include<cstring>
#include<vector>
#include<stdio.h>
using namespace std;
const int N = 1005;
int n, m, low[N], dfn;
vector<int> G[N];            //存图
void dfs(int u,int fa){     //计算每个点的low值
    low[u]= ++dfn;
    for(int i=0;i<G[u].size();i++){
        int v = G[u][i];
        if(v == fa) continue;
        if(!low[v])
            dfs(v,u);
        low[u] = min(low[u], low[v]);
    }
}
int tarjan(){
    int degree[N];                  //计算每个缩点的度数
    memset(degree,0,sizeof(degree));
    for(int i=1; i<=n; i++)       //把有相同low值的点看成一个缩点
        for(int j=0; j<G[i].size(); j++)
            if(low[i] != low[G[i][j]])
                degree[low[i]]++;
    int res=0;
    for(int i=1;i<=n;i++)          //统计度数为1的缩点个数
        if(degree[i]==1) res++;
    return res;
}
int main(){
    while(~scanf("%d%d", &n, &m)){
        memset(low, 0, sizeof(low));
        for(int i=0; i<=n; i++)   G[i].clear();
        for(int i=1; i<=m; i++){
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);  G[b].push_back(a);
        }
        dfn = 0;
        dfs(1,-1);
        int ans = tarjan();
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}
