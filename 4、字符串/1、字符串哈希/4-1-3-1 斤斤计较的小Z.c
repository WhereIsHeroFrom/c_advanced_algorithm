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

char s1[maxn], s2[maxn];

int main() {
    scanf("%s %s", s1, s2);
    init(s1);
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    ull v = get(0, s1len-1);
    int ans = 0;
    init(s2);
    for(int i = 0; i + s1len-1 < s2len ; ++i) {
        if( get(i, i + s1len-1) == v ) {
            ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}
