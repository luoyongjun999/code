//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
int id[5000000+5];
struct Node{
    int size;          //以这个结点为根的子树的结点总数量，用于名次树
    int rank;          //优先级
    int key;           //键值
    Node *son[2];     //son[0]左儿子, son[1]右儿子
    bool operator < (const Node &a)const{return rank < a.rank;}
    int cmp(int x)const{
        if(x==key) return -1;
        return x<key?0:1;
    }
    void update(){     //更新size
        size=1;
        if(son[0]!=NULL) size+= son[0]->size;
        if(son[1]!=NULL) size+= son[1]->size;
        }
};
void rotate(Node* &o,int d){    //d=0左旋转，d=1右旋
        Node *k=o->son[d^1];      //d^1与1-d等价，但是更快
        o->son[d^1]=k->son[d];
        k->son[d]=o;
        o->update();
        k->update();
        o=k;
    }
void insert(Node* &o,int x){   //把x插入到树中
        if(o==NULL){
            o=new Node();
            o->son[0]=o->son[1]=NULL;
            o->rank=rand();
            o->key=x;
            o->size=1;
        }
        else {
            int d=o->cmp(x);
            insert(o->son[d],x);
            o->update();
            if(o<o->son[d])
                rotate(o,d^1);
        }
    }
int kth(Node* o,int k){   //返回第k大的数
        if(o==NULL||k<=0||k>o->size)
            return -1;
        int s=o->son[1]==NULL?0:o->son[1]->size;
        if(k==s+1) return o->key;
        else if(k<=s) return kth(o->son[1],k);
        else return kth(o->son[0],k-s-1);
    }
int find(Node* o,int k){  //返回元素k的名次
        if(o==NULL)
            return -1;
        int d=o->cmp(k);
        if(d==-1 )
            return o->son[1] ==NULL? 1: o->son[1]->size+1;
        else if(d==1) return find(o->son[d],k);
        else{
            int tmp=find(o->son[d],k);
            if(tmp==-1) return -1;
            else
                return o->son[1] ==NULL? tmp+1 : tmp+1+o->son[1]->size;
        }
    }
int main(){
    int n;
    while(~scanf("%d",&n)&&n){
        srand(time(NULL));
        int k,g;
        scanf("%d%d",&k,&g);
        Node *root=new Node();
        root->son[0]=root->son[1]=NULL;
        root->rank=rand(); root->key=g; root->size=1;
        id[g]=k;
        printf("%d %d\n",k,1);
        for(int i=2;i<=n;i++){
            scanf("%d%d",&k,&g);
            id[g]=k;
            insert(root,g);
            int t=find(root,g);   //返回新和尚的名次
            int ans1,ans2,ans;
            ans1=kth(root,t-1);   //前一名的老和尚
            ans2=kth(root,t+1);   //后一名的老和尚
            if(ans1!=-1&&ans2!=-1)
                ans= ans1-g >= g-ans2 ? ans2:ans1;
            else if(ans1==-1) ans=ans2;
            else ans=ans1;
            printf("%d %d\n",k,id[ans]);
        }
    }
    return 0;
}
