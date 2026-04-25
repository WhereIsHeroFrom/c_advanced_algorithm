#include <stdio.h>
#include <string.h>

//////////////////二分图最大匹配模板(邻接表) //////////////////
// 顶点范围  左边的点[1, n]，右边的点[1, m]

#define maxn 510
#define maxm 510

typedef struct {
    int graph[maxn][maxm];
    int deg[maxn];
    int pre[maxm];
    int visit[maxm];
    int n, m;
} Bipartite;

void Hungarian_Initialize(Bipartite *bp, int n, int m) {
    bp->n = n;
    bp->m = m;
    memset(bp->deg, 0, sizeof(bp->deg));
    memset(bp->pre, -1, sizeof(bp->pre));
}

void Hungarian_AddEdge(Bipartite *bp, int u, int v) {
    bp->graph[u][bp->deg[u]++] = v;
}

int hungarian_findMatch(Bipartite *bp, int u) {
    for (int i = 0; i < bp->deg[u]; i++) {
        int v = bp->graph[u][i];
        if (!bp->visit[v]) {
            bp->visit[v] = 1;
            if (bp->pre[v] == -1 || hungarian_findMatch(bp, bp->pre[v])) {
                bp->pre[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int Hungarian_GetMaxMatch(Bipartite *bp) {
    int res = 0;
    for (int u = 1; u <= bp->n; u++) {
        memset(bp->visit, 0, sizeof(bp->visit));
        if (hungarian_findMatch(bp, u)) {
            res++;
        }
    }
    return res;
}

//////////////////二分图最大匹配模板(邻接表) //////////////////


int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Bipartite bp;
    Hungarian_Initialize(&bp, n, m);
    for(int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        Hungarian_AddEdge(&bp, x, y);
    }
    printf("%d\n", Hungarian_GetMaxMatch(&bp));
    return 0;
}