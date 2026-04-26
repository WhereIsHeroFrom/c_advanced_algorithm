#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////////////////////////强连通分量(tarjan模板)///////////////////////////////

#define MAXN 10010
#define MAXM 100010

typedef struct {
    int head[MAXN];     // 链式前向星：头节点数组
    int edge[MAXM];     // 链式前向星：存储边的终点
    int next[MAXM];     // 链式前向星：存储下一条边的索引
    int cnt;            // 链式前向星：边的计数器

    int dfn[MAXN];      // Tarjan：节点的DFS访问时间戳
    int low[MAXN];      // Tarjan：节点能追溯到的最早时间戳
    int inStack[MAXN];  // Tarjan：标记节点是否在栈中
    int sccId[MAXN];    // 每个节点所属的强连通分量编号
    int stack[MAXN];    // Tarjan：递归栈
    int top;            // 栈顶指针
    int timeStamp;      // 全局时间戳
    int sccCount;       // 强连通分量的总数

    int sccMin[MAXN];   // 每个强连通分量的最小节点编号
    int sccSize[MAXN]; // 每个强连通分量的节点数
    int n;              // 图的总节点数
} Tarjan;

int min(int a, int b) {
    return a < b ? a : b;
}

void Tarjan_Initialize(Tarjan *tj, int n) {
    tj->n = n;
    tj->cnt = 0;
    tj->top = 0;
    tj->timeStamp = 0;
    tj->sccCount = 0;

    memset(tj->head, -1, sizeof(tj->head));
    memset(tj->dfn, 0, sizeof(tj->dfn));
    memset(tj->low, 0, sizeof(tj->low));
    memset(tj->inStack, 0, sizeof(tj->inStack));
    memset(tj->sccId, 0, sizeof(tj->sccId));
    memset(tj->sccSize, 0, sizeof(tj->sccSize));
}

void Tarjan_AddEdge(Tarjan *tj, int u, int v) {
    tj->edge[tj->cnt] = v;
    tj->next[tj->cnt] = tj->head[u];
    tj->head[u] = tj->cnt++;
}

void tarjan_DFS(Tarjan *tj, int u) {
    tj->dfn[u] = tj->low[u] = ++tj->timeStamp;
    tj->stack[tj->top++] = u;
    tj->inStack[u] = 1;

    for (int i = tj->head[u]; i != -1; i = tj->next[i]) {
        int v = tj->edge[i];
        if (!tj->dfn[v]) {
            tarjan_DFS(tj, v);
            tj->low[u] = min(tj->low[u], tj->low[v]);
        } else if (tj->inStack[v]) {
            tj->low[u] = min(tj->low[u], tj->dfn[v]);
        }
    }

    if (tj->dfn[u] == tj->low[u]) {
        int v;
        int min_val = u;
        do {
            v = tj->stack[--tj->top];
            tj->inStack[v] = 0;
            tj->sccId[v] = tj->sccCount;
            tj->sccSize[tj->sccCount]++;
            if (v < min_val) min_val = v;
        } while (v != u);

        tj->sccMin[tj->sccCount] = min_val;
        tj->sccCount++;
    }
}

void Tarjan_Solve(Tarjan *tj) {
    for (int i = 1; i <= tj->n; ++i) {
        if (!tj->dfn[i]) {
            tarjan_DFS(tj, i);
        }
    }
}

int Tarjan_Compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
///////////////////////////////强连通分量(tarjan模板)///////////////////////////////


////////////////////////////////强连通分量(缩图模板)////////////////////////////////
typedef struct {
    int head[MAXN];
    int edge[MAXM];
    int next[MAXM];
    int cnt;

    int inDeg[MAXN];   // 入度
    int outDeg[MAXN];  // 出度
} DAG;

void DAG_Init(DAG *dag) {
    memset(dag->head, -1, sizeof(dag->head));
    memset(dag->inDeg, 0, sizeof(dag->inDeg));
    memset(dag->outDeg, 0, sizeof(dag->outDeg));
    dag->cnt = 0;
}

void DAG_AddEdge(DAG *dag, int u, int v) {
    dag->edge[dag->cnt] = v;
    dag->next[dag->cnt] = dag->head[u];
    dag->head[u] = dag->cnt++;
}

void DAG_Build(Tarjan *tj, DAG *dag) {
    int n = tj->n;
    int sccCnt = tj->sccCount;
    DAG_Init(dag);

    static int vis[MAXN];
    memset(vis, -1, sizeof(vis));

    for (int u = 1; u <= n; ++u) {
        for (int i = tj->head[u]; i != -1; i = tj->next[i]) {
            int v = tj->edge[i];
            int su = tj->sccId[u];
            int sv = tj->sccId[v];

            if (su == sv) continue;
            if (vis[sv] == su) continue;

            vis[sv] = su;
            DAG_AddEdge(dag, su, sv);
            dag->outDeg[su]++;
            dag->inDeg[sv]++;
        }
    }
}
////////////////////////////////强连通分量(缩图模板)////////////////////////////////



int getMinEdges(DAG *dag, int sccCnt) {
    if (sccCnt == 1) return 0;
    int in0 = 0, out0 = 0;
    for (int i = 0; i < sccCnt; ++i) {
        if (dag->inDeg[i] == 0) in0++;
        if (dag->outDeg[i] == 0) out0++;
    }
    return (in0 > out0) ? in0 : out0;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);

        Tarjan tj;
        DAG dag;

        Tarjan_Initialize(&tj, n);

        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            Tarjan_AddEdge(&tj, u, v);
        }

        Tarjan_Solve(&tj);
        DAG_Build(&tj, &dag);

        int ans = getMinEdges(&dag, tj.sccCount);
        printf("%d\n", ans);
    }
    return 0;
}