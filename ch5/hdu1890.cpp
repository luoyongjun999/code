//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int maxn=100010;
int root;      //根
int rev[maxn],pre[maxn],size[maxn];
     //rev[i]，标记i被翻转；pre[i]，i的父结点；size[i]，i的子树上结点的个数
int tree[maxn][2]; //记录树：tree[i][0]，i的左儿子；tree[i][1]，i的右儿子
struct node{
    int val,id;
    bool operator<(const node &A)const {  //用于sort()排序
        if(val==A.val)return id<A.id;
        return val<A.val;
    }
}nodes[maxn];
void pushup(int x){  //计算以x为根的子树，包含多少子结点。
    size[x]=size[tree[x][0]]+size[tree[x][1]]+1;
}
void update_rev(int x){
    if(!x)return;
    swap(tree[x][0],tree[x][1]);   //翻转x：交换左右儿子
    rev[x]^=1;                         //标记x被翻转
}
void pushdown(int x){      //做splay时，根据本题的需要，处理机械臂翻转
    if(rev[x]){
        update_rev(tree[x][0]);
        update_rev(tree[x][1]);
        rev[x]=0;
    }
}
void Rotate(int x,int c){      //旋转，c=0左旋，c=1右旋
    int y=pre[x];
    pushdown(y);
    pushdown(x);
    tree[y][!c]=tree[x][c];
    pre[tree[x][c]]=y;
    if(pre[y])
        tree[pre[y]][tree[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    tree[x][c]=y;
    pre[y]=x;
    pushup(y);
}
void splay(int x,int goal){
           //把结点x旋转为goal的儿子，如果goal是0则旋转到根
    pushdown(x);
    while(pre[x]!=goal){        //一直旋转，直到x成为goal的儿子
        if(pre[pre[x]]==goal){  //情况(1)：x的父结点是根，单旋一次即可
            pushdown(pre[x]); pushdown(x);
            Rotate(x,tree[pre[x]][0]==x);
        }
        else{              //x的父结点不是根
            pushdown(pre[pre[x]]); pushdown(pre[x]); pushdown(x);
            int y=pre[x];
            int c=(tree[pre[y]][0]==y);
            if(tree[y][c]==x){   //情况(2)：x、x的父、x父的父，不共线
                Rotate(x,!c);
                Rotate(x,c);
            }
            else{                   //情况(3)：x、x的父、x父的父，共线
                Rotate(y,c);
                Rotate(x,c);
            }
        }
    }
    pushup(x);
    if(goal==0) root=x;  //如果goal是0，则将根结点更新为x
}
int get_max(int x){
    pushdown(x);
    while(tree[x][1]){
        x=tree[x][1];
        pushdown(x);
    }
    return x;
}
void del_root(){           //删除根结点
    if(tree[root][0]==0){
        root=tree[root][1];
        pre[root]=0;
    }
    else{
        int m=get_max(tree[root][0]);
        splay(m,root);
        tree[m][1]=tree[root][1];
        pre[tree[root][1]]=m;
        root=m;
        pre[root]=0;
        pushup(root);
    }
}
void newnode(int &x,int fa,int val){
    x=val;
    pre[x]=fa;
    size[x]=1;
    rev[x]=0;
    tree[x][0]=tree[x][1]=0;
}
void buildtree(int &x,int l,int r,int fa){   //建树
    if(l>r) return;
    int mid=(l+r)>>1;
    newnode(x,fa,mid);
    buildtree(tree[x][0],l,mid-1,x);
    buildtree(tree[x][1],mid+1,r,x);
    pushup(x);
}
void init(int n){
    root==0;
    tree[root][0]=tree[root][1]=pre[root]=size[root]=0;
    buildtree(root,1,n,0);
}
int main(){
    int n;
    while(~scanf("%d",&n) && n){
        init(n);
        for(int i=1;i<=n;i++){
            scanf("%d",&nodes[i].val);  nodes[i].id=i;
        }
        sort(nodes+1,nodes+n+1);
        for(int i=1;i<n;i++){
            splay(nodes[i].id,0);    //第i次翻转：把第i大的数旋到根
            update_rev(tree[root][0]);    //左子树需要翻转
            printf("%d ",i+size[tree[root][0]]);
              //i:第i次翻转；size:第i个被翻转的左边的个数，就是它左子树的个数
            del_root();   //删除第i次翻转的数，准备下一次翻转
        }
        printf("%d\n",n);
    }
    return 0;
}
