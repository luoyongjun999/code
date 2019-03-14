//ECUST luoyongjun
#include <algorithm>
typedef long long LL;
int main(){
		int num, n, K, odd;
		scanf("%d", &num);
		for(int i = 1; i <= num; ++i){
			scanf("%d%d", &n, &K);
     	if(n % 2)
            	odd = 0; //n是奇数，每一层都是最左边的数
        	else {
		odd = 1; //n是偶数，转换为比它小1的奇数处理。最后一层取右边的数
            	n--;
        	}
        	LL pp=(LL)pow(2,K)-1;
//二进制数为全1的数。例如K=5时，pp=31，二进制是11111
	        	LL kk = pp-(pp-n)/2;  //kk的二进制表示，就是一个可行的路径。
								//其中为1的是'+'，为0的是'-'。原因见上文的证明。
        	LL pos = 0;   //当前层数，从国王的顶层开始。
			printf("Case #%d:\n", i);
  		while(kk > 1) 	{	 //不处理最后一层，最后一层有奇偶问题。
         	  if(kk & 1) 		 //二进制数的个位数是当前的层。
								 //这个位置是'1'，表示要加。
                printf("%lld %c\n", (LL)pow(2,pos), '+');
           else        //二进制数的个位数是'0'，表示要减
                printf("%lld %c\n", (LL)pow(2,pos), '-');
           kk = kk >> 1; //二进制数右移一次，把处理过的移走。
							 //新的个位数是下一层。
            pos++;
        }
//下面处理最后一层。如果n是偶数，最后一层取右边。
        if(kk & 1)
             printf("%lld %c\n", (LL)pow(2,pos)+odd, '+');
        else
             printf("%lld %c\n", (LL)pow(2,pos)+odd, '-');
		}
		return 0;
}
