//ECUST luoyongjun
#include <cstdio>
#include <iostream>

using namespace std;

double dp[1005][1005];

int main()
{
    int n, s, ns;

    cin >> n >> s;
    ns = n*s;

    for (int i = n; i >= 0; i--)
        for (int j = s; j >= 0; j--)
        {
            if ( i == n && j == s )
                dp[n][s] = 0.0;
            else
                dp[i][j] = ( ns + (n-i)*j*dp[i+1][j] + i*(s-j)*dp[i][j+1] + (n-i)*(s-j)*dp[i+1][j+1] )/( ns - i*j );
        }
    printf("%.4lf\n", dp[0][0]);

    return 0;
}
