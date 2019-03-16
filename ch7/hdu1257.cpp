//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000;
int n,high[MAXN];
int LIS(){
    int ans = 1;
int dp[MAXN];
    dp[1] = 1;
    for(int i = 2; i <= n; i++){
        int max = 0;
        for(int j=1; j<i; j++)
            if(dp[j] > max  &&  high[j] < high[i])
                max = dp[j];
        dp[i] = max+1;
        if(dp[i] > ans) ans = dp[i];
    }
    return ans;
}
int main(){
    while(cin >> n){
        for(int i=1; i<=n; i++)
            cin >> high[i];            //输入炮弹高度值
        cout << LIS() << endl;
    }
    return 0;
}
