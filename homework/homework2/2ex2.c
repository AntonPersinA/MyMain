#include <stdio.h>


long long ll_pow_n(long long m, long long n){
    long long ans = 1;
    for(int i = 0; i<n;++i)
        ans*=m;
    return ans;
}


long long ll_pow_logn(long long m, long long n){
    long long otv = 1;
    while (n>1){
        if (n%2 == 0){
            m*=m;
            n>>=1;
        }
        else{
            otv*=m;
            n-=1;
            m*=m;
            n>>=1;
        }
    }
    return otv*m;
}


int main() {
    printf("result O(logn) = %lld\n", ll_pow_logn(2, 3));
    printf("result O(n)    = %lld\n", ll_pow_n(2, 3));
    return 0;
}