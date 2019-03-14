//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int K,n;
const ll mod = 1000000007;
ll dp[2][55][55][55];
ll ten[55],tot[55],tot_2[55][55];
string str;
int main(){
    int T;
    int cas = 1;
    cin>>T;
    ten[0] = ten[1] = 1;
    for (int i = 2; i <= 50; i++)
         ten[i] = ten[i - 1] * 10 % mod;
    while (T--) {
        cin>>K>>str;
        n = str.size();
        int now = 0;
        for (int i = 0; i < n; i++)
        if (str[i] == '*') {
            for (int j = 0; j < n; j++)
                for (int k = j + 1; k < n; k++)
                if (str[j] == '*' || str[k] == '*')
                    dp[now][i][j][k] = 0;
                else
                    dp[now][i][j][k] = (str[j] - '0') * (str[k] - '0');
        }
        else {
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    dp[now][i][j][k] = 0;
        }
        ll lamb;
        if (n <= 3) lamb = 1;
        else lamb = (n - 3) * (n - 4) / 2 + 1;
        for (int iter = 0; iter < K; iter++) {
            now = 1 - now;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        dp[now][i][j][k] = 0;
            for (int j = 0; j < n; j++)
                for (int k = j + 1; k < n; k++) {
                    tot_2[j][k] = 0;
                    for (int i = 0; i < n; i++)
                    if (i != j && i != k)
                        tot_2[j][k] += dp[1 - now][i][j][k];
                    tot_2[j][k] %= mod;
                }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                if (i != j) {
                    tot[j] = 0;
                    for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        tot[j] += dp[1 - now][i][min(j,k)][max(j,k)];
                    tot[j] %= mod;
                }
                for (int j = 0; j < n; j++)
                    for (int k = j + 1; k < n; k++)
                    if (j != i && k != i) {
                       dp[now][i][j][k]+= dp[1 - now][i][j][k] * lamb;
                       dp[now][i][j][k]+=tot[j]-dp[1-now][i][j][k]+mod;
                       dp[now][i][j][k]+=tot[k]-dp[1-now][i][j][k]+mod;
		             dp[now][i][j][k]+=tot_2[j][k]-dp[1-now][i][j][k]+mod;
				   dp[now][i][j][k]+=dp[1-now][j][min(i,k)][max(i,k)]
									+dp[1-now][k][min(i,j)][max(i,j)];
                    }
            }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++) {
                        dp[now][i][j][k] %= mod;
                    }
        }
        ll ans = 0;
        for (int i = 1; i < n - 1; i++)
            for (int j = 0; j < i; j++)
                for (int k = i + 1; k < n; k++)
                    ans+=dp[now][i][j][k]*ten[i-j]%mod*ten[n-k]%mod;
        printf("Case #%d: %lld\n", cas++, ans % mod);
    }
}
