#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int N=109;
int low[N],num[N],dfn;
bool iscut[N];
vector <int> G[N];
void dfs(int u, int fa){       //u的父结点是fa
	low[u] = num[u] = ++ dfn;     //初始值
	int child = 0;                  //孩子数目
	for (int i = 0;i < G[u].size(); i++)	{   //处理u的所有子结点
		int v = G[u][i];
		if (!num[v]) {              //v没访问过
		    child++;
			dfs(v, u);
			low[u] = min(low[v], low[u]);    //用后代的返回值更新low值
			if (low[v] >= num[u] && u !=1)
                iscut[u] = true;              //标记割点
		}
		else if(num[v] < num[u] && v != fa)
 		       //处理回退边，注意这里v != fa，fa是u的父结点，
       //fa也是u的邻居，但是前面已经访问过，不需要处理它
            low[u] = min(low[u], num[v]);
	}
	if (u == 1 && child >= 2)     //根结点，有两个以上不相连的子树
        iscut[1] = true;
}
int main(){
    int ans,n;
	while (scanf("%d",&n)!=-1){
		if (n==0)break;
		memset(low,0,sizeof(low));
		memset(num,0,sizeof(num));
		dfn=0;
		for (int i=0;i<=n;i++) G[i].clear();
		int a,b;
		while (scanf("%d",&a)&&a)
			while (getchar()!='\n'){
				scanf("%d",&b);
				G[a].push_back(b);
				G[b].push_back(a);
			}
		memset(iscut,false,sizeof(iscut));
		ans = 0;
		dfs(1,1);
		for (int i=1;i<=n;i++) ans+=iscut[i];
		printf("%d\n",ans);
	}
}
