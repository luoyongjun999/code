//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int N = 10100;
struct Node{
    int id;                  //子结点的编号
    int cost;
};
vector<Node> tree[N];
int dp[N][3];
int n;
void init_read(){
    for(int i=1; i<=n; i++)
       tree[i].clear();
    memset(dp, 0, sizeof(dp));
    for(int i=2; i<=n; i++) {
       int x,y;
       scanf("%d%d",&x,&y);
       Node tmp;
       tmp.cost = y;
       tmp.id=i;              //i是x的子结点
       tree[x].push_back(tmp);
    }
}
void dfs1(int father) {     //dfs，先处理子结点，再处理父结点
    int one=0, two=0;
    for(int i=0; i<tree[father].size(); i++) {
                                 //遍历结点father的所有子结点
        Node child = tree[father][i];
        dfs1(child.id);       //递归子结点，直到最底层
        int cost = dp[child.id][0] + child.cost;
        if(cost >= one) {    //用one记录从father往下走的最长距离
            two = one;         //原来的最长距离one，变成第2长，用two记录
            one = cost;
        }
        if(cost < one && cost >two)     //用two记录第2长的距离
            two = cost;
    }
    dp[father][0] = one;  //得到以father为起点的子树的最长距离
    dp[father][1] = two;  //得到以father为起点的子树的第2长距离
}
void dfs2(int father) {    //先处理父结点，再处理子结点
    for(int i=0; i<tree[father].size(); i++) {
        Node child = tree[father][i];
        if(dp[child.id][0]+ child.cost == dp[father][0])
                                //child在最长距离的子树上
            dp[child.id][2] = max(dp[father][2],
                                       dp[father][1]) + child.cost;
        else                    //child不在最长距离的子树上
            dp[child.id][2] = max(dp[father][2],
                                       dp[father][0]) + child.cost;
        dfs2(child.id);
    }
}
int main(){
    while(~scanf("%d", &n)) {
        init_read();          //初始化、读数据
        dfs1(1);               //计算dp[][0]、dp[][1]
        dp[1][2]=0;
        dfs2(1);               //计算dp[][2]
        for(int i=1; i<=n; i++)
            printf("%d\n", max(dp[i][0], dp[i][2]));
    }
    return 0;
}
