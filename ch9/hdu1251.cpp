//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
int trie[1000010][26];    //数组定义字典树，存储下一个字符的位置
int num[1000010]={0};     //以某一字符串为前缀的单词的数量
int pos = 1;

void Insert(char str[]){    //在字典树中插入某个单词
    int c = 0;
    for(int i=0;str[i];i++){
        int n = str[i]-'a';
        if(trie[c][n]==0)    //如果对应字符还没有值
            trie[c][n] = pos++;
        c = trie[c][n];
        num[c]++;
    }
}
int Find(char str[]){    //返回以某个字符串为前缀的单词的数量
    int c = 0;
    for(int i=0;str[i];i++){
        int n = str[i]-'a';
        if(trie[c][n]==0)
            return 0;
        c = trie[c][n];
    }
    return num[c];
}

int main(){
    char str[11];
    while(gets(str)){
        if ( !strlen(str) )  break;  //输入了一个空行
        Insert(str);
    }
    while( gets(str))  cout << Find(str) << endl;
    return 0;
}
int main1(){
    char str[11];
    while(gets(str)){
        if ( !strlen(str) )  break;  //输入了一个空行
        Insert(str);
    }
    while( gets(str))  printf("%d\n",Find(str));
    return 0;
}
