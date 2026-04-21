#include <stdio.h>

///////////////////最大子数组和模板///////////////////
#define maxn 200010
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

type dp[maxn];
type a[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    printf("%lld\n", getMSS(n, a, dp));
    return 0;
}