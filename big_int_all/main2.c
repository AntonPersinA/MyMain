//
// Created by anton on 27.10.23.
//

#include "test/test.h"
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <stdarg.h>
//#include <limits.h>
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "big_int/big_int.h"

#include "lib/lib.h"


void test_kar()
{
    big_int *n1 = big_int_getloop("1111000011111111000101111", 10); //11110000111111110001000100000000
    big_int *n2 = big_int_getloop("1100000010000000000001010", 10); //10100000111111110000101000000000
//    printf("n1 = ");
//    big_int_print(n1);
//    printf("n2 = ");
//    big_int_print(n2);
//    printf("\n");
//
//
//
//        printf("n1 = ");
//        big_int_print(n1);
//        printf("n2 = ");
//        big_int_print(n2);

    big_int *n4 = big_int_mult1(n1,n2);

    big_int *n3 = big_int_karatsuba_mult2(n1,n2);

//    printf("\nkar = ");
//    big_int_print(n3);
//    printf("mul = ");
//    big_int_print(n4);


//    printf("n1 = ");
//    big_int_print(n1);
//    printf("n2 = ");
//    big_int_print(n2);
//    printf("\n");


    printf("equal = %d\n", big_int_equal_sgn(n3,n4));

    big_int_free2(4, &n1, &n2, &n3, &n4);

}

int new_func()
{
    time_t start, end;

    big_int *n1 = big_int_getloop("11111011", 10);
    big_int *n2 = big_int_getloop("1111011", 10);

    start = clock();
    big_int *n3 = big_int_add1(n1, n2);
    end = clock();

    printf("time my = %f\n", (float)(end - start) / CLOCKS_PER_SEC);

    big_int_free2(3, &n1, &n2, &n3);
}



int new_func_slava()
{
    time_t start1, end1;

    big_int *n11 = big_int_getloop("11111011", 10);
    big_int *n22 = big_int_getloop("1111011", 10);

    start1 = clock();
    big_int *n33 = big_int_add1(n11, n22);
    end1 = clock();

    printf("time slava = %f\n", (float)(end1 - start1) / CLOCKS_PER_SEC);

    big_int_free2(3, &n11, &n22, &n33);
}


int new_func2()
{
    time_t start, end;

    big_int *n1 = big_int_getloop("11111011", 10);
    big_int *n2 = big_int_getloop("1111011", 10);

    start = clock();
    big_int *n3 = big_int_sub1(n1, n2);
    end = clock();

    printf("time my = %f\n", (float)(end - start) / CLOCKS_PER_SEC);

    big_int_free2(3, &n1, &n2, &n3);
}



int new_func_slava2()
{
    time_t start1, end1;

    big_int *n11 = big_int_getloop("11111011", 10);
    big_int *n22 = big_int_getloop("1111011", 10);

    start1 = clock();
//    big_int *n33 = big_int_sub(n11, n22);
    end1 = clock();

    printf("time slava = %f\n", (float)(end1 - start1) / CLOCKS_PER_SEC);

//    big_int_free2(3, &n11, &n22, &n33);
    big_int_free2(2, &n11, &n22);
}


int new_func3()
{
    time_t start, end;

    big_int *n1 = big_int_getloop("1101011", 10);
    big_int *n2 = big_int_getloop("111011", 10);

    start = clock();
    big_int_add2(n1, n2);
    end = clock();

    printf("time my = %f\n", (float)(end - start) / CLOCKS_PER_SEC);

    big_int_free2(2, &n1, &n2);
}



int new_func_slava3()
{
    time_t start1, end1;

    big_int *n11 = big_int_getloop("1101011", 10);
    big_int *n22 = big_int_getloop("111011", 10);

    start1 = clock();
//    big_int_add22(n11, n22);
    end1 = clock();

    printf("time slava = %f\n", (float)(end1 - start1) / CLOCKS_PER_SEC);

    big_int_free2(2, &n11, &n22);
}

int main()
{
    big_int *n1 = big_int_get10(345*1232);
    big_int *n2 = big_int_get10(345);
    big_int *n3 = big_int_divided(n1, n2);
    big_int_to10(n1);
    big_int_to10(n2);
    big_int_to10(n3);
//    big_int_print(n1);
//    big_int_print(n2);
//    big_int_print(n3);

    big_int_free2(3, &n1, &n2, &n3);
    return 0;
}
