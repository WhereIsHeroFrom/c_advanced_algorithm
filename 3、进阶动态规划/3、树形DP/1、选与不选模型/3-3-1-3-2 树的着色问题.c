#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
///////////////////////简单树形DP模板（选or不选）///////////////////////
//////////////////////////////////////////////////////////////////////

#define type long long
#define maxn 100010
#define maxm 200010
#define inf -1000000000000LL
#define mod 1000000007

type dp[maxn][2];
int head[maxn], edge[maxm], next[maxm];
int cnt;
type w[maxn];

void add_edge(int a, int b) {
    edge[cnt] = b;
    next[cnt] = head[a];
    head[a] = cnt++;
}

// 每个要求题目不同，需要做修改
type max(type a, type b) {
    return a > b ? a : b;
}

void TreeDPSimple_AddEdge(int a, int b) {
    add_edge(a, b);
    add_edge(b, a);
}

// 每个要求题目不同，需要做修改
type TreeDPSimple_InitVal(int u, int isChoose) {
    return 1;
}

// 每个要求题目不同，需要做修改
type TreeDPSimple_Opt(type curVal, int isChoose, type ncVal, type cVal) {
    if(isChoose) {
        return curVal * ncVal % mod;
    }
    return curVal * (ncVal + cVal) % mod;
}

// 模板代码，一般不做修改
void TreeDPSimple_Init(int n) {
    for(int i = 0; i <= n; ++i) {
        dp[i][0] = dp[i][1] = inf;
    }
    memset(head, -1, sizeof(head));
    cnt = 0;
}

// 模板代码，一般不做修改
type TreeDPSimple_DFS(int u, int isChoose, int fat) {
    if(dp[u][isChoose] != inf) {
        return dp[u][isChoose];
    }
    type ans = TreeDPSimple_InitVal(u, isChoose);
    for(int i = head[u]; i != -1; i = next[i]) {
        int v = edge[i];
        if(v == fat) continue;
        type nc = TreeDPSimple_DFS(v, 0, u);
        type  c = TreeDPSimple_DFS(v, 1, u);
        ans = TreeDPSimple_Opt(ans, isChoose, nc, c);
    }
    return dp[u][isChoose] = ans;
}

//////////////////////////////////////////////////////////////////////
///////////////////////简单树形DP模板（选or不选）///////////////////////
//////////////////////////////////////////////////////////////////////
int main() {
    int n;
    scanf("%d", &n);
    TreeDPSimple_Init(n);
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        TreeDPSimple_AddEdge(x, y);
    } 
    type ans = (TreeDPSimple_DFS(1, 0, -1) + TreeDPSimple_DFS(1, 1, -1)) % mod;
    printf("%lld\n", ans);
    return 0;
}