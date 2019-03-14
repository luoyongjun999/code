//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1050;
int s[maxn];
int height[maxn];
void init_set(){
   for(int i = 1; i <= maxn; i++){
        s[i] = i;
        height[i]=0;                     //树的高度
   }
}

int find_set(int x){
    if(x != s[x]) s[x] = find_set(s[x]);   //路径压缩
    return s[x];
}
void union_set(int x, int y){         //优化合并操作
    x = find_set(x);
    y = find_set(y);
    if (height[x] == height[y]) {
        height[x] = height[x] + 1;      //合并，树的高度加一
        s[y] = x;
    }
    else{                            //把矮树并到高树上，高的树的高度不变
        if (height[x] < height[y])  s[x] = y;
        else   s[y] = x;
    }
}



int main (){
    int t, n, m, x, y;
    cin >> t;
    while(t--){
        cin >> n >> m;
        init_set();
        for(int i = 1; i <= m; i++){
            cin >> x >> y;
            union_set(x, y);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++)   //统计有多少个集
            if(s[i] == i)
                ans++;
        cout << ans <<endl;
    }
    return 0;
}
