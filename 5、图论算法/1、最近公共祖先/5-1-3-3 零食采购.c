#include <stdio.h>
#include <string.h>

#define maxn 100010
#define maxd 21
#define dummyroot 0

int f[maxn][maxd]; // f[i][j] 代表i号结点的第2^j个祖先
int dep[maxn];     // dep[i] 代表i在这棵树上的深度

// 邻接表实现
int head[maxn];
int edge[maxn*4];
int next[maxn*4];
int cnt;

int w[maxn], fw[maxn][21];  // fw[i][j]代表从根结点到i结点，有多少个种类为j的零食


// 队列实现
int q[maxn*4];
int front, rear;

void LCA_Init(int n) {
    for(int i = 1; i <= n; ++i) {
        head[i] = -1;
    }
    memset(f, dummyroot, sizeof(f));
    cnt = 0;
}

void LCA_AddEdge(int u, int v) {
    edge[cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt++;
    edge[cnt] = u;
    next[cnt] = head[v];
    head[v] = cnt++;
}

void LCA_PreProcess(int root) {
    front = rear = 0;
    f[root][0] = dummyroot;
    fw[root][ w[root] ] = 1;
    dep[root] = 0;
    q[rear++] = root;
    while( front < rear ) {
        int u = q[front++];
        for(int i = 1; i < maxd; ++i) {
            f[u][i] = f[ f[u][i-1] ][ i-1 ];
            if(f[u][i] == dummyroot) break;
        }
        for(int i = head[u]; i != -1; i = next[i]) {
            int v = edge[i];
            if(v == f[u][0]) {
                continue;
            }
            f[v][0] = u;
            // 树上前缀和
            for(int j = 1; j <= 20; ++j) {
                fw[v][j] = fw[u][j] + (w[v] == j ? 1 : 0);
            }
            dep[v] = dep[u] + 1;
            q[rear++] = v;
        }
    }
}

int LCA_Get(int u, int v) {
    // 确保 u的深度 >= v的深度
    if(dep[u] < dep[v]) {
        return LCA_Get(v, u);
    }
    // 将 u 和 v 调整到同一深度
    for(int i = maxd-1; i >= 0; --i) {
        if( dep[u] - (1<<i) >= dep[v] ) {
            u = f[u][i];
        }
    }
    if(u == v) {
        return u;
    }
    // 让 u 和 v 同时网上进行倍增
    for(int i = maxd - 1; i >= 0; --i) {
        if( f[u][i] != f[v][i] ) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

/*
           1
          /
         /
       ....
        /
       z
      / 
    .......
     /   
     x   y
*/

int main() {
    int n;
    int q;
    scanf("%d %d", &n, &q);
    LCA_Init(n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &w[i]);
    }
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        LCA_AddEdge(x, y);
    }
    LCA_PreProcess(1);
    while(q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        int u = LCA_Get(x, y);
        int ans = 0;
        // 枚举每一种零食，在 x->u 以及 y->u 的路径和上是否出现过
        for(int j = 1; j <= 20; ++j) {
            int val = (fw[x][j] - fw[u][j]) + (fw[y][j] - fw[u][j]) + (w[u] == j ? 1 : 0);
            ans += (val > 0 ? 1 : 0);
        } 
        printf("%d\n", ans);
    }
    return 0;
}