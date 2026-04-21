#include <stdio.h>
#include <string.h>

#define maxn 10
#define maxc 11
#define maxv 305
#define max_str_len 100
#define inf ""
#define init ""

struct Item {
    int cnt;
    int w[maxc];
    char v[maxc][max_str_len];
};

void to_string(int num, char* str) {
    sprintf(str, "%d", num);
}

int str_cmp(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a != len_b) {
        return len_a - len_b;
    }
    return strcmp(a, b);
}

void opt(char* result, const char* a, const char* b) {
    if(strcmp(a, inf) == 0) {
        strcpy(result, b);
        return;
    }
    if(strcmp(b, inf) == 0) {
        strcpy(result, a);
        return;
    }
    if(str_cmp(a, b) > 0) {
        strcpy(result, a);
    } else {
        strcpy(result, b);
    }
}

void KnapsackGroup(int n, int V, struct Item items[], char dp[maxn][maxv][max_str_len]) {
    for(int i = 1; i <= V; ++i) {
        strcpy(dp[0][i], inf);
    }
    strcpy(dp[0][0], init);

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= V; ++j) {
            // 前i组物品凑出容量为j的最优价值
            strcpy(dp[i][j], dp[i-1][j]);
            for(int k = 0; k < items[i].cnt; ++k) {
                if(j >= items[i].w[k]) {
                    char tmp[max_str_len];
                    strcpy(tmp, dp[i-1][j - items[i].w[k]]);
                    strcat(tmp, items[i].v[k]);
                    char current[max_str_len];
                    opt(current, dp[i][j], tmp);
                    strcpy(dp[i][j], current);
                }
            }
        }
    }
}

struct Item items[maxn];
char dp[maxn][maxv][max_str_len];

int tbl[] = {
    -1, 2, 5, 5, 4, 5, 6, 3, 7, 6
};

int main() {
    int n, V;
    n = 9;
    V = 300;
    for(int i = 1; i <= n; ++i) {
        items[i].cnt = 10;
        int num = n + 1 - i;
        for(int j = 0; j < items[i].cnt; ++j) {
            items[i].w[j] = tbl[num] * (j + 1);
            // num = 8 , j = 3
            // items[i].v[j] = "8888";
            to_string(num, items[i].v[j]);
            if(j > 0) {
                strcat(items[i].v[j], items[i].v[j-1]);
            }
        }
    }
    KnapsackGroup(n, V, items, dp);
    char ret[max_str_len];
    strcpy(ret, inf);
    for(int i = 0; i <= V; ++i) {
        char current[max_str_len];
        opt(current, ret, dp[n][i]);
        strcpy(ret, current);
    }
    printf("%s\n", ret);
    return 0;
}