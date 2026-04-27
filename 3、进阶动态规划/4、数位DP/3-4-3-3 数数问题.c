#include <stdio.h>
#include <string.h>
//////////////////////////////////////数位DP模板//////////////////////////////////////
// 0、修改点，主要修改 data0_max 和 data1_max 的范围
#define ll long long
#define maxd 100
#define data0_max 305
#define data1_max 2

// 1、修改点，通过输入数据进行输入
ll K;
// 2、修改点，通过题目条件进行修改，二进制就是 2，十进制就是 10，也有可能通过输入数据输入
ll base;
// dp[depth][is_leadingZero][is_limit][data0][data1]
ll dp[maxd][2][2][data0_max][data1_max];

typedef struct {
    ll data0;
    ll data1;
} DpData;

// 3、修改点，数据的初始化，确定 data0 和 data1 表示的是什么
void DpData_init(DpData* this) {
    this->data0 = 0;   // 所有数字之和
    this->data1 = 0;   // 留空不用
}

// 4、修改点，dfs 返回值
ll DpData_dfsReturn(DpData* this, int is_leadingZero) {
    if(is_leadingZero) {
        // 0000000000
        return K == 0 ? 1 : 0;
    }
    return this->data0 == K;
}

// 5、修改点，状态转移的过程
void DpData_getNextDpData(DpData* this, DpData* ret, int is_leadingZero, int digit) {
    ret->data0 = this->data0;
    ret->data1 = this->data1;
    if(is_leadingZero) {
        // 0000000000
        ret->data0 = digit;
    }else {
        // 0000122313
        ret->data0 += digit;
    }
}

// 固定模板，不需要修改
ll digitDP_dfs(
    const char* num,     // 数字字符串
    int depth,           // 当前枚举到的是第几个数位
    int is_leadingZero,  // 为 1 时，代表前面枚举的都是0；默认为 1
    int is_limit,        // 为 1 时，代表前面数位已经 < num 的高位；默认为 0
    DpData dpdata        // 数位DP用到的核心数据结构
) {
    if(depth == (int)strlen(num)) {
        return DpData_dfsReturn(&dpdata, is_leadingZero);
    }
    int maxdigit = is_limit ? (base-1) : (num[depth]-'0');
    ll ans = dp[depth][is_leadingZero][is_limit][dpdata.data0][dpdata.data1];
    if(ans != -1) {
        return ans;
    }
    ans = 0;
    for(int i = 0; i <= maxdigit; ++i) {
        DpData nextDpData;
        DpData_getNextDpData(&dpdata, &nextDpData, is_leadingZero, i);
        ans += digitDP_dfs(
            num,
            depth+1,
            is_leadingZero && (i == 0),
            is_limit || (i < maxdigit),
            nextDpData
        );
    }
    dp[depth][is_leadingZero][is_limit][dpdata.data0][dpdata.data1] = ans;
    return ans;
}

// 固定模板，不需要修改，求 [0, n] 中所有满足条件的数的数量
ll DigitDP_GetAns(ll n) {
    memset(dp, -1, sizeof(dp));
    int a[maxd], asize = 0;
    char s[maxd];
    while(n) {
        a[asize++] = n % base;
        n /= base;
    }
    if(asize == 0) {
        a[asize++] = 0;
    }
    for(int i = 0; i < asize; ++i) {
        s[asize-1-i] = '0' + a[i];
    }
    s[asize] = '\0';
    DpData dpd;
    DpData_init(&dpd);
    return digitDP_dfs(s, 0, 1, 0, dpd);
}

// 固定模板，数位DP的差分操作，求 [l, r] 中所有满足条件的数的个数
ll  DigitDP_GetRange(ll l, ll r) {
    return DigitDP_GetAns(r) - DigitDP_GetAns(l-1);
}
//////////////////////////////////////数位DP模板//////////////////////////////////////


ll solve(ll a, ll b, ll k) {
    ll l = a - 1;
    ll r = b + 1;
    ll lans = DigitDP_GetAns(a-1);
    while(l + 1 < r) {
        ll mid = (l + r) >> 1;
        if( DigitDP_GetAns(mid) - lans >= k ) {
            r = mid;
        }else {
            l = mid;
        }
    }
    if( DigitDP_GetAns(r) - lans >= k ) {
        return r;
    }
    return -1;
}

int main() {
    ll l, r, b, m, k;
    scanf("%lld %lld %lld %lld %lld", &l, &r, &b, &m, &k);
    base = b;
    K = m;
    ll ans = solve(l, r, k);
    if(ans == -1) {
        printf("No\n");
    }else {
        printf("%lld\n", ans);
    }
    return 0;
}