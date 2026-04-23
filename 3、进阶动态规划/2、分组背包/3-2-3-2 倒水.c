#include <stdio.h>

/*
1、非法状态值要设置非常小
2、必须用 long long
3、每组物品必须选择恰好一个
*/

////////////////////////////////////分组背包模板////////////////////////////////////
#define maxn 1010
#define maxc 3
#define maxv 1010
#define inf -1000000000000000000LL
#define init 0
#define vType long long

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
            // 前i组物品凑出容量为 j 的最优价值
            // dp[i][j] = dp[i-1][j];  代表第 i 组物品可以不选择
            // dp[i][j] = inf;         代表第 i 组物品必须恰好选择1个
            dp[i][j] = inf;
            for(int k = 0; k < items[i].cnt; ++k) {
                if(j >= items[i].w[k]) {
                    vType tmp = dp[i-1][j - items[i].w[k]] + items[i].v[k];
                    dp[i][j] = opt( dp[i][j], tmp );
                }
            }
        }
    }
}
////////////////////////////////////分组背包模板////////////////////////////////////

struct Item items[maxn];
vType dp[maxn][maxv];

int main() {
    int n, V;
    scanf("%d %d", &n, &V);
    for(int i = 1; i <= n; ++i) {
        int a, b, c, d, e;
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
        items[i].cnt = 3;

        items[i].w[0] = 0;
        items[i].v[0] = e;

        items[i].w[1] = a;
        items[i].v[1] = b;

        items[i].w[2] = c;
        items[i].v[2] = d;
    }
    KnapsackGroup(n, V, items, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[n][i]);
    }
    printf("%lld\n", ret);
    return 0;
}