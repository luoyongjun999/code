//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int N = 6000+5;
int value[N], dp[N][2], father[N], n;
vector <int> tree[N];
void dfs(int u){
    dp[u][0] = 0;                          //赋初值：不参加宴会
    dp[u][1] = value[u];                  //赋初值：参加宴会
    for(int i=0;i<tree[u].size();i++){  //逐一处理这个父结点的每个子结点
        int son = tree[u][i];
        dfs(son);                            //深搜子结点
        dp[u][0] += max(dp[son][1], dp[son][0]);
						                 //父结点不选，子结点可选可不选
        dp[u][1] += dp[son][0];           //父结点选择，子结点不选
   }
}
int main(){
    while(~scanf("%d",&n)) {
      for(int i=1;i<=n;i++)  {
          scanf("%d",&value[i]);
          tree[i].clear();
          father[i] = -1;                 //赋初值，还未建立关系
      }
      while(1) {
        int a,b;
        scanf("%d%d",&a,&b);
        if(a==0&&b==0)  break;
        tree[b].push_back(a);         //用邻接表建树
        father[a]=b;                    //父子关系
      }
      int t = 1;
      while(father[t] != -1)          //查找树的根结点
        t = father[t];
      dfs(t);                            //从根结点开始，用dfs遍历整棵树
      printf("%d\n", max(dp[t][1], dp[t][0]));
    }
    return 0;
}
