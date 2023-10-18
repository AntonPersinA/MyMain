#include <stdio.h>

int is_it_prime(int num){
    num = abs(num);
    if (num <=1)
        return 0;
    int i;
    double power = pow(num*1.0, 0.5);
    for (i = 2; i<=power*1; ++i){
        if (num%i==0){
            return 0;
        }
    }
    return 1;
}


void print_prime_before(int num_before){
    num_before = abs(num_before);
    printf("{");
    for (int i = 2; i<=num_before; ++i){
        if (is_it_prime(i) == 1){
            printf("%d, ", i);
        }
    }
    printf("\b\b}");
}


void main(){
    print_prime_before(30);
}