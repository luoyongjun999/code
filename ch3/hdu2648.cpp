//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m, p;
    map<string, int> shop;
    while(cin>>n) {
        string s;
        for(int i=1; i<=n; i++) cin>>s; //输入商店名字。实际上用不着处理
        cin >> m;
        while(m--) {
            for(int i=1; i<=n; i++) {
                cin >> p >> s;
                shop[s] += p;               //用map可以直接操作商店，加上价格
            }
            int rank = 1;
            map<string,int>::iterator it;           //迭代器
            for(it=shop.begin(); it != shop.end(); it++)
                if((*it).second > shop["memory"])   //比较价格
						rank++;
            cout<<rank<<endl;
        }
        shop.clear();
    }
    return 0;
}
