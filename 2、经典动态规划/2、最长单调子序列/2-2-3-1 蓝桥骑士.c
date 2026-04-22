#include <stdio.h>

////////////////LIS模板////////////////
// a[i]  < g[mid] 时，求不降
// a[i] <= g[mid] 时，求递增
#define maxn 300010
int getLIS(int n, int a[], int dp[]) {
    // g[i] 代表长度为 i 的
    // 最长单调子序列的最后一个数是什么
    int g[maxn], gSize = 0;
    for(int i = 0; i < n; ++i) {
        // g[] = {1, 4, 5, 7, 8}   
        int l = -1, r = gSize;
        while(l + 1 < r) {
            int mid = (l + r) >> 1;
            if( a[i] <= g[mid] ) {
                r = mid;
            }else {
                l = mid;
            }
        }
        // l + 1 == r
        if(r == gSize) {
            g[gSize++] = a[i];
        }else {
            g[r] = a[i];
        }
        dp[i] = gSize;
    }
    return gSize;
}
////////////////LIS模板////////////////


int a[maxn];
int dp[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", getLIS(n, a, dp));
    return 0;
}