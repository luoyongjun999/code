//ECUST luoyongjun
#include<iostream>
#include<cstring>
const int INF = 0x3f3f3f3f;
using namespace std;
int n,m;
int bit[12]={0,1,3,9,27,81,243,729,2187,6561,19683,59049};
                          //三进制每一位的权值，与二进制的0, 1, 2, 4, 8...对照
int tri[60000][11];
int dp[11][60000];
int map[11][11];                  //存图
void make_trb(){                  //初始化，求所有可能的路径
    for(int i=0;i<59050;++i){   //共3^10=59050种状态
       int t=i;
       for(int j=1; j<=10; ++j){tri[i][j]=t%3; t/=3;}
   }
}
int comp_dp(){
        int ans = INF;
        memset(dp, INF, sizeof(dp));
        for(int i=0;i<=n;i++)
            dp[i][bit[i]]=0;          //bit[i]是第i个城市。起点是任意的
        for(int i=0;i<bit[n+1];i++){
            int flag=1;                 //所有的城市都遍历过1次以上
            for(int j=1;j<=n;j++){    //选一个终点
                if(tri[i][j]== 0){     //判断终点位是否为0
                    flag=0;              //还没有经过所有点
                    continue;
                }
                if(i==j) continue;
                for(int k=1; k<=n; k++)                {
                    int l=i-bit[j];          //i状态的第j位置0
                    if(tri[i][k]==0) continue;
                    dp[j][i]=min(dp[j][i],dp[k][l]+map[k][j]);
                }
            }
            if(flag)                          //找最小费用
                for(int j=1; j<=n; j++)
                    ans = min(ans,dp[j][i]);
        }
        return ans;
}
int main(){
    make_trb();
    while(cin>>n>>m){
        memset(map,INF,sizeof(map));
        while(m--){
            int a,b,c;
            cin>>a>>b>>c;
            if(c<map[a][b])  map[a][b]=map[b][a]=c;
        }
        int ans = comp_dp();
        if(ans==INF) cout<<"-1"<<endl;
        else         cout<<ans<<endl;
    }
    return 0;
}
