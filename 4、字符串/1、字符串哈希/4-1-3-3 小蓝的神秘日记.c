/*
hash(0, 0) = s[0]
hash(0, 1) = s[0] * B + s[1]
hash(0, 2) = s[0] x B^2 + s[1] x B + s[2]
hash(0, r)   = sum( s[i] * B^(r-i) | 0 <= i <= r )
hash(0, l-1) = sum( s[i] * B^(l-1-i) | 0 <= i <= l-1 )
hash(0, l-1) * B^{r-l+1} = sum( s[i] * B^(l-1-i) | 0 <= i <= l-1 ) * B^{r-l+1}
                         = sum( s[i] * B^(r-i) | 0 <= i <= l-1 )

hash(0, r) - hash(0, l-1) * B^{r-l+1}
=     sum( s[i] * B^(r-i) | 0 <= i <= r ) - sum( s[i] * B^(r-i) | 0 <= i <= l-1 )
=     sum( s[i] * B^(r-i) | l <= i <= r )             
*/
#include <stdio.h>
#include <string.h>

//////////////×Ö·û´®¹þÏ£Ä£°å//////////////
#define maxn 1000010
#define ull unsigned long long
#define B 271

ull Power[maxn];
ull Hash[maxn];

void init(char *s) {
    int len = strlen(s);
    Power[0] = 1;
    Hash[0] = s[0];
    for(int i = 1; i < len; ++i){
        Hash[i] = Hash[i-1] * B + s[i];
        Power[i] = Power[i-1] * B;
    }
}

ull get(int l, int r) {
    if(l == 0) {
        return Hash[r];
    }
    return Hash[r] - Hash[l-1] * Power[r-l+1];
}

//////////////×Ö·û´®¹þÏ£Ä£°å//////////////
typedef struct {
    ull val;
    int pos;
} Pair;

int cmp(const void* a, const void *b) {
    Pair* pa = (Pair*)a;
    Pair* pb = (Pair*)b;
    if (pa->val == pb->val) {
        return pa->pos - pb->pos;
    }
    return pa->val < pb->val ? -1 : 1; 
}

int check(char *s, int n, int len) {
    Pair v[maxn];
    int size = n-len+1;
    for(int i = 0; i + len - 1 < n; ++i) {
        v[i].val = get(i, i+len-1);
        v[i].pos = i;
    }
    qsort(v, size, sizeof(Pair), cmp);
    for(int i = 0; i < size; ++i) {
        int j = i+1;
        for(; j < size; ++j) {
            if(v[j].val != v[i].val) {
                i = j - 1;
                break;
            }
            if(v[j].pos - v[i].pos >= len) {
                return 1;
            }
        }
    }
    return 0;
}


char s[maxn];

int main(int argc, char *argv[]) {
    scanf("%s", s);
    int n = strlen(s);
    init(s);
    int l = -1, r = n/2 + 1;
    while(l + 1 < r) {
        int mid = (l + r) >> 1;
        if( check(s, n, mid) ) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%d\n", l);
    return 0;
}
