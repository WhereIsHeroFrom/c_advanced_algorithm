///////////////////////////////////////////////////
/////////////////////区间DP模板/////////////////////
///////////////////////////////////////////////////

#include <stdio.h>

#define maxn 210 
#define type int

int n;
type dp[maxn][maxn];
type a[maxn], mul[maxn][maxn];

type max(type a, type b) {
    return a > b ? a : b;
}

// min、max、sum
type IntervalDP_Opt(type a, type b) {
    return max(a, b);
}

// 非法状态值
type IntervalDP_ValueInf() {
    return  0;
}

// 初始状态值
type IntervalDP_ValueInit() {
    return 0;
}

// 计算区间 [l, r] 的值
type IntervalDP_CalcState(int l, int r) {
    type ans = IntervalDP_ValueInf();
    for(int k = l; k < r; ++k) {
        // dp[l][k] ... dp[k+1][r]
        int a_val = mul[l][k];
        int b_val = mul[k+1][r];
        int v = dp[l][k] + dp[k+1][r] + a_val*b_val/10;
        ans = IntervalDP_Opt(ans, v);
    }
    return ans;
}

// 固定模板，一般情况不需要修改
type IntervalDP_Solve(int maxlen, int maxr) {
    type ans = IntervalDP_ValueInf();
    // 1、枚举区间长度
    for(int i = 1; i <= maxlen; ++i) {
        // 2、枚举区间起点
        for(int j = 1; j+i-1 <= maxr; ++j) {
            int l = j;
            int r = j+i-1;
            if(i == 1) {
                dp[l][r] = IntervalDP_ValueInit();
            }else {
                dp[l][r] = IntervalDP_CalcState(l, r);
            }
            if(i == maxlen) {
                ans = IntervalDP_Opt(ans, dp[l][r]);
            }
        }
    }
    return ans;
}

///////////////////////////////////////////////////
/////////////////////区间DP模板/////////////////////
///////////////////////////////////////////////////

int main() {
    scanf("%d", &n);
    int n2 = n*2;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        a[n+i] = a[i];
    }
    for(int i = 1; i <= n2; ++i) {
        mul[i][i-1] = 1;
        for(int j = i; j <= n2; ++j) {
            mul[i][j] = mul[i][j-1] * a[j] % 10;
        }
    }
    printf("%d\n", IntervalDP_Solve(n, n2));
    return 0;
}