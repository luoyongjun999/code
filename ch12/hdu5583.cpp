//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
#define square(x)  (x)*(x)
void solve() {
    	int i, j=1, k=1;
    	char s[N];
    	int n;
    	long long a[N]={0};
		long long maxsum, oldsum=0;
		scanf("%s", s + 1);
		n = strlen(s + 1);
   	for(i=2; i<=n; i++){   //把表示青蛙序列的”01”字符串改成数字，例如
			 //“000011001”改成数字4221，并存放在数组a[]中，处理起来更加便捷
        if(s[i]==s[i-1])
            j++;
        else {
           a[k]=j;
           k++;
           j=1;
        }
   	}
    	a[k]=j;
    	for(i=1; i<=k; i++){  //计算改变颜色前的合力。
        oldsum = oldsum + a[i]*a[i];
    	}
    	maxsum = oldsum;
		for(i=1; i<=k; i++){    //改变1只青蛙的颜色对合力的影响，
								 //只需要考虑以下2种情况
        if(a[i]==1)           //如果长度是1，说明这只青蛙是孤立的，
							     //改变它的颜色后，可以和左右合并，
							     //例如”00100”，合并成”00000”。
           maxsum = max(maxsum, oldsum+square(a[i-1]+a[i]+a[i+1])
-square(a[i-1])-square(a[i])-square(a[i+1]));
        if(a[i]>=2){  	 //如果长度大于等于2，可以分2次改变颜色：
				//(1)改变最左边的，与左边的邻居合并，例如”0110”，改成”0010”；
				//(2)改变最右边的，和右边的邻居合并，例如”0110”，改成”0100”。
				//如果长度大于等于3，改变中间的，只会减小合力，
				//所以不用考虑，例如”01110”，改成”01010”，合力变小。
          maxsum = max(maxsum, oldsum+square(a[i-1]+1)+square(a[i]-1)
-square(a[i-1])-square(a[i])); //给左边
          maxsum = max(maxsum, oldsum+square(a[i+1]+1)+square(a[i]-1)
-square(a[i+1])-square(a[i])); //给右边
        }
     }
		printf("%lld\n", maxsum);
}
int main() {
		int t;
		scanf("%d", &t);
		for(int i = 1; i <= t; ++ i) {
			printf("Case #%d: ", i);
			solve();
		}
		return 0;
}
