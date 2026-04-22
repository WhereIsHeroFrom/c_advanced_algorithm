#include <stdio.h>

////////////////LIS模板////////////////
// a[i]  < g[mid] 时，求不降
// a[i] <= g[mid] 时，求递增
#define maxn 110
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

int max(int a, int b) {
    return a > b ? a : b;
}

void swap_array(int n, int a[]) {
    for(int i = 0; i < n/2; ++i) {
        int temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
}


int a[maxn];
int dppre[maxn], dppost[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    getLIS(n, a, dppre);
    swap_array(n, a);
    getLIS(n, a, dppost);
    swap_array(n, dppost);
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ans = max(ans, dppre[i] + dppost[i] - 1);
    }
    printf("%d\n", n - ans);
    return 0;
}