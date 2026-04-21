#include <stdio.h>

#define maxn 110

int max(int a, int b) {
    return a > b ? a : b;
}

int a[maxn];

// 这个模板是用来求最长递增子序列的
// 如果要求单调不降，只需要把 a[i] <= g[mid] 改成 a[i] < g[mid]
int getLIS(int n, int a[], int dp[]) {
    // g[i] 代表长度为 i 的最长递增子序列的
    // 最后一个数是什么
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

void swap_array(int n, int a[]) {
    for(int i = 0; i < n/2; ++i) {
        int temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
}

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