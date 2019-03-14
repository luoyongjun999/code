//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int N = 10005;
struct node{
    char name[35];
    int price;
};
vector<node> List[N];                    //用于解决冲突
unsigned int BKDRHash(char *str)  {    //哈希函数
    unsigned int seed = 31,key = 0;
    while(*str)
        key = key*seed+(*str++);
    return key & 0x7fffffff;
}
int main(){
    int n, m, key, add, memory_price, rank, len;
    int p[N];
    char s[35];
    node t;
    while(cin>>n){
        for(int i=0; i<N; i++)
            List[i].clear();
        for(int i=0;i<n;i++){
            cin>>t.name;
            key = BKDRHash(t.name) % N;  //计算hash值，并求余
            List[key].push_back(t);    //hash值可能冲突，把冲突的哈希值都存起来
        }
        cin>>m;
        while(m--){
            rank = len = 0;
            for(int i=0; i<n; i++){
                cin>>add>>s;
                key = BKDRHash(s) % N;                   //计算hash值
                for(int j=0; j<List[key].size(); j++)    //处理冲突问题
                    if(strcmp(List[key][j].name, s)==0){
                        List[key][j].price += add;
                        if(strcmp(s,"memory") == 0)
                            memory_price = List[key][j].price;
                        else
                            p[len++] = List[key][j].price;
                        break;
                    }
            }
            for(int i=0; i<len; i++)
                if(memory_price < p[i])
                    rank++;
            cout<<rank+1<<endl;
        }
    }
    return 0;
}
