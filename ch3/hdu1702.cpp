//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,n,temp;
    cin>>t;
    while(t--){
        string str,str1;
        queue<int>Q;
        stack<int>S;
        cin>>n>>str;
        for(int i=0; i<n; i++){
            if(str=="FIFO"){                  //¶ÓÁÐ
                cin>>str1;
                if(str1=="IN"){
                    cin>>temp;  Q.push(temp);
                }
                if(str1=="OUT"){
                    if(Q.empty()) cout<<"None"<<endl;
                    else{
                        cout<<Q.front()<<endl;
                        Q.pop();
                    }
                }
            }
            else{                                //Õ»
                cin>>str1;
                if(str1=="IN"){
                    cin>>temp;  S.push(temp);
                }
                if(str1=="OUT"){
                    if(S.empty()) cout<<"None"<<endl;
                    else {
                        cout<<S.top()<<endl;
                        S.pop();
                    }
                }
            }
        }
    }
    return 0;
}
