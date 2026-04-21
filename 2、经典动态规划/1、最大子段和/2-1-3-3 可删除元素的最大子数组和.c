#include <stdio.h>

#define maxn 100010
#define maxk 101
#define inf -1000000000

int max(int a, int b) {
    return a > b ? a : b;
}

int a[maxn];
int dp[maxn][maxk];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    dp[0][0] = 0;
    for(int j = 1; j <= k; ++j) {
        dp[0][j] = inf;
    }
    for(int i = 1; i <= n; ++i) {
        dp[i][0] = max(dp[i-1][0], 0) + a[i];
        for(int j = 1; j <= k; ++j) {
            // 当前这个元素 -     不删除           删除
            dp[i][j] = max(dp[i-1][j] + a[i], dp[i-1][j-1]);
        }
    }
    int ans = inf;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= k; ++j) {
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}