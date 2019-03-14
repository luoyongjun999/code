//ECUST   luoyongjun
#include<bits/stdc++.h>
const int LEN = 362888;       //状态共9!=362880种
using namespace std;
struct node{
    int state[9];       //记录一个八数码的排列，即一个状态
    int dis;             //记录到起点的距离
};

int dir[4][2] = {{-1,0}, {0,-1},{1,0},{0,1}};
           //左、上、右、下顺时针方向。左上角坐标是(0,0)
int visited[LEN]={0};  //与每个状态对应的记录，Cantor函数对它置数，并判重
int start[9];            //开始状态
int goal[9];             //目标状态
long int factory[] = {1,1,2,6,24,120,720,5040,40320,362880};
                             //Cantor用到的常数
bool Cantor(int str[], int n) {     //用康托展开判重
    long result = 0;
    for(int i = 0; i < n; i++) {
        int counted = 0;
        for(int j = i+1; j < n; j++) {
            if(str[i] > str[j])       //当前未出现的元素中是排在第几个
                ++counted;
        }
        result += counted*factory[n-i-1];
    }
    if(!visited[result]) {            //没有被访问过
        visited[result] = 1;
        return 1;
    }
    else
        return 0;
}
int bfs() {
    node head;
    memcpy(head.state, start, sizeof(head.state));  //复制起点的状态
    head.dis = 0;
    queue <node> q;          //队列中放状态
    Cantor(head.state, 9);  //用康托展开判重，目的是对起点的visited[]赋初值
    q.push(head);             //第一个进队列的是起点状态

    while(!q.empty()) {              //处理队列
        head = q.front();
        q.pop();                       //可在此处打印head.state，看弹出队列的情况
        int z;
        for(z = 0; z < 9; z++)        //找这个状态中元素0的位置
            if(head.state[z] == 0)    //找到了
                break;
            //转化为二维，左上角是原点(0, 0)。
        int x = z%3;          //横坐标
        int y = z/3;          //纵坐标
        for(int i = 0; i < 4; i++){   //上、下、左、右最多可能有4个新状态
            int newx = x+dir[i][0];    //元素0转移后的新坐标
            int newy = y+dir[i][1];
            int nz = newx + 3*newy;    //转化为一维
            if(newx>=0 && newx<3 && newy>=0 && newy<3) {//未越界
                node newnode;
                memcpy(&newnode,&head,sizeof(struct node));//复制这新的状态
                swap(newnode.state[z], newnode.state[nz]);//把0移动到新的位置
                newnode.dis ++;
                if(memcmp(newnode.state,goal,sizeof(goal)) == 0)
                                                           //与目标状态对比
                    return newnode.dis;             //到达目标状态，返回距离，结束
                if(Cantor(newnode.state, 9))         //用康托展开判重
                    q.push(newnode);                   //把新的状态放进队列
             }
        }
    }
    return -1;            //没找到
}
int main(){
    for(int i = 0; i < 9; i++)  cin >> start[i];       //初始状态
    for(int i = 0; i < 9; i++)  cin >> goal[i];        //目标状态
    int num = bfs();
    if(num != -1)  cout << num << endl;
    else          cout << "Impossible" << endl;
    return 0;
}
