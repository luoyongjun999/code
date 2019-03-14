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
void DFS(int dx, int dy){
    room[dx][dy] = '#';                 //标记这个位置，表示已经走过
      // cout<<"walk:"<<dx<<dy<<endl; //在此处打印走过的位置，验证是否符合
    num++;
    for(int i = 0; i < 4; i++) {      //左、上、右、下，4个方向顺时针深搜
        int newx = dx + dir[i][0];
        int newy = dy + dir[i][1];
        if(CHECK(newx, newy) && room[newx][newy] == '.'){
             DFS(newx, newy);
             // cout<<"    back:"<<dx<<dy<<endl;
 //在此处打印回退的点的坐标，观察深搜到底后，回退的情况
//例如到达最后的15这个位置后，会一直退到起点
//即打印出14-11-10-9-8-7-6-5-4-3-2-1。这也是递归程序返回的过程
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
        DFS(dx, dy);
        cout << num << endl;
    }
    return 0;
}
