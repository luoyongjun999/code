//ECUST luoyongjun
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

string s;
priority_queue <int, vector<int>, greater<int> > q;
//priority_queue <int> q;
int main()
{
	while(getline(cin, s) && s != "END"){
		int t = 1;
		sort(s.begin(), s.end());
		for(int i = 1; i < s.length(); i++){
			if(s[i] != s[i-1]){
				q.push(t);
				t = 1;
			}
			else t++;
		}
		q.push(t);

		if(q.size() == 1) {
			printf("%d %d 8.0\n", s.length()*8, s.length());
			q.pop();
			continue;
		}

		int ans = 0;
		while(q.size() > 1){
			int a = q.top(); q.pop();
			int b = q.top(); q.pop();
			q.push(a+b);
			ans += a+b;
		}
		q.pop();
		printf("%d %d %.1lf\n", s.length()*8, ans, (double)s.length()*8.0/(double)ans);
	}
}
