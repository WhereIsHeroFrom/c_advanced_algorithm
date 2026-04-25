#include <stdio.h>
#include <string.h>

////////////////////////////manacher模板////////////////////////////
#define maxn 1000010
#define SPLIT '$'
int p[maxn];
char strTmp[maxn];

int manacherMatch(char a, char b) {
    return a == b;
}

void manacherPre(char *str) {
    strcpy(strTmp, str);
    int i;
    for(i = 0; strTmp[i]; ++i) {
        str[2*i] = SPLIT;
        str[2*i+1] = strTmp[i];
    }
    str[2*i] = SPLIT;
    str[2*i+1] = '\0';
}

int min(int a, int b) {
    return a < b ? a : b;
}

int Manacher(char *str) {
    manacherPre(str);
    // ct  : 当前已知最右回文区域的中心位置
    //  r  : 当前已知最右回文区域的右边界（即ct + p[ct]）
    // p[] : 记录每个位置的回文半径
    int ct = 0, r = 0, maxLen = 1;
    p[0] = 1;
    for(int i = 1; str[i]; ++i) {
        // 1.计算p[i]初始值 
        if(i < r) {
            p[i] = min(p[2*ct-i], r-i);
        }else {
            p[i] = 0;
        }

        // 2.扩张p[i]，以适应达到p[i]最大值 
        while(i-p[i]>=0 && manacherMatch(str[i-p[i]], str[i+p[i]]) )
            ++p[i];

        // 3.更新ct
        if(p[i] + i > r) {
            ct = i;
            r = p[i] + i;
        }
        // 4.更新最长回文 
        if(2*p[i]-1 > maxLen) {
            maxLen = 2*p[i] - 1;
        }
    }
    return maxLen; 
}
////////////////////////////manacher模板////////////////////////////

char str[maxn];

int main() {
    scanf("%s", str);
    int ans = Manacher(str);
    printf("%d\n", ans/2);
    return 0;
}