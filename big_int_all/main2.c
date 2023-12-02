//
// Created by anton on 27.10.23.
//

//#include <limits.h>
//#include <math.h>
//#include <stdarg.h>
#include <stdlib.h>
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


int test()
{
    for (int x = 0; x < 10; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            for (int z = 1; z < 10; ++z)
            {
                big_int *n1 = big_int_get10(53); //53
                big_int *pow = big_int_get10(256*256*256*x + 256*256*y + z); //7523558
                big_int *modul = big_int_get10(1617); //161

                big_int *res1 = big_int_pow_mod(n1, pow, modul);
                big_int *res2 = big_int_pow_mod_fast(n1, pow, modul);
                big_int_to10(res1);
                big_int_to10(res2);

                if (!big_int_equal_sgn(res1, res2))
                {
                    return 0;
                }
                printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                big_int_free2(5, &n1, &pow, &modul, &res1, &res2);
            }
        }
    }
}
int main()
{

    test();

    big_int *n1 = big_int_get10(3); //53
    big_int *pow = big_int_get10(3); //7523558
    big_int *modul = big_int_get10(1617); //161

    big_int *res1 = big_int_pow_mod(n1, pow, modul);
    big_int *res2 = big_int_pow_mod_fast(n1, pow, modul);
    big_int_to10(res1);
    big_int_to10(res2);



//    big_int *test = big_int_get10(81);
//    big_int *test15 = big_int_get10(15);
//    big_int *otv = big_int_mod(test, test15);
//
//    big_int_to10(otv);


//    big_int_free2(5, &n1, &pow, &modul, &res1, &res2);
    big_int_free2(5, &n1, &pow, &modul, &res1, &res2);
    return 0;
}








