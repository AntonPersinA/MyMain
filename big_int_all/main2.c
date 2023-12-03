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
    for (int d = 0; d < 18; ++d)
    {
        for (int x = 0; x < 18; ++x)
        {
            for (int y = 0; y < 18; ++y)
            {
                for (int z = 1; z < 257; ++z)
                {
                    big_int *n1 = big_int_get10(53); //53
                    big_int *pow = big_int_get10(256*256*256*x + 256*256*y + d*255 + z); //7523558
                    big_int *modul = big_int_get10(1617); //161

                    big_int *res1 = big_int_rl_mod_pow2(n1, pow, modul);
                    big_int *res2 = big_int_pow_mod_fast(n1, pow, modul);
//                    big_int_to10(res1);
//                    big_int_to10(res2);

                    if (!big_int_equal_sgn(res1, res2))
                    {
                        return 0;
                    }
//                    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                    big_int_free2(5, &n1, &pow, &modul, &res1, &res2);
                }
            }
        }
    }

    printf("\n\n\n\n\n\nYYYYYYYYYYYYYYYYYYYYYRRRRRRRRRRRRRRRRRRAAAAAAAAAAAAAAAAAAAAAAAAA\n");
}


int pow_mod_func()
{
    time_t start, end;

    big_int *n1 = big_int_get10((long long int)234); //53
    big_int *pow = big_int_getloop("1001", 22222); //7523558
    big_int *modul = big_int_get10(65537); //161

    start = clock();
    big_int *res1 = big_int_rl_mod_pow2(n1, pow, modul);
    end = clock();
    printf("powmod slava = %f\n", (float)(end - start)/(float)(CLOCKS_PER_SEC));

    start = clock();
    big_int *res2 = big_int_pow_mod_fast(n1, pow, modul);
    end = clock();
    printf("pow_mod_fast = %f\n", (float)(end - start)/(float)(CLOCKS_PER_SEC));

    big_int_to10(res1);
    big_int_to10(res2);


    big_int_free2(4, &n1, &pow, &modul, &res2);
    big_int_free(&res1);
    return 0;
}




int main()
{
    return 0;
}








