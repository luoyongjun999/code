//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
int main(){
		int n;
		char ch;
		scanf("%d",&n);  getchar();
		while(n--){
			stack<char> s;
			while(true){
				ch = getchar();                   //一次读入一个字符
            	if(ch==' '||ch=='\n'||ch==EOF){
					while(!s.empty()){
						printf("%c",s.top());  //输出栈顶
						s.pop();                  //清除栈顶
					}
					if(ch=='\n'||ch==EOF)  break;
					printf(" ");
				}
				else   s.push(ch);                //入栈
			}
			printf("\n");
		}
	return 0;
}
