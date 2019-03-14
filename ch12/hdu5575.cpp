//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int N = 200100;
const int INF = 2000000000;
int n, m, h[N], st[N], wh[N], height[N * 2], val[N * 2][2], dp[N * 2][2];
int lca[N * 2][18], dep[N * 2];
vector<int > pos[2], off[2], high[N * 2][2];
vector<int > edge[2 * N];
void clear(){
	for(int i = 0; i <= n; ++ i) {
		edge[i].clear();
		high[i][0].clear(); high[i][1].clear();
	}
	pos[0].clear(); off[0].clear();
	pos[1].clear(); off[1].clear();
}
void pre_dfs(int u, int fa, int dist) {
	lca[u][0] = fa; dep[u] = dist;
	for(int i = 1; i < 18; ++ i)
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	for(int i = 0; i < edge[u].size(); ++ i) {
		int v = edge[u][i];
		pre_dfs(v, u, dist + 1);
	}
}
int get_node(int x, int y) {
	for(int i = 17; i >= 0; -- i)
		if(dep[x] > (1 << i) && height[lca[x][i]] <= y)
			x = lca[x][i];
	return x;
}
void add_edge(int x, int y) {
	edge[x].push_back(y);
}
void build_tree() {
	int tot = n, top = 0;
	h[n] = INF;	height[0] = INF;
	for(int i = 1; i <= n; ++ i) {
		height[i] = 0; val[i][0] = val[i][1] = 0;
		wh[top] = i;
		while(top > 0 && st[top - 1] < h[i]) {
			++ tot;
			height[tot] = st[top - 1];
			val[tot][0] = val[tot][1] = 0;
			int tid = top - 1;
			add_edge(tot, wh[top]);
			while(top > 0 && st[top - 1] == st[tid]){
				-- top;
				add_edge(tot, wh[top]);
			}
			wh[top] = tot;
		}
		st[top ++] = h[i];
	}
	n = tot;
	for(int i = 0; i < 18; ++ i)
		lca[0][i] = 0;
	pre_dfs(n, 0, 1);
	for(int i = 0; i < 2; ++ i) {
		for(int j = 0; j < pos[i].size(); ++ j) {
			int id = get_node(pos[i][j], off[i][j]);
			val[id][i] ++; high[id][i].push_back(off[i][j]);
		}
	}
}
void dfs(int u) {
	dp[u][0] = val[u][0];
	dp[u][1] = val[u][1];
	sort(high[u][0].begin(), high[u][0].end());
	sort(high[u][1].begin(), high[u][1].end());
	int p = 0, ret = 0;
	for(int i = 0; i < val[u][0]; ++ i) {
		while(p < val[u][1] && high[u][1][p] < high[u][0][i])
			++ p;
		ret = max(ret, p + val[u][0] - i);
	}
	int flag = val[u][0], Mind = INF;
	for(int i = 0; i < edge[u].size(); ++ i) {
		int v = edge[u][i];
		dfs(v);
		dp[u][1] += dp[v][1];
		dp[u][0] += max(dp[v][0], dp[v][1]);
	}
	dp[u][0] = max(dp[u][0], dp[u][1] - val[u][1] + ret);
}
void solve() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++ i)
		scanf("%d", h + i);
	for(int i = 1; i <= m; ++ i) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		pos[z].push_back(x); off[z].push_back(y);
	}
	build_tree();
	dfs(n);
	printf("%d\n", max(dp[n][0], dp[n][1]));
	clear();
}
int main() {
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++ i) {
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
