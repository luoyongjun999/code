//ECUST luoyongjun
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
const int V = 1100;
const int N = 1000;
const int P = 1000000007;
int rev[V], pt[V], C[V][V];
int Pow(int x, int y){
	int ret = 1;
	while(y){
		if(y & 1) ret =  (LL) ret * x % P;
		x = (LL) x * x % P;
		y /= 2;
	}
	return ret;
}
void init(){
	for(int i = 1; i <= N; ++i)
        rev[i] = Pow(i, P - 2);
	pt[0] = 1;
	for(int i = 1; i <= N; ++i)
        pt[i] = pt[i - 1] * 2 % P;
	memset(C, 0, sizeof(C));
	for(int i = 0; i <= N; ++i){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
}
struct Point{
	int x, y;
}p[V];
struct PNode{
	int x, y, rev;
}Node[V];
bool EQ(PNode x, PNode y){
    if(x.x == y.x && x.x == 0) return true;
    if(x.x * y.x < 0) return false;
    return x.x * y.y == x.y * y.x;
}
bool Nodecmp(PNode x, PNode y){
    if(x.x * y.x <= 0) return x.x > y.x;
	if(x.x * y.y != x.y * y.x){
		if(x.x >= 0) return x.x * y.y > x.y * y.x;
		else return x.x * y.y > x.y * y.x;
	}
	return x.rev < y.rev;
}
int _, n;
/*分为几部分: 1.五点及以上共线；  2.任意一、二、三、四个点；
		     3.四点以上共线+任意一点；4.三点以上共线+两侧各一点  */
int sol_line(int ln, int rn, int revn, int nown, int total){
	int ans = 0;
	for(int i = 4; i <= ln + rn; ++i)
        ans =(ans+(LL)C[ln+rn][i]*rev[i+1]%P)%P;
	for(int i = 3; i <= ln + rn; ++i)
		ans=(ans+(LL)C[ln+rn][i]*rev[i+1]%P*(n-ln-rn-1)%P)%P;
	int D = revn - nown;
	int A = revn - D - rn;
	int c = total - A - ln - rn;
	int CD = c + D;
	int AB = n - 1 - ln - rn - CD;
	for(int i = 2; i <= ln + rn; ++i)
		ans = (ans+(LL)C[ln+rn][i]*rev[i+1]%P*AB%P*CD%P)%P;
	return ans;
}
int mid_way[V];
int sol(){
	int ret = 0;
	for(int i = 1; i <= 4; ++i)
	ret = (ret + C[n][i]) % P;
	for(int i = 0; i < n; ++i){
		int revn = 0;
		for(int j = 0; j < n; ++j){
			Node[j].x = p[j].x - p[i].x;
			Node[j].y = p[j].y - p[i].y;
			if(Node[j].y < 0 || (Node[j].y == 0 && Node[j].x < 0)){
				Node[j].x = -Node[j].x;
				Node[j].y = -Node[j].y;
				Node[j].rev = 1;
				++revn;
			}
			else Node[j].rev = -1;
		}
		sort(Node, Node + n, Nodecmp);
		int ln = 0, rn = 0, midn = 0, nown = 0, total = 0, pre = -1;
		for(int j = 0; j < n; ++j){
			if(Node[j].x == 0 && Node[j].y == 0) continue;
			if(pre != -1 && !EQ(Node[j], Node[pre])){
				ret += sol_line(ln, rn, revn, nown, total);
				ret %= P;
				mid_way[midn++] = (LL) ln * rn % P;
				ln = rn = 0;
			}
			if(Node[j].rev == -1) ++ln;
			else ++nown, ++rn;
			++total;
			pre = j;
		}
		mid_way[midn++] = (LL) ln * rn % P;
		ret += sol_line(ln, rn, revn, nown, total);
		ret %= P;
		int mids = 0;
		for(int j = 0; j < midn; ++j) mids = (mids + mid_way[j]) % P;
		for(int j = 0; j < midn; ++j){
			ret = (ret-(LL)(mids-mid_way[j])*mid_way[j]%P*rev[2]%P)%P;
			if(ret < 0) ret += P;
		}
	}
	return ret;
}
int main(){
    init();
	scanf("%d", &_);
	for(int ca = 1; ca <= _; ++ca){
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].x, &p[i].y);
		printf("Case #%d: %d\n", ca, sol());
	}
	return 0;
}
