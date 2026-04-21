#include <stdio.h>

#define mod 1000000007
#define maxn 1010
char s[maxn][maxn];
int dp[maxn][maxn];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", s[i]);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(s[i][j] == '*') {
                dp[i][j] = 0;
            }else {
                if(i == 0 && j == 0) {
                    dp[i][j] = 1;
                }else if(i == 0) {   // 从左边过来
                    dp[i][j] = dp[i][j-1];
                }else if(j == 0) {   // 从上边过来
                    dp[i][j] = dp[i-1][j];
                }else {
                    dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % mod;
                }
            }
        }
    }
    printf("%d\n", dp[n-1][n-1]);
    return 0;
}