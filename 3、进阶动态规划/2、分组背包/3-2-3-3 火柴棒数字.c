#include <stdio.h>
#include <string.h>

#define max_str_len 100
typedef struct {
    char str[max_str_len];
} DPNode;

////////////////////////////////////分组背包模板////////////////////////////////////
#define maxn 10
#define maxc 11
#define maxv 305
#define vType DPNode
#define inf (DPNode){""}
#define init (DPNode){""}

struct Item {
    int cnt;
    int w[maxc];
    vType v[maxc];  
};

// 1、修改点1：字符串比较的逻辑
vType opt(vType a, vType b) {
    int str_cmp(const char* x, const char* y) {
        int len_x = strlen(x);
        int len_y = strlen(y);
        if(len_x != len_y) return len_x - len_y;
        return strcmp(x, y);
    }

    if(strcmp(a.str, inf.str) == 0) return b;
    if(strcmp(b.str, inf.str) == 0) return a;
    return str_cmp(a.str, b.str) > 0 ? a : b;
}

// 2、修改点2：结构体加法：字符串拼接（C无运算符重载，用函数替代+）
vType add(vType a, vType b) {
    vType res = inf;
    strcpy(res.str, a.str);
    strcat(res.str, b.str);
    return res;
}

void KnapsackGroup(int n, int V, struct Item items[], vType dp[maxn][maxv]) {
    for(int i = 1; i <= V; ++i) {
        dp[0][i] = inf;
    }
    dp[0][0] = init;

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= V; ++j) {
            dp[i][j] = dp[i-1][j];
            for(int k = 0; k < items[i].cnt; ++k) {
                if(j >= items[i].w[k]) {
                    // 3、修改点3：模板原有 tmp = 前状态 + 价值 → 调用add函数实现拼接
                    vType tmp = add(dp[i-1][j - items[i].w[k]], items[i].v[k]);
                    dp[i][j] = opt( dp[i][j], tmp );
                }
            }
        }
    }
}
////////////////////////////////////分组背包模板////////////////////////////////////

// 全局变量
struct Item items[maxn];
vType dp[maxn][maxv];

int tbl[] = {
    -1, 2, 5, 5, 4, 5, 6, 3, 7, 6
};

// 数字转字符串
void to_string(int num, vType* node) {
    sprintf(node->str, "%d", num);
}

int main() {
    int n, V;
    n = 9;
    V = 300;
    for(int i = 1; i <= n; ++i) {
        items[i].cnt = 10;
        int num = n + 1 - i;
        for(int j = 0; j < items[i].cnt; ++j) {
            items[i].w[j] = tbl[num] * (j + 1);
            to_string(num, &items[i].v[j]);
            if(j > 0) {
                strcat(items[i].v[j].str, items[i].v[j-1].str);
            }
        }
    }
    KnapsackGroup(n, V, items, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[n][i]);
    }
    printf("%s\n", ret.str);
    return 0;
}