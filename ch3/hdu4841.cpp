//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int main(){
    vector <int> table;                          //模拟圆桌
    int n, m;
    while(cin >> n >> m){
        table.clear();
        for(int i=0; i<2*n; i++)  table.push_back(i);  //初始化
        int pos = 0;                               //记录当前位置
        for(int i=0; i<n; i++){                  //赶走n个
            pos = (pos+m-1) % table.size();    //圆桌是个环，取余处理
            table.erase(table.begin() + pos); //赶走坏人，table人数减1
        }
        int j = 0;
        for(int i=0; i<2*n; i++){               //打印预先安排座位
            if(!(i%50) && i)  cout<<endl;       //50个字母一行
            if(j<table.size() && i==table[j]){ //table留下的都是好人
                j++;
                cout<<"G";
            }
            else
                cout<<"B";
        }
        cout<<endl<<endl;                          //留一个空行
    }
    return 0;
}
