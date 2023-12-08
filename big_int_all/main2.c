//
// Created by anton on 27.10.23.
//

//#include <limits.h>
//#include <math.h>
//#include <stdarg.h>
//#include <stdlib.h>
    #include <stdio.h>
//#include <string.h>
    #include <time.h>

    #include "big_int/big_int.h"
//#include "lib/lib.h"
    #include "test/test.h"

int while_true_func()
{
    int i = 1;
    while(test_all(i))
    {
        printf("i = %d\n", i);
        ++i;
    }
}

int time_test()
{
    clock_t start, end;
    big_int *n1 = big_int_getloop("100100001101", 5000);
    big_int *n2 = big_int_getloop("100100001101", 5000);

    big_int *num1 = big_int_karatsuba_mult2(n1,n2);
    big_int *num2 = big_int_karatsuba_mult2(n1,n2);

    start = clock();


    for (int i = 0; i < 200000; ++i)
    {
        big_int *n3 = big_int_add1(num1, num2);

        big_int_free(&n3);
    }

    end = clock();

    printf("time last = %f\n", (float)(end - start)/CLOCKS_PER_SEC);

    big_int_free2(2, &n1, &n2);
    big_int_free2(2, &num1, &num2);
}

int main()
{
    while_true_func();
//    time_test();
    return 0;
}
























