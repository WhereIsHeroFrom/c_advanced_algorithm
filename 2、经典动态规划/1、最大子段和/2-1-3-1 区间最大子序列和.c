#include <stdio.h>

///////////////////最大子数组和模板///////////////////
#define maxn 2010
#define type long long
#define inf -1000000000000000000LL

type max(type a, type b) {
    return a > b ? a : b;
}

type getMSS(int n, type a[], type dp[]) {
    // dp[i] 表示以第 i 个数结尾的最大子段和
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        dp[i] = a[i] + max(dp[i-1], (type)0);
    }
    // 转换成前 i 个元素的最大子段和
    dp[0] = inf;
    for(int i = 1; i <= n; ++i) {
        dp[i] = max(dp[i], dp[i-1]);
    }
    return dp[n];
}
///////////////////最大子数组和模板///////////////////

// dp[i][j] 代表从第i个元素
// 开始的数组的第j个元素结尾的最大子段和
type dp[maxn][maxn];
type a[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for(int i = 1; i <= n; ++i) {
        getMSS(n-i+1, &a[i-1], dp[i]);
    }
    int t;
    scanf("%d", &t);
    while(t--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%lld\n", dp[l][r - l + 1]);
    }
    return 0;
}