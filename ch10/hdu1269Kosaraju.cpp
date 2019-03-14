//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int NUM = 10005;
vector<int> G[NUM], rG[NUM];
vector<int> S;             //存第一次dfs1的结果：标记点的先后顺序
int vis[NUM], sccno[NUM], cnt;   // cnt：强连通分量的个数
void dfs1(int u) {
    if(vis[u]) return;
    vis[u] = 1;
    for(int i=0; i<G[u].size(); i++)   dfs1(G[u][i]);
    S.push_back(u);       //记录点的先后顺序，标记大的放在S的后面
}
void dfs2(int u) {
    if(sccno[u]) return;
    sccno[u] = cnt;
    for(int i=0; i < rG[u].size(); i++)   dfs2(rG[u][i]);
}
void Kosaraju(int n) {
   cnt = 0;
   S.clear();
   memset(sccno, 0, sizeof(sccno));
   memset(vis, 0, sizeof(vis));
   for(int i = 1; i <= n; i++)  dfs1(i);  //点的编号：1~n。递归所有点
   for(int i = n-1; i >= 0; i--)
       if(!sccno[S[i]]) { cnt++; dfs2(S[i]);}
}
int main(){
    int n, m, u, v;
    while(scanf("%d%d", &n, &m), n != 0 || m != 0) {
        for(int i = 0; i < n; i++) { G[i].clear(); rG[i].clear();}
        for(int i = 0; i < m; i++){
            scanf("%d%d", &u, &v);
            G[u].push_back(v);    //原图
            rG[v].push_back(u);   //反图
        }
        Kosaraju(n);
        printf("%s\n", cnt == 1 ? "Yes" : "No");
    }
    return 0;
}
