//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int dp[1005][1005];
string str1, str2;
int LCS(){
    memset(dp, 0, sizeof(dp));
    for(int i=1; i<=str1.length(); i++)
        for(int j=1; j<=str2.length(); j++){
            if(str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    return dp[str1.length()][str2.length()];
}
int main(){
    while(cin >> str1 >> str2)
        cout<< LCS() << endl;
    return 0;
}
