//ECUST luoyongjun
//滚动数组
#include<bits/stdc++.h>
using namespace std;
struct BONE{
	int val;
int vol;
}bone[1011];
int T,N,V;

int dp[1011];                     //替换 int dp[1011][1011];
int ans(){
    memset(dp, 0, sizeof(dp));
    for(int i=1; i<=N; i++)
        for(int j=V; j>=bone[i].vol; j--)  //反过来循环
            dp[j] = max(dp[j],dp[j-bone[i].vol]+bone[i].val);
    return dp[V];
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
