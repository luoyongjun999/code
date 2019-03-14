//ECUST luoyongjun
#include<iostream>
using namespace std;
const int MAXN=200;
int c1[MAXN+1],c2[MAXN+1];
void part()
{
    int i,j,k;
    for(i=0;i<=MAXN;i++)
    {   c1[i]=1;
        c2[i]=0;
    }
    for(k=2;k<=MAXN;k++)
    {
      for(i=0;i<=MAXN;i++)
        for(j=0;j+i<=MAXN;j+=k)
        {
            c2[i+j]+=c1[i];
        }
      for(i=0;i<=MAXN;i++)
      {
          c1[i]=c2[i];
          c2[i]=0;
      }
    }
}
int main()
{
    int n;
    part();
    while(cin>>n)
    {
        cout<<c1[n]<<endl;
    }
    return 0;
}
