#include <stdio.h>
#include <string.h>

#define MAXN 10010

// 邻接表实现
int head[MAXN];
int edge[MAXN*10];
int next[MAXN*10];
int cnt;

// Tarjan 算法所需的数组
int dfn[MAXN];
int low[MAXN];
int inStack[MAXN];
int sccId[MAXN];
int stack[MAXN];
int top;
int timeStamp;
int sccCount;

// 存储每个强连通分量的节点
int sccNodes[MAXN][MAXN];
int sccSize[MAXN];

// 缩点后的图
int shrinkHead[MAXN];
int shrinkEdge[MAXN*10];
int shrinkNext[MAXN*10];
int shrinkCnt;
int ind[MAXN];
int outd[MAXN];
int hasEdge[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void init(int n) {
    for(int i = 1; i <= n; ++i) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        inStack[i] = 0;
        sccId[i] = 0;
    }
    for(int i = 0; i < MAXN; ++i) {
        sccSize[i] = 0;
        shrinkHead[i] = -1;
        ind[i] = 0;
        outd[i] = 0;
        for(int j = 0; j < MAXN; ++j) {
            hasEdge[i][j] = 0;
        }
    }
    cnt = 0;
    top = 0;
    timeStamp = 0;
    sccCount = 0;
    shrinkCnt = 0;
}

void addEdge(int u, int v) {
    edge[cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt++;
}

void tarjanDFS(int u) {
    dfn[u] = low[u] = ++timeStamp;
    stack[top++] = u;
    inStack[u] = 1;

    for(int i = head[u]; i != -1; i = next[i]) {
        int v = edge[i];
        if( !dfn[v] ) {
            tarjanDFS(v);
            low[u] = min(low[u], low[v]);
        }else if( inStack[v] ) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) {
        int v;
        do {
            v = stack[--top];
            inStack[v] = 0;
            sccId[v] = sccCount;
            sccNodes[sccCount][sccSize[sccCount]++] = v;
        }while(v != u);
        sccCount++;
    }
}

void solve(int n) {
    for(int i = 1; i <= n; ++i) {
        if( !dfn[i] ) {
            tarjanDFS(i);
        }
    }
}

void shrinkGraph(int n) {
    for(int i = 0; i < sccCount; ++i) {
        for(int j = 0; j < sccSize[i]; ++j) {
            int u = sccNodes[i][j];
            for(int k = head[u]; k != -1; k = next[k]) {
                int v = edge[k];
                int sccU = sccId[u];
                int sccV = sccId[v];
                if(sccU == sccV) continue;
                if(hasEdge[sccU][sccV]) continue;
                hasEdge[sccU][sccV] = 1;
                outd[sccU]++;
                ind[sccV]++;
            }
        }
    }
}

int calculateMinEdges() {
    int indCount = 0, outdCount = 0;
    for(int i = 0; i < sccCount; ++i) {
        if( !ind[i]) indCount++;
        if( !outd[i] ) outdCount++;
    }
    return max(indCount, outdCount);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d %d", &n, &m);
        init(n);
        for(int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
        }
        solve(n);
        if(sccCount == 1) {
            printf("0\n");
            continue;
        }
        shrinkGraph(n);
        int ans = calculateMinEdges();
        printf("%d\n", ans);
    }
    return 0;
}