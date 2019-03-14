//ECUST luoyongjun
#include<bits/stdc++.h>
using namespace std;
char room[23][23];
int dir[4][2] = {
    {-1,0},  //向左。左上角坐标是(0, 0)
    {0,-1},  //向上
    {1,0},   //向右
    {0,1}    //向下
};
int Wx, Hy, num;                 //Wx行，Hy列。用num统计可走的位置有多少
#define CHECK(x, y) (x<Wx && x>=0 && y >=0 && y<Hy) //是否在room里
struct node {int x,y;};
void BFS(int dx,int dy){
    num=1;                         //起点也包含在砖块内
    queue <node> q;              //队列中放坐标点
    node start, next;
    start.x = dx;
    start.y = dy;
    q.push(start);
    while(!q.empty()) {
        start = q.front();
        q.pop();
//cout<<"out"<<start.x<<start.y<<endl;    //打印出队列情况，进行验证
        for(int i=0; i<4; i++) { //按左、上、右、下，4个方向顺时针逐一搜索
            next.x = start.x + dir[i][0];
            next.y = start.y + dir[i][1];
            if(CHECK(next.x,next.y) && room[next.x][next.y]=='.') {
                room[next.x][next.y]='#';           //进队之后，标记为已经处理过
                num++;
                q.push(next);
            }
        }
    }
}
int main(){
    int x, y, dx, dy;
    while (cin >> Wx >> Hy) {   	          //Wx行，Hy列
        if (Wx==0 && Hy==0)   			 //结束
            break;
        for (y = 0; y < Hy; y++) {         //有Hy列
            for (x = 0; x < Wx; x++) { 	 //一次读入一行
                cin >> room[x][y];
                if(room[x][y] == '@') {     //读入起点
                    dx = x;
                    dy = y;
                }
            }
        }
        num = 0;
        BFS(dx, dy);
        cout << num << endl;
    }
    return 0;
}
