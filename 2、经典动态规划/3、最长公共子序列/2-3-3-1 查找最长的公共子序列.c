#include <stdio.h>
#include <string.h>

/////////////////////LCS模板/////////////////////
#define maxn 1010
#define maxm 1010
#define type char

int getLCS(int n, type a[], int m, type b[],
    int dp[maxn][maxm], char path[maxn][maxm]) {
        // dp[i][j] 代表 a[1:i] 和 b[1:j] 
        // 这两个数组的最长公共子序列的长度
        // return dp[n][m];
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i] == b[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                path[i][j] = 0;
            }else if( dp[i-1][j] > dp[i][j-1] ) {
                dp[i][j] = dp[i-1][j];
                path[i][j] = 1;
            }else {
                dp[i][j] = dp[i][j-1];
                path[i][j] = 2;
            }
        }
    }
    return dp[n][m];
}
/////////////////////LCS模板/////////////////////

void swap_char(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void constructLCS(int x, type a[], int y, type b[], 
           char path[maxn][maxm], type ans[], int* ansSize
        ) {
    int i = x, j = y;
    *ansSize = 0;
    while(i && j) {
        if( path[i][j] == 0 ) {
            ans[(*ansSize)++] = a[i];
            --i, --j;
        }else if(path[i][j] == 1) {
            --i;
        }else if(path[i][j] == 2) {
            --j;
        }
    }
    for(int i = 0; i < *ansSize/2; ++i) {
        swap_char(&ans[i], &ans[*ansSize-1-i]);
    }
}


int dp[maxn][maxm];
char path[maxn][maxm];

char a[maxn], b[maxm];
char ans[maxn];
int ansSize;

int main() {
    scanf("%s", &a[1]);
    scanf("%s", &b[1]);
    int n = strlen(&a[1]);
    int m = strlen(&b[1]);
    getLCS(n, a, m, b, dp, path);
    int x = 1, y = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(dp[i][j] > dp[x][y]) {
                x = i;
                y = j;
            }
        }
    }
    constructLCS(x, a, y, b, path, ans, &ansSize);
    for(int i = 0; i < ansSize; ++i) {
        printf("%c", ans[i]);
    }
    printf("\n");
    return 0;
}