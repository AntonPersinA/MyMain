#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_int.h"

big_int *big_int_get(char *bin_number)
{
    int bit_len = strlen(bin_number);
    char sign_bin = 0;
    big_int *res = (big_int *) calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }

    if (*bin_number == '-')
    {
        sign_bin = 1;
        res->sign = '-';
    } else { res->sign = '+'; }
    if (*bin_number == '+') {
        sign_bin = 1;
    }
    res->length = (bit_len + 7 - sign_bin) >> 3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }

    for (int i = 0; i < bit_len - sign_bin; ++i)
    {
        res->number[i / 8] += (bin_number[bit_len - i - 1] - '0') << (i % 8);
//        printf("%d", (bin_number[bit_len - i - 1] - '0'));
    }
//    printf("\n\n\n");
//    big_int_dlz(res);
    return res;
}


void big_int_print(big_int *number)
{
    putchar(number->sign);
    for (int i = number->length - 1; i >= 0; --i)
    {
        int bit = 128;
        for (int j = 7; j >= 0; --j)
        {
            printf("%d", (bit & (number->number[i * sizeof(number->number[0])])) != 0);
            bit >>= 1;
        }
        printf(" ");
    }
    printf("\n");
}


void big_int_dlz(big_int *n)
{
    unsigned int i = n->length - 1;
    while ((i > 0) && (n->number[i] == 0))
    {
        --i;
    }
    if (i != n->length - 1)
    {
        n->length = i + 1;
        n->number = realloc(n->number, n->length);
        if (n->number == NULL)
        {
            printf("memory error in big_int_dlz\n");
            return;
        }
    }
}


char big_int_equal(big_int *n1, big_int *n2)
{
    if (n1->length != n2->length)
    {
        return 0;
    }
    for (int i = 0; i < n1->length; ++i)
    {
        if (n1->number[i] != n2->number[i])
        {
            return 0;
        }
    }
    return 1;
}


char big_int_equal_sgn(big_int *n1, big_int *n2)
{
    if (n1->length != n2->length || n1->sign != n2->sign)
    {
        return 0;
    }

    for (int i = 0; i < n1->length; ++i)
    {
        if (n1->number[i] != n2->number[i])
        {
            return 0;
        }
    }
    return 1;
}


void big_int_free(big_int *n)
{
    free(n->number);
    free(n);
}


void big_int_swap(big_int *n1, big_int *n2)
{
    unsigned int len = n1->length;
    char sign = n1->sign;
    unsigned char *num = calloc(len, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_swap");
        return;
    }
    memmove(num, n1->number, len);

    n1->number = realloc(n1->number, n2->length);
    if (n1->number == NULL)
    {
        printf("memory error in big_int_swap");
        return;
    }
    memmove(n1->number, n2->number, n2->length);

    n2->number = realloc(n2->number, n1->length);
    if (n2->number == NULL)
    {
        printf("memory error in big_int_swap");
        return;
    }
    memmove(n2->number, num, n1->length);

    n1->length = n2->length;
    n2->length = len;

    n1->sign = n2->sign;
    n2->sign = sign;

    free(num);
}

void big_int_swap2(big_int *n1, big_int *n2)
{
    unsigned int len = n1->length;
    char sign = n1->sign;
    unsigned char *num = n1->number;

    n1->number = n2->number;
    n1->sign = n2->sign;
    n1->length = n2->length;

    n2->number = num;
    n2->sign = sign;
    n2->length = len;
}

big_int *big_int_copy(big_int *x)
{
    big_int *n = calloc(1, sizeof(big_int));
    if (n == NULL)
    {
        printf("memory error in big_int_copy");
    }
    unsigned char *num = calloc(x->length, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_copy");
    }
    memmove(num, x->number, x->length);
    n->number = num;
    n->length = x->length;
    n->sign = x->sign;
    return n;
}

//redo
big_int *big_int_add1(big_int *n1, big_int *n2)
{
    big_int *n3;
    if (n1->number[0] == 0 && n2->number[0] == 0 && (n1->length + n2->length) == 2) // n1 == 0 && n2 == 0
    {
        n3 = big_int_get("0");
        return n3;
    }
    if (n1->sign == *"+" && n2->sign == *"-")
    {
        n2->sign = *"+";
        n3 = big_int_sub1(n1,n2);
        n2->sign = *"-";
        return n3;
    }
    if (n1->sign == *"-" && n2->sign == *"+")
    {
        n1->sign = *"+";
        n3 = big_int_sub1(n2,n1);
        n1->sign = *"-";
        return n3;
    }
    char sign = *"+";
    if (n1->sign == *"-" && n2->sign == *"-")
    {
        sign = *"-";
    }
    n3 = calloc(1, sizeof(big_int));
    unsigned int len_max = n1->length > n2->length ? n1->length + 1 : n2->length + 1;
    unsigned int len_min = n1->length < n2->length ? n1->length : n2->length;
    n3->length = len_max;
    n3->number = calloc(n3->length, sizeof(unsigned char));
    unsigned int flag = 0;
    for (unsigned int i = 0; i < n3->length - 1; ++i)
    {
        if (i < len_min)
        {
            n3->number[i] += n2->number[i] + n1->number[i] + flag;
            flag = (256 - (int) n1->number[i] <= (int) n2->number[i]);
        } else{
            if (n1->length < n2->length)
            {
                n3->number[i] += n2->number[i] + flag;
                if (n2->number[i] != 255)
                {
                    flag = 0;
                }
            } else
            {
                n3->number[i] += n1->number[i] + flag;
                if (n1->number[i] != 255)
                {
                    flag = 0;
                }
            }
        }
    }
    if (flag)
    {
        n3->number[n3->length - 1] += flag;
    }
    n3->sign = sign;
    big_int_dlz(n3);
    return n3;
}


void big_int_add2(big_int *n1, big_int *n2)
{
    if (big_int_equal(n1,n2) && n1->sign != n2->sign)
    {
        free(n1->number);
        n1->number = calloc(1, sizeof(char));
        n1->sign = '+';
        return;
    }
    if (n1->sign == *"+" && n2->sign == *"-")
    {
        n2->sign = *"+";
        big_int_sub2(n1,n2);
        n2->sign = *"-";
        return;
    }
    if (n1->sign == *"-" && n2->sign == *"+")
    {
        n1->sign = *"+";
        big_int_sub2(n1,n2); ////
//        if (n1->sign = '-')
//        {
//            n1->sign = '+';
//        }
//        else
//        {
//            n1->sign = '-';
//        }
        return;
    }




    unsigned int flag = 0, flag2;
    int i = 0;
    if (n1->length >= n2->length)
    {
        n1->length += 1;
        n1->number = realloc(n1->number, n1->length);
        for (; i < n2->length; ++i)
        {
            flag2 = flag;
            flag = (256 - (int) n1->number[i] <= (int) n2->number[i]);
            n1->number[i] += n2->number[i] + flag2;
        }
        if (flag)
        {
            while (n1->number[i] == 255)
            {
                n1->number[i] += 1;
                ++i;
            }
            n1->number[i] += 1;
        }
    } else {
        unsigned int len_swap = n1->length;
        unsigned char *n3_ptr = n1->number;
        n1->length = n2->length;
        n2->length = len_swap;

        n1->number = n2->number;
        n2->number = n3_ptr;
        n1->length += 1;
        n1->number = realloc(n1->number, n1->length);

        for (; i < n2->length; ++i)
        {
            flag2 = flag;
            flag = (256 - (int) n1->number[i] <= (int) n2->number[i]);
            n1->number[i] += n2->number[i] + flag2;
        }
        if (flag)
        {
            while (n1->number[i] == 255)
            {
                n1->number[i] += 1;
                ++i;
            }
            n1->number[i] += 1;
        }
    }
    big_int_dlz(n1);
}


void big_int_shft_l(big_int *n1)
{
    int flag = 0;
    if (n1->number[n1->length - 1] & 128)
    {
        n1->number = realloc(n1->number, ++n1->length);
        n1->number[n1->length - 1] = 1;
        for (int i = 0; i < n1->length - 1; ++i)
        {
            if (n1->number[i] & 128)
            {
                n1->number[i] <<= 1;
                n1->number[i] += flag;
                flag = 1;
            } else {
                n1->number[i] <<= 1;
                n1->number[i] += flag;
                flag = 0;
            }
        }
        return;
    }
    for (int i = 0; i < n1->length; ++i)
    {
        if (n1->number[i] & 128)
        {
            n1->number[i] <<= 1;
            n1->number[i] += flag;
            flag = 1;
        } else {
            n1->number[i] <<= 1;
            n1->number[i] += flag;
            flag = 0;
        }
    }
}


void big_int_shft_r(big_int *n1)
{
    if ((n1->number[n1->length - 1] - 1) || n1->length == 1)
    {
        for (int i = 0; i < n1->length; ++i)
        {
            n1->number[i] >>= 1;
        }
    } else {
        n1->length--;
        n1->number = realloc(n1->number, n1->length);
        if (n1->number == NULL)
        {
            printf("memory error in big_int_shft_r\n");
            return;
        }
        for (int i = 0; i < n1->length; ++i)
        {
            n1->number[i] >>= 1;
        }
        n1->number[n1->length - 1] += 128;
    }
}


void big_int_shft_l2(big_int *n1, int cnt)
{
    big_int_dlz(n1);
    for (int i = 0; i < (cnt & 7); ++i)
    {
        big_int_shft_l(n1);
    }
    cnt >>= 3;
    if (!cnt)
    {
        return;
    }
    n1->length = n1->length + cnt;
    n1->number = realloc(n1->number, n1->length);
    for (int i = n1->length - cnt; i >= 0; --i)
    {
        n1->number[i + cnt] = n1->number[i];
    }
    for (int i = 0; i < cnt; ++i)
    {
        n1->number[i] = 0;
    }
}


void big_int_shft_r2(big_int *n1, int cnt)
{
    big_int_dlz(n1);
    for (int i = 0; i < (cnt & 7); ++i)
    {
        big_int_shft_r(n1);
    }
    cnt >>= 3;
    if (!cnt)
    {
        return;
    }
    if (cnt >= n1->length)
    {
        n1->length = 1;
        n1->number = realloc(n1->number, 1);
        n1->number[0] = 0;
    } else {
        n1->length = n1->length - cnt;
        n1->number = realloc(n1->number, n1->length);
    }
}


int bit_int_leq(big_int *n1, big_int *n2) //n1<=n2
{
    if (n1->length < n2->length)
    {
        return 1;
    }
    if (n1->length > n2->length)
    {
        return 0;
    }
    for (int i = n1->length - 1; i >= 0; --i)
    {
        if (n1->number[i] < n2->number[i]){
            return 1;
        }
        if (n1->number[i] > n2->number[i]){
            return 0;
        }
    }
    return 1;
}


int bit_int_meq(big_int *n1, big_int *n2) //n1>=n2
{
    if (n1->length > n2->length)
    {
        return 1;
    }
    if (n1->length < n2->length)
    {
        return 0;
    }
    for (int i = n1->length - 1; i >= 0; --i)
    {
        if (n1->number[i] > n2->number[i])
        {
            return 1;
        }
        if (n1->number[i] < n2->number[i])
        {
            return 0;
        }
    }
    return 1;
}


big_int *big_int_sub1(big_int *n1, big_int *n2)
{
    big_int *n3;
    if (n1->number[0] == 0 && n2->number[0] == 0 && (n1->length + n2->length) == 2) // n1 == 0 && n2 == 0
    {
        n3 = big_int_get("0");
        return n3;
    }
    if (n1->sign == *"+" && n2->sign == *"-") // n1 - (-n2) = n1 + n2
    {
        printf("test1\n");
        n2->sign = *"+";
        n3 = big_int_add1(n1,n2);
        n2->sign = *"-";
        return n3;
    }
    if (n1->sign == *"-" && n2->sign == *"-") // - n1 - (-n2) = - n1 + n2 = n2 - n1
    {
        printf("test2\n");
        n1->sign = *"+";
        n2->sign = *"+";
        n3 = big_int_sub1(n2,n1);
        n1->sign = *"-";
        n2->sign = *"-";
        return n3;
    }
    if (n1->sign == *"-" && n2->sign == *"+") // - n1 - n2 = n2 - n1
    {
        printf("test3\n");
        n2->sign = *"-";
        n3 = big_int_add1(n1,n2);
        n2->sign = *"+";
        return n3;
    }
    if (bit_int_leq(n1,n2) && !big_int_equal(n1,n2))
    {
        n3 = big_int_sub1(n2,n1);
        n3->sign = *"-";
        return n3;
    }
    else
    {
        n3 = calloc(1, sizeof(big_int));
        n3->number = calloc(n1->length, sizeof(unsigned char));
        n3->length = n1->length;
        n3->sign = *"+";
        int i = 0;
        int flag = 0;
        for (; i < n2->length; ++i)
        {
            n3->number[i] = n1->number[i] - n2->number[i] - flag;
            flag = (int)n1->number[i] < (int)n2->number[i] + (int)flag ? 1 : 0;
        }
        if (flag)
        {
            for (; i < n1->length; ++i)
            {
                if (n1->number[i] != 0)
                {
                    n3->number[i] = n1->number[i] - 1;
                    break;
                }
            }
        }
        i += flag;
        for (; i < n1->length; ++i)
        {
            n3->number[i] = n1->number[i];
        }
    }
    return n3;
}


void big_int_sub2(big_int *n1, big_int *n2)
{
    big_int_dlz(n1);
    big_int_dlz(n2);
    if (n1->sign == *"+" && n2->sign == *"-") // n1 - (-n2) = n1 + n2
    {
        printf("test1\n");
        n2->sign = *"+";
        big_int_add2(n1,n2);
        n2->sign = *"-";
        return;
    }
    if (n1->sign == *"-" && n2->sign == *"-") // - n1 - (-n2) = - n1 + n2 = n2 - n1
    {
        printf("test2\n");
        big_int *n3 = big_int_copy(n2);
        n2->sign = '+';
        n1->sign = '+';
        big_int_sub2(n2,n1);
        big_int_swap2(n1,n2);
        n2->length = n3->length;
        n2->sign = n3->sign;
        n2->number = n3->number;
        return;
    }
    if (n1->sign == *"-" && n2->sign == *"+") // - n1 - n2 = - ( n2 + n1 )
    {
        printf("test3\n");
        n1->sign = *"+";
        big_int_add2(n1,n2);
        n1->sign = *"-";
        return;
    }

    if (!big_int_equal(n1,n2) && bit_int_leq(n1,n2))
    {
        big_int *n3 = big_int_copy(n2);
        big_int_sub2(n2,n1);
        big_int_swap2(n1,n2);
        n2->length = n3->length;
        n2->sign = n3->sign;
        free(n2->number);
        n2->number = n3->number;
        free(n3);
        return;
    }

    if (big_int_equal(n1,n2))
    {
        big_int *n3 = big_int_get("0");
//        big_int_free(n1);
//        big_int *n1;
        n1->length = n3->length;
        n1->sign = n3->sign;
        free(n1->number);
        n1->number = n3->number;
        free(n3);
        return;
    }

    unsigned int flag = 0, flag2;
    int i = 0;
    for (; i < n2->length; ++i)
    {
        flag2 = flag;
        flag = ((int) n1->number[i] < (int) n2->number[i] + flag2); ///////////////////////////////////////////////////////
        n1->number[i] -= n2->number[i] + flag2;//////////////////////////////////////////
    }
    if (flag)
    {
        while (n1->number[i] == 0)
        {
            n1->number[i] = 255;
            ++i;
        }
        n1->number[i] -= 1;
    }
//    n2->sign = '+';
}




















void big_int_fastadd2(big_int *n1, big_int *n2)
{
    if (n1->sign == n2->sign && n1->sign == '-')
    {
        n1->sign = '+';
        n2->sign = '+';
        big_int_fastadd2(n1,n2);
        n1->sign = '-';
        n2->sign = '-';
        return;
    }

    big_int_dlz(n1);
    big_int_dlz(n2);

    if (n1->sign == n2->sign && n1->sign == '+')
    {
        if (n1->length >= n2->length && n2->length >= 2)
        {
            short flag = (n1->number[1] + n2->number[1] + (n1->number[0] + n2->number[0] >= 256) >= 256);
            n1->number[0] += n2->number[0];

            int i = 1;
            for (; i < n2->length - 1; ++i)
            {
                n1->number[i] += n2->number[i] + flag;
                flag = (n1->number[i + 1] + n2->number[i + 1] + flag >= 256);
            }
            n1->number[n2->length - 1] += n2->number[n2->length - 1] + flag;
            ++i;

            if (flag)
            {
                for (; i < n1->length; ++i)
                {
                    if (n1->number[i] == 255)
                    {
                        n1->number[i] = 0;
                    }
                    else
                    {
                        n1->number[i] += 1;
                        return;
                    }
                }
                n1->length += 1;
                n1->number = realloc(n1->number, n1->length);
                n1->number[i] = 1;
                return;
            }

            return;
        }

        if (n1->length < n2->length && n1->length >= 2)
        {
            short flag = (n1->number[1] + n2->number[1] + (n1->number[0] + n2->number[0] >= 256) >= 256);

            n1->number[0] += n2->number[0];
            n1->length = n2->length + 1;
            n1->number = realloc(n1->number, n1->length);

            int i = 1;
            for (; i < n2->length - 1; ++i)
            {
                n1->number[i] += n2->number[i] + flag;
                flag = (n1->number[i + 1] + n2->number[i + 1] + flag >= 256);
            }
            int flag2 = (n1->number[n2->length - 1] + n2->number[n2->length - 1] + flag >= 256);
            n1->number[n2->length - 1] += n2->number[n2->length - 1] + flag;
            ++i;

            if (flag2)
            {
                n1->number[n1->length - 1] = 1;
            }

            big_int_dlz(n1);
            return;
        }

        int i = 0;
        n1->length = n1->length > n2->length ? n1->length + 1 : n2->length + 1;
        n1->number = realloc(n1->number, n1->length);

        char flag1 = 0, flag2 = 0;
        for (; i < n2->length; ++i)
        {
            flag2 = (n1->number[i] + n2->number[i] + flag1 >= 256);
            n1->number[i] += n2->number[i] + flag1;
            flag1 = flag2;
        }

        if (flag1)
        {
            for (; i < n1->length; ++i)
            {
                if (n1->number[i] == 255)
                {
                    n1->number[i] = 0;
                }
                else
                {
                    n1->number[i] += 1;
                    big_int_dlz(n1);
                    return;
                }
            }
            n1->length += 1;
            n1->number = realloc(n1->number, n1->length);
            n1->number[i] = 1;

            big_int_dlz(n1);
            return;
        }

        big_int_dlz(n1);
        return;
    }
}
















void big_int_fastsub2(big_int *n1, big_int *n2)
{
    big_int_dlz(n1);
    big_int_dlz(n2);

    if (n1->sign == n2->sign && n1->sign == '+')
    {
        if (n1->length >= n2->length && n2->length >= 2)
        {
            short flag = (n2->number[1] - n1->number[1] + (n2->number[0] - n1->number[0] > 0) > 0);
//            printf("flag = %d\n", flag);
            n1->number[0] -= n2->number[0];
//            printf("n2_len = %d\n", n2->length);
            int i = 1;
            for (; i < n2->length - 1; ++i)
            {
                n1->number[i] -= n2->number[i] + flag;
                flag = (n2->number[i + 1] - n1->number[i + 1] + flag > 0);
            }
            n1->number[n2->length - 1] -= n2->number[n2->length - 1] + flag;
            ++i;

            if (flag)
            {
                for (; i < n1->length; ++i)
                {
                    if (n1->number[i] == 0)
                    {
                        n1->number[i] = 255;
                    }
                    else
                    {
                        n1->number[i] -= 1;
                        big_int_dlz(n1);
                        return;
                    }
                }
                n1->length += 1;
                n1->number = realloc(n1->number, n1->length);
                n1->number[i] = 1;
                big_int_dlz(n1);
                return;
            }
            big_int_dlz(n1);
            return;
        }

        if (n1->length < n2->length && n1->length >= 2)
        {
            short flag = (n1->number[1] + n2->number[1] + (n1->number[0] + n2->number[0] >= 256) >= 256);

            n1->number[0] += n2->number[0];
            n1->length = n2->length + 1;
            n1->number = realloc(n1->number, n1->length);

            int i = 1;
            for (; i < n2->length - 1; ++i)
            {
                n1->number[i] += n2->number[i] + flag;
                flag = (n1->number[i + 1] + n2->number[i + 1] + flag >= 256);
            }
            int flag2 = (n1->number[n2->length - 1] + n2->number[n2->length - 1] + flag >= 256);
            n1->number[n2->length - 1] += n2->number[n2->length - 1] + flag;
            ++i;

            if (flag2)
            {
                n1->number[n1->length - 1] = 1;
            }

            big_int_dlz(n1);
            return;
        }

        int i = 0;
        n1->length = n1->length > n2->length ? n1->length + 1 : n2->length + 1;
        n1->number = realloc(n1->number, n1->length);

        char flag1 = 0, flag2 = 0;
        for (; i < n2->length; ++i)
        {
            flag2 = (n1->number[i] + n2->number[i] + flag1 >= 256);
            n1->number[i] += n2->number[i] + flag1;
            flag1 = flag2;
        }

        if (flag1)
        {
            for (; i < n1->length; ++i)
            {
                if (n1->number[i] == 255)
                {
                    n1->number[i] = 0;
                }
                else
                {
                    n1->number[i] += 1;
                    big_int_dlz(n1);
                    return;
                }
            }
            n1->length += 1;
            n1->number = realloc(n1->number, n1->length);
            n1->number[i] = 1;

            big_int_dlz(n1);
            return;
        }

        big_int_dlz(n1);
        return;
    }
}