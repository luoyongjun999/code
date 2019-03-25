//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;
const int N = 300;
int sum[N], n;
int Minval() {
    int dp[N][N];
    for(int i=1; i <= n; i++)
        dp[i][i] = 0;
    for(int len=1; len < n; len++)       //len是i和j之间的距离
        for(int i=1; i <= n-len; i++) {  //从第i堆开始
            int j = i + len;               //到第j堆结束
            dp[i][j] = INF;
            for(int k=i; k<j; k++)         //i和j之间，用k进行分割
           dp[i][j]=min(dp[i][j],
                       dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
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
