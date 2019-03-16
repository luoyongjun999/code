//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int COIN = 101;                   //题目要求不超过100个硬币
const int MONEY = 251;                  //题目给定的钱数不超过250
int dp[MONEY][COIN] = {0};              // DP转移矩阵
int type[5] = {1, 5, 10, 25, 50};      //5种面值
void solve() {                             // DP
    dp[0][0] = 1;
    for(int i=0; i<5; i++)
        for(int j=1; j<COIN; j++)
            for(int k = type[i]; k < MONEY; k++)
                dp[k][j] += dp[k-type[i]][j-1];
}
int main() {
    int s;
    int ans[MONEY] = {0};
    solve();                          //用DP计算完整的转移矩阵
    for(int i=0; i< MONEY; i++)   //对每个金额，计算有多少种组合方案。打表
        for(int j=0; j<COIN; j++)  //从0开始，注意 dp[0][0]=1
            ans[i] += dp[i][j];
    while(cin >> s)
        cout << ans[s] << endl;
    return 0;
}
