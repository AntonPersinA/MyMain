#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "homework.h"
#include "homework.h"
#include <time.h>
#include <stdarg.h>
#include <limits.h>
#include "big_int.h"


#define sq(A, B) "sq of rectangle ("#A") * ("#B")\n"
#define test(gg) x##gg


//clock_t start, end;
//long long x;
//start = clock();
//x = int_pow_n(3, int_pow_n(8,10)-1);
//end = clock();
//printf("%lld\n%f\n", x, ((double)end - start)/CLOCKS_PER_SEC);


#define size 10


int len_str(char *str){
    return strlen(str);
}
int main(){
    big_int *n1,*n2;

    n1 = big_int_get("1000000000000001");

//    char x = 300;

    printf("%d\n", n1->number[102]);
//    n1 = big_int_get("10101010");
//
    big_int_print(n1);
//    big_int_print(n2);
//
//    big_int_swap(n1,n2);
//    big_int_swap(n1,n2);
//    big_int_swap(n1,n2);
//    big_int_swap(n1,n2);
//
//    big_int_print(n1);
//    big_int_print(n2);
//
//    big_int_free(n2);
    big_int_free(n1);
}



























