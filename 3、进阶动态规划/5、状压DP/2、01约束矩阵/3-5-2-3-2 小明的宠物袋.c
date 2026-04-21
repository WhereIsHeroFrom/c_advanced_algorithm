#include <stdio.h>

///////////////////////////////////////////////////
/////////////状压DP - 带约束的01矩阵模板/////////////
///////////////////////////////////////////////////
//// 所有的1不能相邻，求方案数，最大值，最小值等等 ////
/*
1、求最大值，所以 dptype 选择 1 (MAX)
2、输入0的GridType就是-1 (EMPTY)，否则是0 (ZERO)
3、根据 (Mask::UP|Mask::LEFT) 满足约束填入 1 (ONE)
*/

#define maxn 30
#define maxm 10
#define type long long
#define dptype 1  // 0: MIN, 1: MAX, 2: NUM, 3: MOD
#define mod 100000000
#define MaskType (1|2)  // UP|LEFT
#define GridType_EMPTY -1
#define GridType_ZERO 0
#define GridType_ONE 1
#define Mask_UP (1<<0)
#define Mask_LEFT (1<<1)

int n, m;
type dp[2][1<<maxm];
int grid[maxn][maxm];

type min(type a, type b) {
    return a < b ? a : b;
}

type max(type a, type b) {
    return a > b ? a : b;
}

// 固定模板
type MatrixPutDP_opt( type cur, type pre, type curOneCount) {
    if (dptype == 0) {  // MIN
        return min(cur, pre + curOneCount);
    }else if(dptype == 1) {  // MAX
        return max(cur, pre + curOneCount);
    }else if(dptype == 2) {  // NUM
        return cur + pre;
    }else {  // MOD
        return (cur + pre) % mod;
    }
}

// 固定模板，如果类型不是 long long基本不需要修改
type MatrixPutDP_ValueInf() {
    if (dptype == 0) {  // MIN
        return 1000000000;
    }else if(dptype == 1) {  // MAX
        return -1000000000;
    }else if(dptype == 2) {  // NUM
        return 0;
    }else if(dptype == 3) {  // MOD
        return 0;
    }
}

// 固定模板
type MatrixPutDP_ValueInit() {
    if (dptype == 0) {  // MIN
        return 0;
    }else if(dptype == 1) {  // MAX
        return 0;
    }else if(dptype == 2) {  // NUM
        return 1;
    }else if(dptype == 3) {  // MOD
        return 1;
    }
}

// 根据 LEFT 和 UP 进行判断，不能有相邻的 ONE
bool MatrixPutDP_canPut(int prestate, int curstate, int r, int c) {
    if( grid[r][c] != GridType_EMPTY ) {
        return false;
    }
    if(MaskType & Mask_UP) {
        if(r > 0 && grid[r-1][c] == GridType_ONE) {
            return false;
        }
        if(prestate & 1) {
            return false;
        }
    }
    if(MaskType & Mask_LEFT) {
        if(c > 0 && grid[r][c-1] == GridType_ONE) {
            return false;
        }
        if( (curstate>>1) & 1 ) {
            return false;
        }
    }
    return true;
}

void MatrixPutDP_Dfs(int col, int maxcol, 
    int row, int pre, int prestate, 
    int cur, int curstate, int cnt) {
    
    if(col == maxcol) {
        dp[cur][curstate] = MatrixPutDP_opt( dp[cur][curstate], dp[pre][prestate], cnt);
        return ;
    }
    // 枚举前一行放和不放
    for(int i = 0; i < 2; ++i) {
        int pres = prestate << 1 | i;
        // 枚举这一行放和不放
        for(int j = 0; j < 2; ++j) {
            int curs = (curstate << 1 | j);
            if(j == GridType_ONE) {
                if( !MatrixPutDP_canPut(pres, curs, row, col) ) {
                    continue;
                }
            }
            MatrixPutDP_Dfs(col+1, maxcol, row, pre, pres, cur, curs, cnt + j);
        }
    }
}

type MatrixPutDP_Solve(int n, int m) {
    // 1、初始状态
    int pre = 0, cur = 1;
    for(int i = 0; i < (1<<m); ++i) {
        dp[pre][i] = MatrixPutDP_ValueInf();
    }
    dp[pre][0] = MatrixPutDP_ValueInit();
    // 2、状态转移
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1<<m); ++j) {
            dp[cur][j] = MatrixPutDP_ValueInf();
        }
        MatrixPutDP_Dfs(0, m, i, pre, 0, cur, 0, 0);
        int temp = pre;
        pre = cur;
        cur = temp;
    }
    // 3、总结状态
    type ans = MatrixPutDP_ValueInf();
    for(int j = 0; j < (1<<m); ++j) {
        ans = MatrixPutDP_opt(ans, dp[pre][j], MatrixPutDP_ValueInit());
    }
    return ans;
}

///////////////////////////////////////////////////
/////////////状压DP - 带约束的01矩阵模板/////////////
///////////////////////////////////////////////////

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);
            if(x == 0) {
                grid[i][j] = GridType_EMPTY;
            }else {
                grid[i][j] = GridType_ZERO;
            }
        }
    }
    printf("%lld\n", MatrixPutDP_Solve(n, m));
    return 0;
}