#include <stdio.h>

////////////////////状压DP模板(带约束的01矩阵)////////////////////
#define maxn 226
#define maxm 16
#define type long long
#define inf 0
#define init 1
#define mod 10007
#define GridType_EMPTY -1
#define GridType_ZERO 0
#define GridType_ONE 1

type dp[2][1<<maxm];
int grid[maxn][maxm];

// 根据实际题目要求进行修改，有可能是最小值，最大值 或者方案数
type MatrixPutDP_Opt( type cur, type pre, type curOneCount) {
    return (cur + pre) % mod;
}

// 根据实际题目要求进行修改，放置与否
int matrixPutDP_canPut(int prestate, int curstate, int r, int c) {
    if( grid[r][c] != GridType_EMPTY ) {
        return 0;
    }
    // 如果上面有1，不能放1
    if(r > 0 && grid[r-1][c] == GridType_ONE) {
        return 0;
    }
    if(prestate & 1) {
        return 0;
    }

    // 如果下面有1，不能放1
    if(grid[r+1][c] == GridType_ONE) {
        return 0;
    }

    // 如果左边有1，不能放1
    if(c > 0 && grid[r][c-1] == GridType_ONE) {
        return 0;
    }
    if( (curstate>>1) & 1 ) {
        return 0;
    }
    // 如果右边有1，不能放1
    if(grid[r][c+1] == GridType_ONE) {
        return 0;
    }
    return 1;
}

// 固定模板，无需修改
void MatrixPutDP_Dfs(int col, int maxcol, 
    int row, int pre, int prestate, 
    int cur, int curstate, int cnt) {
    
    if(col == maxcol) {
        dp[cur][curstate] = MatrixPutDP_Opt( dp[cur][curstate], dp[pre][prestate], cnt);
        return ;
    }
    // 枚举前一行放和不放
    for(int i = 0; i < 2; ++i) {
        int pres = prestate << 1 | i;
        // 枚举这一行放和不放
        for(int j = 0; j < 2; ++j) {
            int curs = (curstate << 1 | j);
            if(j == GridType_ONE) {
                if( !matrixPutDP_canPut(pres, curs, row, col) ) {
                    continue;
                }
            }
            MatrixPutDP_Dfs(col+1, maxcol, row, pre, pres, cur, curs, cnt + j);
        }
    }
}

// 固定模板，无需修改
type MatrixPutDP_Solve(int n, int m) {
    // 1、初始状态
    int pre = 0, cur = 1;
    for(int i = 0; i < (1<<m); ++i) {
        dp[pre][i] = inf;
    }
    dp[pre][0] = init;
    // 2、状态转移
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1<<m); ++j) {
            dp[cur][j] = inf;
        }
        MatrixPutDP_Dfs(0, m, i, pre, 0, cur, 0, 0);
        pre ^= 1;
        cur ^= 1;
    }
    // 3、总结状态
    type ans = inf;
    for(int j = 0; j < (1<<m); ++j) {
        ans = MatrixPutDP_Opt(ans, dp[pre][j], init);
    }
    return ans;
}

////////////////////状压DP模板(带约束的01矩阵)////////////////////

char mat[maxm][maxm];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%s", mat[i]);
    }
    if(n > m) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(mat[i][j] == '0') grid[i][j] = GridType_ZERO;
                else if(mat[i][j] == '1') grid[i][j] = GridType_ONE;
                else grid[i][j] = GridType_EMPTY;
            }
        }
    }else {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(mat[i][j] == '0') grid[j][i] = GridType_ZERO;
                else if(mat[i][j] == '1') grid[j][i] = GridType_ONE;
                else grid[j][i] = GridType_EMPTY;
            }
        }
        int tmp = n;
        n = m;
        m = tmp;
    }
    printf("%lld\n", MatrixPutDP_Solve(n, m));
    return 0;
}