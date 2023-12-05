#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../big_int/big_int.h"
#include "test.h"
#include "../lib/lib.h"

int test_all(int limit)
{

    if (!test_get())
    {
        return 0;
    }

    if (!test_get10())
    {
        return 0;
    }

    if (!test_get10loop(50))
    {
        return 0;
    }

    if (!test_get_loop())
    {
        return 0;
    }

    if (!test_equal(limit))
    {
        return 0;
    }

    if (!test_equal_sgn(limit))
    {
        return 0;
    }

    if (!test_leq())
    {
        return 0;
    }

    if (!test_meq())
    {
        return 0;
    }

    if (!test_swap1(limit))
    {
        return 0;
    }

    if (!test_swap2(limit))
    {
        return 0;
    }


    if (!test_copy())
    {
        return 0;
    }

    if (!test_add12(limit))
    {
        return 0;
    }


    if (!test_sub12(limit))
    {
        return 0;
    }

    if (!test_mult1(limit))
    {
        return 0;
    }

    if (!test_shft_l())
    {
        return 0;
    }

    if (!test_shft_r())
    {
        return 0;
    }

    if (!test_karatsuba(limit))
    {
        return 0;
    }

    if (!test_pow(limit))
    {
        return 0;
    }

    if (!test_divided(limit))
    {
        return 0;
    }

    if (!test_mod(limit))
    {
        return 0;
    }

    if (!test_dlz())
    {
        return 0;
    }

    if (!test_rnd_odd(limit))
    {
        return 0;
    }

    if (!test_pow_mod(limit))
    {
        return 0;
    }

    if (!test_miller_rabin(limit))
    {
        return 0;
    }

    return 1;
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
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int2\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("000000000000001");
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get big_int3\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("-00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int4\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("-0");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int5\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("+00000000000000");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int6\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("+0");
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get big_int7\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("-00000000000001");
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get big_int8\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("100000001");
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get big_int9\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get("-100000001");
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get big_int10\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    return 1;
}


int test_get10()
{
    {
        big_int *n1 = big_int_get10(0);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get10 big_int1\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get10(+0);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get10 big_int2\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get10(1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get10 big_int3\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get10(-0);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get10 big_int4\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }


    {
        big_int *n1 = big_int_get10(-1);
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get10 big_int5\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get10(257);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get10 big_int6\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_get10(-257);
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get10 big_int7\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    return 1;
}


int test_get10loop(int a) //Имеетеся в виду что тест переборный
{
    big_int *zero = big_int_get("0");
    big_int *one = big_int_get("1");
    for (int i = 0; i <= a; ++i)
    {
        big_int *n1 = big_int_get10(i);
        if (!big_int_equal_sgn(zero, n1))
        {
            printf("error test_get10loop\n");
            big_int_to10(zero);
            big_int_to10(n1);
            big_int_free2(3, &zero, &n1, &one);
            return 0;
        }
        big_int_free(&n1);
        big_int_add2(zero, one);
    }


    for (int i = 0; i >= a; --i)
    {
        big_int *n1 = big_int_get10(i);
        if (!big_int_equal_sgn(zero, n1))
        {
            printf("error test_get10loop\n");
            big_int_to10(zero);
            big_int_to10(n1);
            big_int_free2(3, &zero, &n1, &one);
            return 0;
        }
        big_int_free(&n1);
        big_int_sub2(zero, one);
    }

    big_int_free(&zero);
    big_int_free(&one);
    return 1;
}


int test_get_loop()
{
    {
        big_int *n1 = big_int_getloop("0", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int1\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("0", 100);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int2\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("00000000000000", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int3\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("00000000000000", 10);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int4\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("000000000000001", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int5\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("00000001", 2);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get_loop big_int6\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("+00000001", 2);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get_loop big_int7\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("-00000001", 2);
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get_loop big_int8\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("-00000000000000", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int9\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("-0", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int10\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("+00000000000000", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int11\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("+0", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 0 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int12\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("-00000000000001", 1);
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->length == 1))
        {
            printf("error test_get_loop big_int13\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("100000001", 1);
        if (!(n1->sign == '+' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get_loop big_int14\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    {
        big_int *n1 = big_int_getloop("-100000001", 1);
        if (!(n1->sign == '-' &&
              n1->number[0] == 1 &&
              n1->number[1] == 1 &&
              n1->length == 2))
        {
            printf("error test_get_loop big_int15\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    return 1;
}


int test_equal(int limit)
{
    long long int a258 = 258 * 2;
    for (int a = -limit; a <= limit; ++a)
    {
        for (int b = -limit; b <= limit; ++b)
        {
            int a_1 = (a * 177 * limit) % a258 - 258 >= 0 ? (a * 177 * limit) % a258 - 258: - ((a * 177 * limit) % a258 - 258);
            int b_1 = (b * 177 * limit) % a258 - 258 >= 0 ? (b * 177 * limit) % a258 - 258 : - ((b * 177 * limit) % a258 - 258);
            big_int *n1 = big_int_get10((a * 177 * limit) % a258 - 258);
            big_int *n2 = big_int_get10((b * 177 * limit) % a258 - 258);

            if ((a_1 == b_1) != (big_int_equal(n1,n2)))
            {
                printf("error test_equal big_int\n");

                big_int_free(&n1);
                big_int_free(&n2);

                return 0;
            }

            big_int_free(&n1);
            big_int_free(&n2);
        }
    }
    return 1;
}


int test_equal_sgn(int limit)
{
    {
        big_int *n1 = big_int_get("1");
        big_int *n2 = big_int_get("-1");

        if ((1 == -1) != (big_int_equal_sgn(n1,n2)))
        {
            printf("error test_equal_sgn big_int1\n");
            big_int_free(&n1);
            big_int_free(&n2);

            return 0;
        }

        big_int_free(&n1);
        big_int_free(&n2);
    }
    long long int a258 = 258 * 2;
    for (int a = -limit; a <= limit; ++a)
    {
        for (int b = -limit; b <= limit; ++b)
        {
            long long int a_1 = (a * 3 * limit) % a258 - 258;
            long long int b_1 = (b * 3 * limit) % a258 - 258;
            big_int *n1 = big_int_get10(a_1);
            big_int *n2 = big_int_get10(b_1);

            if ((a_1 == b_1) != (big_int_equal_sgn(n1,n2)))
            {
                printf("error test_equal_sgn big_int2\n");
                big_int_free(&n1);
                big_int_free(&n2);

                return 0;
            }

            big_int_free(&n1);
            big_int_free(&n2);
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

                big_int_free(&n1);
                big_int_free(&n111);
                big_int_free(&n2);
                big_int_free(&n222);

                continue;
            }

            free(str1);
            free(str111);
            free(str2);
            free(str222);

            big_int_free(&n1);
            big_int_free(&n111);
            big_int_free(&n2);
            big_int_free(&n222);

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

                big_int_free(&n1);
                big_int_free(&n111);
                big_int_free(&n2);
                big_int_free(&n222);

                continue;
            }

            free(str1);
            free(str111);
            free(str2);
            free(str222);

            big_int_free(&n1);
            big_int_free(&n111);
            big_int_free(&n2);
            big_int_free(&n222);

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
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    {
        big_int *n1 = big_int_get("111111111111111111");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int2\n");
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    {
        big_int *n1 = big_int_get("00000000000000000000000");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int3\n");
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    {
        big_int *n1 = big_int_get("-0");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int4\n");
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    {
        big_int *n1 = big_int_get("-111111111111111111");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int5\n");
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    {
        big_int *n1 = big_int_get("-00000000000000000000000");
        big_int *n2 = big_int_copy(n1);
        if (!big_int_equal_sgn(n1,n2))
        {
            printf("error test_copy big_int6\n");
            big_int_free(&n1);
            big_int_free(&n2);
            return 0;
        }
        big_int_free(&n1);
        big_int_free(&n2);
    }

    return 1;
}


int test_add12(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 300001;
            long long int j = (291 * j1 * a) % 300001;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str(i + j);
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);
            big_int *n6 = big_int_copy(n1);
            big_int *n5 = big_int_copy(n2);
            big_int *n4 = big_int_add1(n1, n2);


            if (!big_int_equal_sgn(n2, n5))
            {
                printf("error change n5, test_add12, redo\n");
                return 0;
            }


            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_add1\n");
                printf("i = %lld, j = %lld\n", i, j);
                big_int_print(n1);
                big_int_print(n2);
                big_int_print(n4);
                big_int_print(n3);
                big_int_free2(6, &n1, &n2, &n3, &n4, &n5, &n6);
                free(str1);
                free(str2);
                free(str3);
                return 0;
            }
            if (!big_int_equal_sgn(n1, n6))
            {
                printf("error change n6, test_add12, redo\n");
                return 0;
            }
            big_int_add2(n1, n2);
            if (!big_int_equal_sgn(n3, n1))
            {
                printf("error test_add2\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n1);
                big_int_free2(6, &n1, &n2, &n3, &n4, &n5, &n6);
                free(str1);
                free(str2);
                free(str3);
                return 0;
            }
            big_int_free2(6, &n1, &n2, &n3, &n4, &n5, &n6);
            free(str1);
            free(str2);
            free(str3);
        }
    }
    return 1;
}


int test_sub12(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 300001;
            long long int j = (291 * j1 * a) % 300001;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str(i - j);
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_sub1(n1, n2);
            big_int_sub2(n1, n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_sub1\n");
                big_int_free2(4, &n1, &n2, &n3, &n4);
                free(str1);
                free(str2);
                free(str3);
                return 0;
            }
            if (!big_int_equal_sgn(n3, n1))
            {
                printf("error test_sub2\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n1);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                free(str1);
                free(str2);
                free(str3);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_mult1(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 300001;
            long long int j = (291 * j1 * a) % 300001;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str(i * j);
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_mult1(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_mult1\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_shft_l()
{
    for (int i = -10310; i < 10310; ++i)
    {
        for(int j = 0; j < 30; ++j)
        {
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            big_int *n1 = big_int_get(str1);
            long long int ppp = 1;
            for (int k = 0; k < j; ++k)
            {
                ppp *= 2;
            }
            char *str3 = bin_str((long long int)((long long int)i*(long long int)ppp));
            big_int *n3 = big_int_get(str3);

            big_int_shft_l2(n1, j);
            big_int_dlz(n1);
            big_int_dlz(n3);
            if (!big_int_equal_sgn(n1, n3))
            {
                printf("error test_shft_l = %d\n", j);
                big_int_print(n1);
                big_int_print(n3);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(2, &n1, &n3);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(2, &n1, &n3);
        }
    }
    return 1;
}


int test_shft_r()
{
    for (int i = -10310; i < 10310; ++i)
    {
        for(int j = 0; j < 30; ++j)
        {
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            big_int *n1 = big_int_get(str1);
            long long int ppp = 1;
            for (int k = 0; k < j; ++k)
            {
                ppp *= 2;
            }
            char *str3 = bin_str((long long int)((long long int)i/(long long int)ppp));
            big_int *n3 = big_int_get(str3);

            big_int_shft_r2(n1, j);
            big_int_dlz(n3);
            if (!big_int_equal_sgn(n1, n3))
            {
                printf("error test_shft_r = %d\n", j);
                printf("error i = %d\n", i);
                big_int *pri = big_int_get10(i);
                big_int_print(pri);
                big_int_free(&pri);
                big_int_print(n1);
                big_int_print(n3);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(2, &n1, &n3);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(2, &n1, &n3);
        }
    }
    return 1;
}


int test_karatsuba(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 300001;
            long long int j = (291 * j1 * a) % 300001;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str(i * j);
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_karatsuba_mult2(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_karatsuba\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_pow(int a)
{
    for (int i1 = 0; i1 < a; ++i1)
    {
        for (int j1 = 0; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 36 - 18;
            long long int j = (291 * j1 * a) % 15;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str((long long int)powl(i, j));
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_pow(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_pow\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_divided(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (291 * i1 * a) % 1234567;
            long long int j = (291 * j1 * a) % 1234 + (!((291 * j1 * a) % 1234));
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str((long long int)(i/j));
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_divided(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_divided\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_mod(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = (11 * i1 * a) % 123456567;
            long long int j = (j1 * a) % 12368 + (!(((j1 * a) % 12368)));
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str((long long int)(i%j));
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_mod(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_mod\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_divided_loop(int a)
{
    for (int i1 = -a; i1 < a; ++i1)
    {
        for (int j1 = -a; j1 < a; ++j1)
        {
            long long int i = i1;
            long long int j = j1 + !j1;
            char *str1 = bin_str(i);
            char *str2 = bin_str(j);
            char *str3 = bin_str((long long int)(i/j));
            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *n3 = big_int_get(str3);

            big_int *n4 = big_int_divided(n1,n2);
            if (!big_int_equal_sgn(n3, n4))
            {
                printf("error test_divided_loop\n");
                printf("%lld %lld\n", i, j);
                big_int_print(n3);
                big_int_print(n4);
                free(str1);
                free(str2);
                free(str3);
                big_int_free2(4, &n1, &n2, &n3, &n4);
                return 0;
            }
            free(str1);
            free(str2);
            free(str3);
            big_int_free2(4, &n1, &n2, &n3, &n4);
        }
    }
    return 1;
}


int test_leq()
{
    for (int i = -10; i < 11; ++i)
    {
        for (int j = -10; j < 11; ++j)
        {
            big_int *n1 = big_int_get10(i);
            big_int *n2 = big_int_get10(j);

            if (big_int_leq(n1, n2) != (i <= j))
            {
                printf("error test_leq1 = %d\n", big_int_leq(n1, n2));
                big_int_free2(2, &n1, &n2);
                return 0;
            }
            big_int_free2(2, &n1, &n2);
        }
    }

    {
        big_int *n1 = big_int_get10(-123456789);
        big_int *n2 = big_int_get10(12345);
        if (big_int_leq(n1, n2) != (-123456789 <= 12345))
        {
            printf("error test_leq2\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(123456789);
        big_int *n2 = big_int_get10(12345);
        if (big_int_leq(n1, n2) != (123456789 <= 12345))
        {
            printf("error test_leq3\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-123456789);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_leq(n1, n2) != (-123456789 <= -12345))
        {
            printf("error test_leq4\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(123456789);
        big_int *n2 = big_int_get10(12345);
        if (big_int_leq(n1, n2) != (123456789 <= 12345))
        {
            printf("error test_leq5\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(123456789);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_leq(n1, n2) != (123456789 <= -12345))
        {
            printf("error test_leq6\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(-123456789);
        if (big_int_leq(n1, n2) != (12345 <= -123456789))
        {
            printf("error test_leq7\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(123456789);
        if (big_int_leq(n1, n2) != (12345 <= 123456789))
        {
            printf("error test_leq8\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(123456789);
        if (big_int_leq(n1, n2) != (-12345 <= 123456789))
        {
            printf("error test_leq9\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(-123456789);
        if (big_int_leq(n1, n2) != (-12345 <= -123456789))
        {
            printf("error test_leq10\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }


    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_leq(n1, n2) != (12345 <= -12345))
        {
            printf("error test_leq11\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(12345);
        if (big_int_leq(n1, n2) != (12345 <= 12345))
        {
            printf("error test_leq12\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(12345);
        if (big_int_leq(n1, n2) != (-12345 <= 12345))
        {
            printf("error test_leq13\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_leq(n1, n2) != (-12345 <= -12345))
        {
            printf("error test_leq14\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    return 1;
}


int test_meq()
{
    for (int i = -10; i < 11; ++i)
    {
        for (int j = -10; j < 11; ++j)
        {
            big_int *n1 = big_int_get10(i);
            big_int *n2 = big_int_get10(j);

            if (big_int_meq(n1, n2) != (i >= j))
            {
                printf("error test_meq1 = %d\n", big_int_leq(n1, n2));
                big_int_free2(2, &n1, &n2);
                return 0;
            }
            big_int_free2(2, &n1, &n2);
        }
    }

    {
        big_int *n1 = big_int_get10(-123456789);
        big_int *n2 = big_int_get10(12345);
        if (big_int_meq(n1, n2) != (-123456789 >= 12345))
        {
            printf("error test_meq2\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(123456789);
        big_int *n2 = big_int_get10(12345);
        if (big_int_meq(n1, n2) != (123456789 >= 12345))
        {
            printf("error test_meq3\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-123456789);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_meq(n1, n2) != (-123456789 >= -12345))
        {
            printf("error test_meq4\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(123456789);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_meq(n1, n2) != (123456789 >= -12345))
        {
            printf("error test_meq6\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(-123456789);
        if (big_int_meq(n1, n2) != (12345 >= -123456789))
        {
            printf("error test_meq7\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(123456789);
        if (big_int_meq(n1, n2) != (12345 >= 123456789))
        {
            printf("error test_meq8\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(123456789);
        if (big_int_meq(n1, n2) != (-12345 >= 123456789))
        {
            printf("error test_meq9\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(-123456789);
        if (big_int_meq(n1, n2) != (-12345 >= -123456789))
        {
            printf("error test_meq10\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_meq(n1, n2) != (12345 >= -12345))
        {
            printf("error test_meq11\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(12345);
        big_int *n2 = big_int_get10(12345);
        if (big_int_meq(n1, n2) != (12345 >= 12345))
        {
            printf("error test_meq12\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(12345);
        if (big_int_meq(n1, n2) != (-12345 >= 12345))
        {
            printf("error test_meq13\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    {
        big_int *n1 = big_int_get10(-12345);
        big_int *n2 = big_int_get10(-12345);
        if (big_int_meq(n1, n2) != (-12345 >= -12345))
        {
            printf("error test_meq14\n");
            big_int_free2(2, &n1, &n2);
            return 0;
        }
        big_int_free2(2, &n1, &n2);
    }
    return 1;
}


int test_dlz()
{
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(10, sizeof(unsigned char));
        n1->length = 10;
        n1->sign = '-';
        big_int_dlz(n1);
        if (n1->length != 1 && n1->number[0] != 0)
        {
            printf("error test_dlz1\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(10, sizeof(unsigned char));
        n1->length = 10;
        n1->sign = '-';
        n1->number[1] = 1;
        big_int_dlz(n1);
        if (n1->length != 2 && n1->number[0] != 0 && n1->number[1] != 1)
        {
            printf("error test_dlz2\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(10, sizeof(unsigned char));
        n1->length = 10;
        n1->sign = '-';
        n1->number[0] = 1;
        big_int_dlz(n1);
        if (n1->length != 1 && n1->number[0] != 1)
        {
            printf("error test_dlz3\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(1, sizeof(unsigned char));
        n1->length = 1;
        n1->sign = '-';
        big_int_dlz(n1);
        if (n1->length != 1 && n1->number[0] != 0)
        {
            printf("error test_dlz4\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(2, sizeof(unsigned char));
        n1->length = 2;
        n1->sign = '-';
        n1->number[1] = 1;
        big_int_dlz(n1);
        if (n1->length != 2 && n1->number[0] != 0 && n1->number[1] != 1)
        {
            printf("error test_dlz5\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }
    {
        big_int *n1 = calloc(1, sizeof(big_int));
        n1->number = calloc(1, sizeof(unsigned char));
        n1->length = 1;
        n1->sign = '-';
        n1->number[0] = 1;
        big_int_dlz(n1);
        if (n1->length != 1 && n1->number[0] != 1)
        {
            printf("error test_dlz6\n");
            big_int_free(&n1);
            return 0;
        }
        big_int_free(&n1);
    }

    return 1;
}


int test_rnd_odd(int limit)
{
    for (int i = 1; i <= limit; ++i)
    {
        big_int *n1 = big_int_rnd_odd(i);

        if (n1->number[0] % 2 == 0)
        {
            printf("error test_rnd_odd\n");
            big_int_free2(1, &n1);
            return 0;
        }
        big_int_free2(1, &n1);
    }
    return 1;
}


int test_pow_mod(int limit)
{
    for (int int_a = 1; int_a < 4; ++int_a)
    {
        for (int int_pow = 1; int_pow < 20; ++int_pow)
        {
            for (int int_mod = 1; int_mod < limit; ++int_mod)
            {
                big_int *a = big_int_get10(int_a);
                big_int *pow1 = big_int_get10(int_pow);
                big_int *modul = big_int_get10(int_mod);

                big_int *ans = big_int_get10((int)pow(int_a, int_pow) % int_mod);
                big_int *my_res = big_int_pow_mod(a, pow1, modul);

                if (!big_int_equal_sgn(ans, my_res))
                {
                    printf("test_pow_mod error\n");
                    printf("a = %d\npow = %d\nmod = %d\n", int_a, int_pow, int_mod);
                    printf("ans = %d\n",(int)pow(int_a, int_pow) % int_mod);
                    big_int_print(my_res);
                    big_int_free2(5, &a, &pow1, &modul, &ans, &my_res);
                    return 0;
                }
                big_int_free2(5, &a, &pow1, &modul, &ans, &my_res);

            }
        }
    }
    return 1;
}

int test_miller_rabin(int limit) //Следует выставлять хотя бы 20
{
    for (int i = 0; i < limit; ++i)
    {
        big_int *n1 = big_int_rnd(i%3 + !(i%3));
        if (n1->number[0] == 1 && n1->length == 1)
        {
            big_int_free(&n1);
            continue;
        }

        char pr_test = 1;
        char pr_miller = big_int_miller_rabin(n1, 10 + limit);
        big_int *zero = big_int_get("0");
        big_int *one = big_int_get("1");
        big_int *two = big_int_get("10");
        for (;;)
        {
            if (big_int_meq(two, n1))
            {
                pr_test = 1;
                break;
            }
            big_int *mod = big_int_mod(n1, two);
            if (!big_int_equal_sgn(mod, zero))
            {
                big_int_free(&mod);
                big_int_add2(two, one);
            }
            else
            {
                pr_test = 0;
                big_int_free(&mod);
                break;
            }
        }
        if (pr_test != pr_miller)
        {
            big_int_to10(n1);
            printf("miller = %d\n", pr_miller);
            printf("test = %d\n", pr_test);
            big_int_free2(4, &one, &zero, &two, &n1);
            return 0;
        }
        big_int_free2(4, &one, &zero, &two, &n1);
    }
    return 1;
}



int test_get_prime(int limit)
{
    for (int i = 0; i < limit; ++i)
    {
//        printf("fefefef = %d\n", i%4 + !(i%4));
        big_int *n1 = big_int_get_prime(1, 10);
        if (n1->number[0] <= 1 && n1->length == 1)
        {
            printf("test_get_prime error1\n");
            big_int_free(&n1);
            return 0;
        }
        char pr_test = 1;
        big_int *zero = big_int_get("0");
        big_int *one = big_int_get("1");
        big_int *square = big_int_get("10");
        for (;;)
        {
            if (big_int_meq(square, n1))
            {
                pr_test = 1;
                break;
            }
            big_int *mod = big_int_mod(n1, square);
            if (!big_int_equal_sgn(mod, zero))
            {
                big_int_free(&mod);
                big_int_add2(square, one);
            }
            else
            {
                big_int_to10(n1);
                big_int_to10(square);
                pr_test = 0;
                big_int_free(&mod);
                break;
            }
        }
        if (pr_test != 1)
        {
            printf("test_get_prime error2\n");
            big_int_free2(4, &one, &zero, &square, &n1);
            return 0;
        }
        big_int_free2(4, &one, &zero, &square, &n1);
    }
    return 1;
}