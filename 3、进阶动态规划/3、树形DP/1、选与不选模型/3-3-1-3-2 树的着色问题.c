//////////////////////////////////////////////////////////////////////
///////////////////////简单树形DP模板（选or不选）///////////////////////
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#define type long long
#define maxn 100010
#define maxm 200010 // 每个边存储两次
#define inf -1000000000000LL
#define mod 1000000007

int n;
// dp[i][0] 代表以 i 为根节点的子树，且根节点不选的最大（小）价值（或方案数）
// dp[i][1] 代表以 i 为根节点的子树，且根节点  选的最大（小）价值（或方案数）
type dp[maxn][2];

// 邻接表存储树
int head[maxn];
int edge[maxm];
int next[maxm];
int cnt;

void add_edge(int a, int b) {
    edge[cnt] = b;
    next[cnt] = head[a];
    head[a] = cnt++;
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
    scanf("%d", &n);
    TreeDPSimple_Init(n);
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    } 
    type ans = (TreeDPSimple_DFS(1, 0, -1) + TreeDPSimple_DFS(1, 1, -1)) % mod;
    printf("%lld\n", ans);
    return 0;
}