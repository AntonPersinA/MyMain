#include <time.h>
#include <stdio.h>

#define test    41

long long fibonachi_def(int n){
    if (n==1 || n == 2)
        return 1;
//    if (n%2 == 0){
//        long long f_k = fibonachi_def(n/2);
//        long long f_k1 = fibonachi_def(n/2-1);
//        return f_k*(2*f_k1 + f_k);
//    }
    return fibonachi_def(n-1)+ fibonachi_def(n-2);
}


long long fibonachi_for(int n){
    long long s_1 = 1, s_2 = 1, help;
    for (int i = 3; i <= n; i++){
        help = s_2;
        s_2 += s_1;
        s_1 = help;
    }
    return s_2;
}


int main() {
    clock_t end, start;
    int answer;
    start = clock();
    fibonachi_def(test);
    end = clock();
    printf("recursion running time = %f\n", ((double)end - start)/CLOCKS_PER_SEC);

    start = clock();
    fibonachi_for(test);
    end = clock();
    printf("for loop time          = %f\n", ((double)end - start)/CLOCKS_PER_SEC);
    return 0;
}