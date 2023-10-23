#include <stdio.h>


long long ll_pow_n(int m, int n){
    long long ans = 1;
    for(int i = 0; i<n;++i)
        ans*=m;
    return ans;
}


long long ll_pow_logn(int m, int n){
    long long otv = 1;
    if (n == 0){return 1;}
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


int test_MyPow(){
    FILE *fr = fopen("2test1.txt", "r");

    if (fr == NULL){
        perror("2test1.txt");
        return 0;
    }

    int n,m;

    long long ans;
    fscanf(fr, "%d", &m);
    fscanf(fr, "%d", &n);
    fscanf(fr, "%Ld", &ans);

    if (ans != ll_pow_logn(m,n)){
        fclose(fr);
        return -1;
    }

    if (ans != ll_pow_n(m,n)){
        fclose(fr);
        return -2;
    }
    fclose(fr);
    return 1;
}


int main() {
    printf("%d\n", test_MyPow());
    return 0;
}