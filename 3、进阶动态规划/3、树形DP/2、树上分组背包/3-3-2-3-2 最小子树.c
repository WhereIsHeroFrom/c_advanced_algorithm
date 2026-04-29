#include <stdio.h>
#include <string.h>

///////////////////////////////// 树上分组背包模板 ////////////////////////////////
#define type int
#define maxn 100010
#define maxv 3
#define maxm 200010
#define inf 100000000
#define mod 998244353

struct Item {
    int vol;    // 每个物品的容量
    int wei;    // 每个物品的权值
}items[maxn];

int head[maxn], edge[maxm], next[maxm];
int cnt;

// dp[i][j] 代表以i为根的子树中
// 选择容量总和为j的物品，得到的最优价值
type dp[maxn][maxv];
// sumVol[i] 代表所有子结点的容量和
int sumVol[maxn];
// n件物品，最大容量为V
int n, V;

type min(type a, type b) {
    return a < b ? a : b;
}

void AddEdge(int a, int b) {
    edge[cnt] = b;
    next[cnt] = head[a];
    head[a] = cnt++;
}

// 1、修改点，初始状态值
// 需要根据题目含义进行修改
type KnapsackTreeDP_InitValue(int u) {
    return 0;
}

// 2、修改点，状态转移方程
// 需要根据题目含义进行修改
type KnapsackTreeDP_Opt(type curVal, type preVal, type itemWei) {
    return min(curVal, preVal + itemWei);
}

// 3、修改点，这一步非常关键
// 目的是把 滚动数组 dpu 中计算出的数据，转移到 dp 上
// dpu 是临时数据，递归结束就销毁了
// dp 是持久化数据，递归结束一直保存
void KnapsackTreeDP_Post(int u, type dpu[maxv]) {
    for(int j = 0; j <= V; ++j) {
        dp[u][j] = dpu[j] + items[u].wei;
    }
}

// 4、修改点，获取最优解，根据题目要求执行逻辑
type KnapsackTreeDP_GetAnswer(int root) {
    type ans = inf;
    for(int i = 1; i <= n; ++i) {
        int mv = (i==root?V:V-1);
        for(int j = 0; j <= mv; ++j)
            ans = KnapsackTreeDP_Opt( ans, dp[i][j], 0 );
    }
    return ans;
}

// 模版代码，基本不用改
void KnapsackTreeDP_Dfs(int u, int fat) {
    // 1、初始化 dpu[pre][...]
    type dpu[2][maxv];
    int pre = 0;
    dpu[pre][0] = KnapsackTreeDP_InitValue(u);
    for(int i = 1; i <= V; ++i) {
        dpu[pre][i] = inf;
    }
    int cur = 1 - pre;
    sumVol[u] = items[u].vol;
    // 2、遍历子结点进行分组背包
    for(int i = head[u]; i != -1; i = next[i]) {
        int v = edge[i];
        if(v == fat) continue;
        KnapsackTreeDP_Dfs(v, u);
        sumVol[u] += sumVol[v];
        for(int j = 0; j <= V; ++j) {
            // 以 u 为根的子树中，在总容量为 j 的情况下
            // 选择容量总和为 j 的物品，得到的最优价值
            // k 代表 v 子结点中选择的物品容量总和
            // j-k 代表在 v 之前的子结点中选择的物品容量总和
            dpu[cur][j] = inf;
            // 和模板有出入需要增加一个判定
            if(j > 0) dpu[cur][j] = dpu[pre][j-1];
            for(int k = 0; k <= j && k <= sumVol[v]; ++k) {
                dpu[cur][j] = KnapsackTreeDP_Opt(dpu[cur][j], dpu[pre][j-k], dp[v][k]);
            }
        }
        pre ^= 1;
        cur ^= 1;
    }
    // 3、把 滚动数组 dpu 中计算出的数据，转移到 dp 上
    KnapsackTreeDP_Post(u, dpu[pre]);
}
///////////////////////////////// 树上分组背包模板 ////////////////////////////////

int main() {
    V = 2;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        items[i].vol = 1;
        scanf("%d", &items[i].wei);
    }
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        AddEdge(x, y);
        AddEdge(y, x);
    }
    KnapsackTreeDP_Dfs(1, 0);
    printf("%d\n", KnapsackTreeDP_GetAnswer(1));
    return 0;
}