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

//    char *a = '1';
//    printf("%i\n", (a - '0'));
//    char str = '0';
//    printf("%d\n", str);
    big_int *n1;
    n1 = big_int_get("10000000");
    big_int_print(n1);
//    printf("%s\n", n1->number);
//    print_array(n1->number, n1->length);
//    printf("%d    ", 5&5);
    printf("%ld\n\n\n", sizeof(n1->number[0]));
    free(n1->number);
    free(n1);
}



























