#include <stdio.h>
#include <string.h>

#define MAXN 10010
#define MAXM 100010

// 链式前向星邻接表
int head[MAXN];
int edge[MAXM];
int next[MAXM];
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

// 存储每个强连通分量的大小
int sccSize[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

void init(int n) {
    for(int i = 1; i <= n; ++i) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        inStack[i] = 0;
        sccId[i] = 0;
    }
    // 初始化 sccSize 数组，包括 0 号强连通分量
    for(int i = 0; i < MAXN; ++i) {
        sccSize[i] = 0;
    }
    cnt = 0;
    top = 0;
    timeStamp = 0;
    sccCount = 0;
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
            sccSize[sccCount]++;
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
        long long ans = 0;
        for(int i = 0; i < sccCount; ++i) {
            int size = sccSize[i];
            ans += (long long)size * (size - 1) / 2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}