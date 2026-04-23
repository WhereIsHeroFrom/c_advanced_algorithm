#include <stdio.h>

////////////////////////////////////////////多重背包模板////////////////////////////////////////////
#define maxn 101
#define maxc 10
#define maxv 201
#define inf -1
#define init 0
#define vType int

vType opt(vType a, vType b) {
    if(a == inf) return b;
    if(b == inf) return a;
    return a > b ? a : b;
}

void Knapsack01(int n, int V, int w[maxn*maxc], vType v[maxn*maxc], vType dp[maxv]) {
    // 1、初始化
    for(int i = 1; i <= V; ++i) {
        dp[i] = inf;
    }
    dp[0] = init;
    // 2、状态转移
    for(int i = 1; i <= n; ++i) {
        for(int j = V; j >= w[i]; --j) {
            dp[j] = opt(dp[j], dp[j-w[i]] + v[i]);
        }
    }
}

void KnapsackMultiple(int n, int V, int w[maxn], vType v[maxn], int c[maxn], vType dp[maxv]) {
    int m = 0;  // 拆分以后，物品数量就是 m 了，不再是 n
    int nw[maxn * maxc];
    vType nv[maxn * maxc];
    for(int i = 1; i <= n; ++i) {
        int k = 1;
        while(k < c[i]) {
            ++m;
            nw[m] = k*w[i];
            nv[m] = k*v[i];
            c[i] -= k;
            k *= 2;
        }
        if(c[i]) {
            ++m;
            nw[m] = c[i]*w[i];
            nv[m] = c[i]*v[i];
        }
    }
    Knapsack01(m, V, nw, nv, dp);
}
////////////////////////////////////////////多重背包模板////////////////////////////////////////////

int w[maxn], c[maxn];
vType v[maxn];
vType dp[maxv];

int main() {
    int n, V;
    scanf("%d %d", &n, &V);
    for(int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &w[i], &v[i], &c[i]);
    }
    KnapsackMultiple(n, V, w, v, c, dp);
    vType ret = 0;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[i]);
    }
    printf("%d\n", ret);
    return 0;
}