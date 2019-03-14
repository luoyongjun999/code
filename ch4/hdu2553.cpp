//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int n, tot = 0;
int col[12] = {0};
bool check(int c, int r) {              //检查是否和已经放好的皇后冲突
    for(int i = 0; i < r; i++)
        if(col[i] == c || (abs(col[i]-c) == abs(i -r))) //取绝对值
            return false;
    return true;
}
void  DFS(int r) {                   //一行一行地放皇后，这一次是第r行
    if(r == n) {             //所有皇后都放好了，递归返回
       tot++;                  //统计合法的棋局个数
       return;
    }
    for(int c = 0; c < n; c++)      //在每一列放皇后
        if(check(c, r)){              //检查是否合法
            col[r] = c;                //在第r行的c列放皇后
            DFS(r+1);                   //继续放下一行皇后
        }
}
int main() {
    int ans[12]={0};
    for(n = 0; n <= 10; n++){      //算出所有n皇后的答案。先打表不然会超时
        memset(col,0,sizeof(col)); //清空，准备计算下一个N皇后问题
        tot = 0;
        DFS(0);
        ans[n] = tot;                //打表
    }
    while(cin >> n) {
        if(n==0)
           return 0;
        cout << ans[n] << endl;
    }
    return 0;
}
