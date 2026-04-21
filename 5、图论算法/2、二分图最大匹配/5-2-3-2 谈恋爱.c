#include <stdio.h>
#include <string.h>

/////////////////////////////////////////////////////////////
//////////////////二分图最大匹配模板(邻接表) //////////////////
/////////////////////////////////////////////////////////////
// 顶点范围  左边的点[1, n]，右边的点[1, m]

#define maxn 1010
#define maxm 1010
#define false 0
#define true 1
#define bool int



// 邻接表实现
int head[maxn];
int edge[maxn*maxm];
int next[maxn*maxm];
int cnt;

int pre[maxm];             // 匈牙利算法找增广路时的pre数组
bool visit[maxm];          // 匈牙利算法找增广路时的visit数组
int n, m;                  // 左、右点集的数目

// 初始化二分图
void Hungarian_Initialize(int n_, int m_) {
    n = n_;
    m = m_;
    memset(pre, -1, sizeof(pre));
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }
    cnt = 0;
}

void Hungarian_AddEdge(int u, int v) {
    edge[cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt++;
}

bool Hungarian_findMatch(int u) {
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = edge[i];
        if (!visit[v]) {
            visit[v] = true;
            int vpre = pre[v];
            pre[v] = u;
            if (vpre == -1 || Hungarian_findMatch(vpre)) {
                return true;
            }
            pre[v] = vpre;
        }
    }
    return false;
}

// 获取最大匹配数
int Hungarian_GetMaxMatch() {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        memset(visit, false, sizeof(visit));
        if (Hungarian_findMatch(i)) {
            ++cnt;
        }
    }
    return cnt;
}
/////////////////////////////////////////////////////////////
//////////////////二分图最大匹配模板(邻接表) //////////////////
/////////////////////////////////////////////////////////////

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Hungarian_Initialize(n, m);
    for(int i = 1; i <= k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        Hungarian_AddEdge(x, y);
    }
    printf("%d\n", Hungarian_GetMaxMatch());
    return 0;
}