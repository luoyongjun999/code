//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000+5;
char str[MAXN], pattern[MAXN];
int Next[MAXN];
int cnt;
int getFail(char *p, int plen){
                //预计算Next[]。用于失配的情况下，得到j回溯的位置
    Next[0]=0; Next[1]=0;
    for(int i=1; i < plen; i++){
        int j = Next[i];
        while(j && p[i] != p[j])   j = Next[j];
        Next[i+1] = (p[i]==p[j]) ? j+1 : 0;
    }
}
int kmp(char *s, char *p) {      //在s中找p
   int last = -1;
    int slen=strlen(s), plen=strlen(p);
    getFail(p, plen);              //预计算Next[]数组
    int j=0;
    for(int i=0; i<slen; i++) {  //匹配S和P的每个字符
        while(j && s[i]!=p[j])  j=Next[j];  //失配了，用Next[]找j的回溯位置
        if(s[i]==p[j])  j++;      //当前位置的字符匹配，继续
        if(j == plen) {           //完全匹配
           	//这个匹配，在S中的起点是i+1-plen，末尾是i。如有需要可以打印：
           	// printf("at location=%d, %s\n", i+1-plen,&s[i+1-plen]);
            //-------------------下面是与本题相关的工作
            if( i-last >= plen) {  //判断新的匹配和上一个匹配是否能分开
                cnt++;
                last=i;               //last指向上一次匹配的末尾位置
            }
            //-------------------
        }
    }
}
int main(){
    while(~scanf("%s", str)){      //读串
        if(str[0] == '#')  break;
        scanf("%s", pattern);      //读模式串
        cnt = 0;
        kmp(str, pattern);
        printf("%d\n", cnt);
    }
    return 0;
}
