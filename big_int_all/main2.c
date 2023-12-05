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


int f()
{
    big_int *n1 = big_int_get("1");
    big_int *n2 = big_int_get("10");
    for (int len = 1000; len < 1020; ++len)
    {
        for (int i = 1; i < 100; ++i)
        {
            big_int *rnd = big_int_rnd_odd(len);
            big_int *ost = big_int_mod(rnd, n2);
            if (!big_int_equal(n1, ost))
            {
                printf("((((((\n");
                printf("rnd = ");
                big_int_print(rnd);
                printf("n1 = ");
                big_int_print(n1);
                printf("ost = ");
                big_int_print(ost);
                printf("bool = %d\n", !big_int_equal(n1, ost));

                big_int_free2(4, &ost, &rnd, &n1, &n2);
                return 0;
            }
            big_int_free2(2, &ost, &rnd);
        }
    }
    big_int_free2(2, &n1, &n2);
}


int g()
{
    int i = 1;
    while(test_pow_mod(i))
    {
        if (i % 10 == 0)
        {
            printf("i = %d\n", i);
        }
        ++i;
    }
    return 0;
}


int main()
{
    test_all(2);
    return 0;
}
























