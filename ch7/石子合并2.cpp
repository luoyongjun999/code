//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;
const int N = 300;
int sum[N], n;
int Minval() {     //平行四边形优化
    int dp[N][N], s[N][N];
    for(int i=1; i <= n; i++){
        dp[i][i] = 0;
        s[i][i] = i;               //初始值
    }
    for(int len=1; len < n; len++)
        for(int i=1; i<= n-len; i++)  {
            int j = i + len;
            dp[i][j] = INF;
            for(int k = s[i][j-1]; k <= s[i+1][j]; k++)  //缩小范围
                if(dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]<dp[i][j]){
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    s[i][j] = k;      //记录[i, j]的最优分割点
                }
        }
    return dp[1][n];
}

int main() {
    while(cin>>n) {
        sum[0]=0;
        for(int i=1; i<= n; i++) {
int x;
            cin >> x;
            sum[i] = sum[i-1]+x;       //sum[i,j]的值等于 sum[j]-sum[i-1]
        }
        cout << Minval() << endl;
    }
    return 0;
}
