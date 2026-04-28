#include <stdio.h>
#include <math.h>

///////////////////////////状压DP模板(哈密尔顿路)///////////////////////////

#define maxn 16
#define type double
#define inf 1000000000
#define init 0
typedef type(*dis_func) (int a, int b);

// dp[i][j] etc, i = 1101, j = 2
// 代表已经访问了0、2、3三个顶点，且上一个顶点是2的最优解
type dp[1<<maxn][maxn];
// dis[i][j] 代表从 i->j 的距离
type dis[maxn][maxn];

type min(type a, type b) {
    return a < b ? a : b;
}

// 需要根据实际题目进行修改，有可能是最小值，最大值 或者方案数
type HamiltonDP_opt( type curVal, type start2i, type i2end) {
    return min(curVal, start2i + i2end);
}

// 固定模板，计算任意两点间的距离
void hamiltonDP_initEdges(int n, dis_func df) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            dis[i][j] = df(i, j);
        }
    }
}

// 固定模板，初始化所有状态，顶点编号是 [0, n)
void hamiltonDP_Init(int n, dis_func df) {
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = -1;
        }
    }
    hamiltonDP_initEdges(n, df);
}

// 固定模板，大部分情况不需要修改
// state ：二进制的1101 代表 0、2、3 三个顶点已经被访问
//     n ：总共多少个顶点
// start : 路径上的起点顶点
//   end ：路径上的终点顶点
type hamiltonDP_Dfs(int state, int n, int start, int end) {
    if (start == end && state == 0) {
        return init;
    }
    if (dp[state][end] >= 0) {
        return dp[state][end];  
    }
    type ans = inf;
    for (int i = 0; i < n; ++i) {
        if ((state & (1 << i)) == 0) {
            continue;
        }
        if ((state & (1 << end)) == 0) {
            continue;
        }
        // start -> ... -> i -> end 为一条路径
        type start2i = hamiltonDP_Dfs(state ^ (1 << end), n, start, i);
        type i2end = dis[i][end];
        ans = HamiltonDP_opt(ans, start2i, i2end);
    }
    return dp[state][end] = ans;
}

// 固定模板，大部分情况不需要修改
// 求从 start 到 所有的 end 路径上的最优值
type HamiltonDP_Solve(dis_func df, int n, int start) {
    hamiltonDP_Init(n, df);
    type ret = inf;
    for(int end = 0; end < n; ++end) {
        type ans = hamiltonDP_Dfs((1 << n) - 1, n, start, end);
        ret = HamiltonDP_opt(ret, init, ans);
    }
    return ret;
}

///////////////////////////状压DP模板(哈密尔顿路)///////////////////////////

int n;
int x[maxn], y[maxn];

type d(int a, int b) {
    return sqrt( 
        (x[a] - x[b]) * (x[a] - x[b])
    +   (y[a] - y[b]) * (y[a] - y[b])
    );
}

int main() {
    scanf("%d", &n);
    n++;
    x[0] = y[0] = 0;
    for(int i = 1; i < n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    printf("%.2lf\n", HamiltonDP_Solve(d, n, 0) );
    return 0;
}