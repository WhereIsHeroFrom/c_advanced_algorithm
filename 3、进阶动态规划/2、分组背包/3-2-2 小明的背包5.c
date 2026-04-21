#include <stdio.h>

#define maxn 110
#define maxc 110
#define maxv 110
#define inf -1
#define init 0
#define vType int

struct Item {
    int cnt;
    int w[maxc];
    vType v[maxc];
};

vType opt(vType a, vType b) {
    if(a == inf) return b;
    if(b == inf) return a;
    return a > b ? a : b;
}

void KnapsackGroup(int n, int V, struct Item items[], vType dp[maxn][maxv]) {
    for(int i = 1; i <= V; ++i) {
        dp[0][i] = inf;
    }
    dp[0][0] = init;

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= V; ++j) {
            // 前i组物品凑出容量为j的最优价值
            dp[i][j] = dp[i-1][j];
            for(int k = 0; k < items[i].cnt; ++k) {
                if(j >= items[i].w[k]) {
                    vType tmp = dp[i-1][j - items[i].w[k]] + items[i].v[k];
                    dp[i][j] = opt( dp[i][j], tmp );
                }
            }
        }
    }
}

struct Item items[maxn];
vType dp[maxn][maxv];

int main() {
    int n, V;
    scanf("%d %d", &n, &V);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &items[i].cnt);
        for(int j = 0; j < items[i].cnt; ++j) {
            scanf("%d %d", &items[i].w[j], &items[i].v[j]);
        }
    }
    KnapsackGroup(n, V, items, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[n][i]);
    }
    printf("%d\n", ret);
    return 0;
}