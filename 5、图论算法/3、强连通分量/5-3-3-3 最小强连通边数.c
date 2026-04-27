#include <stdio.h>
#include <stdlib.h>

//////////////////强连通分量(tarjan算法)//////////////////
#define maxn 100010
#define maxm 100010

typedef struct {
    int head[maxn];   // 头结点数组
    int edge[maxm];   // 存储边的终点
    int next[maxm];   // 存储下一条边的索引
    int cnt;          // 边的计数器

    int dfn[maxn];    // 代表结点的dfs访问时间戳
    int low[maxn];    // 代表结点能够追溯到的最早时间戳
    int inStack[maxn];// 标记当前结点是否在栈中
    int sccId[maxn];  // 每个节点所属的强连通分量编号
    int stack[maxn];  // 递归时记录当前访问的结点
    int top;          // 栈顶指针
    int timeStamp;    // 全局时间戳
    int sccCount;     // 代表强连通分量的总数

    int sccMin[maxn]; // 每个强连通分量的最小节点编号
    int sccSize[maxn];// 每个强连通分量的结点数
    int n;            // 图的总结点数
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
    memset(tj->sccId, 0, sizeof(tj->sccId));
    memset(tj->sccSize, 0, sizeof(tj->sccSize));
}

void Tarjan_AddEdge(Tarjan *tj, int u, int v) {
    tj->edge[ tj->cnt ] = v;
    tj->next[ tj->cnt ] = tj->head[u];
    tj->head[u] = tj->cnt++;
}

void tarjan_dfs(Tarjan *tj, int u) {
    tj->dfn[u] = tj->low[u] = ++tj->timeStamp;
    tj->stack[  tj->top++ ] = u;
    tj->inStack[u] = 1;

    for (int i = tj->head[u]; i != -1; i = tj->next[i]) {
        int v = tj->edge[i];
        // (u, v) 是一条有向边
        if( tj->dfn[v] == 0) {
            tarjan_dfs(tj, v);
            tj->low[u] = min(tj->low[u], tj->low[v]);
        }else if (tj->inStack[v]) {
            tj->low[u] = min(tj->low[u], tj->dfn[v]);
        }
    }

    if(tj->dfn[u] == tj->low[u]) {
        int v;
        int minval = u;
        do {
            v = tj->stack[--tj->top];
            tj->inStack[v] = 0;
            tj->sccId[v] = tj->sccCount;
            tj->sccSize[tj->sccCount]++;
            minval = min(minval, v);
        }while (v != u);
        tj->sccMin[tj->sccCount] = minval;
        tj->sccCount ++;
    }
}

void Tarjan_Solve(Tarjan *tj) {
    for(int i = 1; i <= tj->n; ++i) {
        if(!tj->dfn[i]) {
            tarjan_dfs(tj, i);
        }
    }
}
//////////////////强连通分量(tarjan算法)//////////////////


///////////////////强连通分量(缩图算法)////////////////////

typedef struct {
    int head[maxn];
    int edge[maxm];
    int next[maxm];
    int cnt;

    int inDeg[maxn];
    int outDeg[maxn];
} DAG;

void DAG_Initialize(DAG *dag) {
    memset(dag->head, -1, sizeof(dag->head));
    memset(dag->inDeg, 0, sizeof(dag->inDeg));
    memset(dag->outDeg, 0, sizeof(dag->outDeg));
    dag->cnt = 0;
}

void DAG_AddEdge(DAG* dag, int u, int v) {
    dag->edge[ dag->cnt ] = v;
    dag->next[ dag->cnt ] = dag->head[u];
    dag->head[u] = dag->cnt++;
}

void DAG_Build(Tarjan *tj, DAG* dag) {
    int n = tj->n;
    int sccCnt = tj->sccCount;
    DAG_Initialize(dag);

    static int vis[maxn];
    memset(vis, -1, sizeof(vis));

    for(int u = 1; u <= n; ++u) {
        for(int i = tj->head[u]; i != -1; i = tj->next[i]) {
            int v = tj->edge[i];
            int su = tj->sccId[u];
            int sv = tj->sccId[v];
            if(su == sv) continue;
            if(vis[sv] == su) continue;
            vis[sv] = su;
            DAG_AddEdge(dag, su, sv);
            dag->outDeg[su]++;
            dag->inDeg[sv]++;
        }
    }
}

///////////////////强连通分量(缩图算法)////////////////////

int getMinEdges(DAG *dag, int sccCnt) {
    if(sccCnt == 1) {
        return 0;
    }
    int in0 = 0, out0 = 0;
    for(int i = 0; i < sccCnt; ++i) {
        if (dag->inDeg[i] == 0) in0++;
        if(dag->outDeg[i] == 0) out0++;
    }
    return (in0 > out0) ? in0 : out0;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        Tarjan tj;
        DAG dag;
        Tarjan_Initialize(&tj, n);
        for(int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            Tarjan_AddEdge(&tj, u, v);
        }
        Tarjan_Solve(&tj);
        DAG_Build(&tj, &dag);

        printf("%d\n", getMinEdges(&dag, tj.sccCount));
    }
    return 0;
}