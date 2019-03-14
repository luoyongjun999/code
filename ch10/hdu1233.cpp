//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int NUM = 103;
int S[NUM];                                         //并查集
struct Edge {int u, v, w;} edge[NUM*NUM];     //定义边
bool cmp(Edge a, Edge b)  { return a.w < b.w; }
int find(int u) { return S[u] == u ? u : find(S[u]); }
              //查询并查集，返回u的根结点
int n, m;        //点，边
int kruskal() {
        int ans = 0;
        for(int i=1; i<=n; i++)
S[i]=i;                //初始化，开始时每个村庄都是单独的集
        sort(edge+1, edge+1+m, cmp);
        for(int i = 1; i <= m; i++) {
            int b = find(edge[i].u);    //边的前端点u属于哪个集？
            int c = find(edge[i].v);    //边的后端点v属于哪个集？
            if(b == c) continue;         //产生了圈，丢弃这个边
            S[c] = b;                      //合并
            ans += edge[i].w;            //计算MST
        }
        return ans;
}
int main() {
    while(scanf("%d", &n), n) {
        m = n*(n-1)/2;
        for(int i = 1; i <= m; i++)     //题目中，点的编号从1开始
            scanf("%d%d%d",&edge[i].u, &edge[i].v, &edge[i].w);
        printf("%d\n", kruskal());
    }
    return 0;
}
