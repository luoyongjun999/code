//ECUST luoyongjun
#include <bits/stdc++.h>
using namespace std;
const int N = 1100;
int a[N], b[N], c[N], ta[N], tb[N], tc[N], n, d[N], add[N], del[N];
bool check() {
	int tot = 0;
	for(int i = 1; i <= n; ++ i) {
		d[i] = a[i] + b[i] - c[i];
		add[i] = a[i] * ta[i] + b[i] * tb[i];
		del[i] = c[i] * tc[i];
		tot += abs(d[i]);
	}
	for(int i = 1; i <= n; ++ i) {
		if((d[i] > 0 && d[i] > add[i] - del[i]) ||
                   (d[i] < 0 && - d[i] > del[i] - add[i]))
			return 0;
		if((d[i] >= 0 && d[i] < add[i] - del[i]) ||
                   (d[i] <= 0 && - d[i] < del[i] - add[i])) {
			if(tot - abs(d[i]) > abs(d[i]))
				return 0;
		}
	}
	return 1;
}
void solve(int cas) {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) scanf("%d", a + i);
	for(int i = 1; i <= n; ++ i) scanf("%d", ta + i);
	for(int i = 1; i <= n; ++ i) scanf("%d", b + i);
	for(int i = 1; i <= n; ++ i) scanf("%d", tb + i);
	for(int i = 1; i <= n; ++ i) scanf("%d", c + i);
	for(int i = 1; i <= n; ++ i) scanf("%d", tc + i);
	int win = 1;
	for(int i = 1; i <= n; ++ i) {
		if(a[i] + b[i] != c[i]) {
			win = 0;
			break;
		}
	}
	if(win){ puts("Tweek"); return;	}
	for(int i = 1; i <= n; ++i){
		if(ta[i] && a[i] > 0){
			a[i] --;
			if(check()){ puts("Tweek");	return;	}
			a[i] ++;
		}
		if(tb[i] && b[i] > 0) {
			b[i] --;
			if(check()){ puts("Tweek");return;}
			b[i] ++;
		}
		if(tc[i] && c[i] > 0) {
			c[i] --;
			if(check()){ puts("Tweek");	return;}
			c[i] ++;
		}
	}
	puts("Craig");
	return;
}
int main(){
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++ i) {
		printf("Case #%d: ", i);
		solve(i);
	}
	return 0;
}
