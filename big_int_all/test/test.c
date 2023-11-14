#include <stdlib.h>
#include <stdio.h>

#include "../big_int/big_int.h"
#include "test.h"
#include "../lib/lib.h"


int test_equal()
{
    for (int a = - 1024 - 2; a < 1024 + 2; ++a)
    {
        for (int b = - 1024 - 2; b < 1024 + 2; ++b)
        {
            char *str1 = bin_str(a);
            char *str2 = bin_str(b);

            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);

            int a_1 = a >= 0 ? a : - a;
            int b_1 = b >= 0 ? b : - b;

            if ((a_1 == b_1) != (big_int_equal(n1,n2)))
            {
                printf("error test_equal big_int\n");

                free(str1);
                free(str2);
                big_int_free(n1);
                big_int_free(n2);

                return 0;
            }

            free(str1);
            free(str2);
            big_int_free(n1);
            big_int_free(n2);
        }
    }
    return 1;
}


int test_equal_sgn()
{
    for (int a = - 1024 - 2; a < 1024 + 2; ++a)
    {
        for (int b = - 1024 - 2; b < 1024 + 2; ++b)
        {
            char *str1 = bin_str(a);
            char *str2 = bin_str(b);

            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);

            if ((a == b) != (big_int_equal_sgn(n1,n2)))
            {
                printf("error test_equal_sgn big_int\n");

                free(str1);
                free(str2);
                big_int_free(n1);
                big_int_free(n2);

                return 0;
            }

            free(str1);
            free(str2);
            big_int_free(n1);
            big_int_free(n2);
        }
    }
    return 1;
}


int test_swap1()
{
    for (int a = - 1024 - 2; a < 1024 + 2; ++a)
    {
        for (int b = - 1024 - 2; b < 1024 + 2; ++b)
        {
            char *str1 = bin_str(a);
            char *str111 = bin_str(a);
            char *str2 = bin_str(b);
            char *str222 = bin_str(b);

            big_int *n1 = big_int_get(str1);
            big_int *n111 = big_int_get(str111);
            big_int *n2 = big_int_get(str2);
            big_int *n222 = big_int_get(str222);

            big_int_swap(n1,n2);

            if (big_int_equal_sgn(n1,n222) && big_int_equal_sgn(n2,n111))
            {
                free(str1);
                free(str111);
                free(str2);
                free(str222);

                big_int_free(n1);
                big_int_free(n111);
                big_int_free(n2);
                big_int_free(n222);

                continue;
            }

            free(str1);
            free(str111);
            free(str2);
            free(str222);

            big_int_free(n1);
            big_int_free(n111);
            big_int_free(n2);
            big_int_free(n222);

            printf("error test_swap1 big_int\n");
            return 0;
        }
    }
    return 1;
}


int test_swap2()
{
    for (int a = - 1024 - 2; a < 1024 + 2; ++a)
    {
        for (int b = - 1024 - 2; b < 1024 + 2; ++b)
        {
            char *str1 = bin_str(a);
            char *str111 = bin_str(a);
            char *str2 = bin_str(b);
            char *str222 = bin_str(b);

            big_int *n1 = big_int_get(str1);
            big_int *n111 = big_int_get(str111);
            big_int *n2 = big_int_get(str2);
            big_int *n222 = big_int_get(str222);

            big_int_swap2(n1,n2);

            if (big_int_equal_sgn(n1,n222) && big_int_equal_sgn(n2,n111))
            {
                free(str1);
                free(str111);
                free(str2);
                free(str222);

                big_int_free(n1);
                big_int_free(n111);
                big_int_free(n2);
                big_int_free(n222);

                continue;
            }

            free(str1);
            free(str111);
            free(str2);
            free(str222);

            big_int_free(n1);
            big_int_free(n111);
            big_int_free(n2);
            big_int_free(n222);

            printf("error test_swap2 big_int\n");
            return 0;
        }
    }
    return 1;
}