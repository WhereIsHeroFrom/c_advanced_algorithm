#include <stdio.h>
#include <string.h>

///////////////////////最近公共祖先(倍增算法)///////////////////////
#define maxn 500010
#define maxd 18
#define dummyroot 0

typedef struct {
    int f[maxn][maxd];   // f[i][j] 代表i号结点的第2^j个祖先
    int dep[maxn];       // dep[i] 代表i在这棵树上的深度

    int head[maxn];
    int edge[maxn * 2];
    int next[maxn * 2];
    int cnt;

    int q[maxn];
    int front, rear;
    int n;               // 树的总结点数
} LCA;


void addSingleEdge(LCA *lca, int u, int v) {
    lca->edge[lca->cnt] = v;
    lca->next[lca->cnt] = lca->head[u];
    lca->head[u] = lca->cnt++;
}

void LCA_Initialize(LCA *lca, int n) {
    lca->n = n;
    for (int i = 1; i <= n; ++i) {
        lca->head[i] = -1;
    }
    memset(lca->f, dummyroot, sizeof(lca->f));
    lca->cnt = 0;
}

void LCA_AddEdge(LCA *lca, int u, int v) {
    addSingleEdge(lca, u, v);
    addSingleEdge(lca, v, u);
}

void LCA_PreProcess(LCA *lca, int root) {
    lca->front = lca->rear = 0;
    lca->f[root][0] = dummyroot;
    lca->dep[root] = 0;
    lca->q[lca->rear++] = root;

    while (lca->front < lca->rear) {
        int u = lca->q[lca->front++];
        for (int i = 1; i < maxd; ++i) {
            lca->f[u][i] = lca->f[lca->f[u][i-1]][i-1];
            if (lca->f[u][i] == dummyroot) break;
        }
        for (int i = lca->head[u]; i != -1; i = lca->next[i]) {
            int v = lca->edge[i];
            if (v == lca->f[u][0]) {
                continue;
            }
            lca->f[v][0] = u;
            lca->dep[v] = lca->dep[u] + 1;
            lca->q[lca->rear++] = v;
        }
    }
}

int LCA_Get(LCA *lca, int u, int v) {
    // 1、确保 u的深度 >= v的深度
    if (lca->dep[u] < lca->dep[v]) {
        return LCA_Get(lca, v, u); 
    }
    // 2、将 u 和 v 调整到同一深度
    for (int i = maxd - 1; i >= 0; --i) {
        if (lca->dep[u] - (1 << i) >= lca->dep[v]) {
            u = lca->f[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    // 3、让 u 和 v 同时往上进行倍增
    for (int i = maxd - 1; i >= 0; --i) {
        if (lca->f[u][i] != lca->f[v][i]) {
            u = lca->f[u][i];
            v = lca->f[v][i];
        }
    }
    return lca->f[u][0];
}
///////////////////////最近公共祖先(倍增算法)///////////////////////

LCA lca;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    LCA_Initialize(&lca, n);
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        LCA_AddEdge(&lca, x, y);
    }
    LCA_PreProcess(&lca, 1);
    while(q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", LCA_Get(&lca, x, y));
    }
    return 0;
}