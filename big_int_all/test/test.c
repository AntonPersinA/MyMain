#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../big_int/big_int.h"
#include "test.h"
#include "../lib/lib.h"

void test_all(int limit)
{
    int s = -1000;

    int test_get();

    int test_equal(int limit);

    int test_equal_sgn(int limit);

    int test_swap1(int limit);

    int test_swap2(int limit);

    int test_copy();
}


int test_get()
{
    {
        big_int *n1 = big_int_get("0");
        if (!(n1->sign == '+' &&
            n1->number[0] == 0 &&
            n1->length == 1))
        {
            printf("error test_get big_int1\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int2\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("000000000000001");
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get big_int3\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("-00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int4\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("-0");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int5\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("+00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int6\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("+0");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int7\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("-00000000000001");
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get big_int8\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("100000001");
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get big_int9\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }

    {
        big_int *n1 = big_int_get("-100000001");
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get big_int10\n");
            big_int_free(n1);
            return 0;
        }
        big_int_free(n1);
    }
}


int test_equal(int limit)
{
    for (int a = -limit; a <= limit; ++a)
    {
        for (int b = -limit; b <= limit; ++b)
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


int test_equal_sgn(int limit)
{
    for (int a = -limit; a <= limit; ++a)
    {
        for (int b = -limit; b <= limit; ++b)
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


int test_swap1(int limit)
{
    for (int a = -limit; a <= limit; ++a)
    {
        for (int b = -limit; b <= limit; ++b)
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


int test_swap2(int limit)
{
    for (int a = -limit; a < limit; ++a)
    {
        for (int b = -limit; b < limit; ++b)
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


int test_copy()
{
    {
        big_int *n1 = big_int_get("0");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int1\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }

    {
        big_int *n1 = big_int_get("111111111111111111");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int2\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }

    {
        big_int *n1 = big_int_get("00000000000000000000000");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int3\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }

    {
        big_int *n1 = big_int_get("-0");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int4\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }

    {
        big_int *n1 = big_int_get("-111111111111111111");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int5\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }

    {
        big_int *n1 = big_int_get("-00000000000000000000000");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int6\n");
            big_int_free(n1);
            big_int_free(n2);
            return 0;
        }
        big_int_free(n1);
        big_int_free(n2);
    }
}


int test_add12(int a)
{
    for (int i = -a; i < a; ++i)
    {
        for(int j = -a; j < a; ++j)
        {
            big_int *n1 = big_int_get(bin_str(i));
            big_int *n2 = big_int_get(bin_str(j));
            big_int *n3 = big_int_get(bin_str(i + j));

            big_int *n4 = big_int_add1(n1, n2);
            big_int_add2(n1, n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_add1\n");
                big_int_free2(4, n1, n2, n3, n4);
                return 0;
            }
            if (!big_int_equal_sgn(n3, n1))
            {
                printf("error test_add2\n");
                printf("%d %d\n", i, j);
                big_int_print(n3);
                big_int_print(n1);
                big_int_free2(4, n1, n2, n3, n4);
                return 0;
            }
        }
    }
    return 1;
}


int test_sub12(int a)
{
    for (int i = -a; i < a; ++i)
    {
        for(int j = -a; j < a; ++j)
        {
            big_int *n1 = big_int_get(bin_str(i));
            big_int *n2 = big_int_get(bin_str(j));
            big_int *n3 = big_int_get(bin_str(i - j));

            big_int *n4 = big_int_sub1(n1, n2);
            big_int_sub2(n1, n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_sub1\n");
                big_int_free2(4, n1, n2, n3, n4);
                return 0;
            }
            if (!big_int_equal_sgn(n3, n1))
            {
                printf("error test_sub2\n");
                printf("%d %d\n", i, j);
                big_int_print(n3);
                big_int_print(n1);
                big_int_free2(4, n1, n2, n3, n4);
                return 0;
            }
        }
    }
    return 1;
}


int test_mult1(int a)
{
    for (int i = -a; i < a; ++i)
    {
        for(int j = -a; j < a; ++j)
        {
            big_int *n1 = big_int_get(bin_str(i));
            big_int *n2 = big_int_get(bin_str(j));
            big_int *n3 = big_int_get(bin_str(i*j));

            big_int *n4 = big_int_mult1(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_mult1\n");
                printf("%d %d\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                big_int_free2(4, n1, n2, n3, n4);
                return 0;
            }
        }
    }
    return 1;
}

int test_shft()
{
    for (int i = -1030; i < 1030; ++i)
    {
        for(int j = 0; j < 30; ++j)
        {
            big_int *n1 = big_int_get(bin_str(i));
            big_int *n2 = big_int_get(bin_str(i));
            long long int ppp = 1;
            for (int k = 0; k < j; ++k)
            {
                ppp *= 2;
            }
            big_int *n3 = big_int_get(bin_str((i*ppp)));

            big_int_shft_l2(n1, j);
            if (!big_int_equal_sgn(n1, n3))
            {
                printf("error test_shft = %lld\n", ppp*i);
                printf("00000000 00000000 ");
                big_int_print(n2);
                printf("00000000 ");
                big_int_print(n1);
                big_int_print(n3);
                big_int_free2(3, n1, n2, n3);
                return 0;
            }
        }
    }
    return 1;
}