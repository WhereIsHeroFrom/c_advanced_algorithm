#include <stdio.h>
#include <string.h>

#define MAXN 10010
#define MAXM 100010
#define MAXSCC 10010
#define MAXSCCEDGE 100010

// 链式前向星邻接表（原图）
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

// 缩点后的图（链式前向星）
int sccHead[MAXSCC];
int sccEdge[MAXSCCEDGE];
int sccNext[MAXSCCEDGE];
int sccCnt;
int ind[MAXSCC];
int outd[MAXSCC];

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

// 缩点函数
void shrinkGraph(int n) {
    // 初始化缩点后的图
    for(int i = 0; i < sccCount; ++i) {
        sccHead[i] = -1;
        ind[i] = 0;
        outd[i] = 0;
    }
    sccCnt = 0;

    // 遍历原图的所有边
    for(int u = 1; u <= n; ++u) {
        for(int i = head[u]; i != -1; i = next[i]) {
            int v = edge[i];
            int sccU = sccId[u];
            int sccV = sccId[v];
            if(sccU == sccV) continue;

            // 检查这条边是否已经存在
            int exists = 0;
            for(int j = sccHead[sccU]; j != -1; j = sccNext[j]) {
                if(sccEdge[j] == sccV) {
                    exists = 1;
                    break;
                }
            }
            if(!exists) {
                // 添加新边
                sccEdge[sccCnt] = sccV;
                sccNext[sccCnt] = sccHead[sccU];
                sccHead[sccU] = sccCnt++;
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