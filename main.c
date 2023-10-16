#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "homework.h"
#include <time.h>
#include <stdarg.h>

#define sq(A, B) "sq of rectangle ("#A") * ("#B")\n"
#define test(gg) x##gg

//char message1[] = {"hello"};
//char message2[] = "hello";
//int size = sizeof(message1);
//int size_2 = sizeof(message2);
//printf("size of message1 = %d\nsize of message2 = %d\n", size, size_2);

//clock_t start, end;
//long long x;
//start = clock();
//x = int_pow_n(3, int_pow_n(8,10)-1);
//end = clock();
//printf("%lld\n%f\n", x, ((double)end - start)/CLOCKS_PER_SEC);

//100000
//#define size 2000000

//int printf(const char * __format, ...);

int sum(int count, ...){
    int s = 0;
    va_list arg1;
    va_start(arg1, count);
    for (int i =0; i < count; i++){
        s+=va_arg(arg1, int);
    }
    va_end(arg1);
    return s;
}

#define size 10


int main() {
    int *mas = malloc(sizeof(int)*size);
    fill_mas_rand(mas, size, 100);
    print_array(mas, size);
    int g = more_meet_el(mas,size);
    printf("%d\n", g);
}

