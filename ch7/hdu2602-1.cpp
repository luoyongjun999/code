//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
struct BONE{
	int val;
int vol;
}bone[1011];
int T,N,V;
int dp[1011][1011];
int ans(){
    memset(dp,0,sizeof(dp));
    for(int i=1; i<=N; i++)
        for(int j=0; j<=V; j++){
     	  if(bone[i].vol > j)   //第i个物品太大，装不了
              dp[i][j] = dp[i-1][j];
           else                      //第i个物品可以装
	          dp[i][j]=max(dp[i-1][j],
			  		        dp[i-1][j-bone[i].vol]+bone[i].val);
}
    return dp[N][V];
}
int main(){
	cin>>T;
	while(T--){
		cin >> N >> V;
		for(int i=1;i<=N;i++)	cin>>bone[i].val;
		for(int i=1;i<=N;i++)	cin>>bone[i].vol;
		cout << ans() << endl;
	}
	return 0;
}
