#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "big_int.h"
#include "../lib/lib.h"





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
    }
    big_int_dlz(res);

    if (res->number[0] == 0 && res->length == 1)
    {
        res->sign = '+';
    }
    return res;
}


big_int *big_int_reget(big_int *n1, char *bin_number)
{
    free(n1->number);

    int bit_len = strlen(bin_number);
    char sign_bin = 0;

    if (*bin_number == '-')
    {
        sign_bin = 1;
        n1->sign = '-';
    } else
    {
        n1->sign = '+';
    }
    if (*bin_number == '+')
    {
        sign_bin = 1;
    }

    n1->length = (bit_len + 7 - sign_bin) >> 3;
    n1->number = calloc(n1->length, sizeof(n1->number[0]));
    if (n1->number == NULL)
    {
        printf("memory error in big_int_reget\n");
        return NULL;
    }

    for (int i = 0; i < bit_len - sign_bin; ++i)
    {
        n1->number[i / 8] += (bin_number[bit_len - i - 1] - '0') << (i % 8);
    }
    big_int_dlz(n1);

    if (n1->number[0] == 0 && n1->length == 1)
    {
        n1->sign = '+';
    }
    return n1;
}


big_int *big_int_getloop(char *bin_number, int loop)
{
    long long bit_len = strlen(bin_number);
    loop = loop <= 0 ? 1 : loop;
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
    long long  bit_len_loop = (strlen(bin_number) - sign_bin) * loop;

    res->length = (bit_len_loop + 7) >> 3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }
    if (bin_number[0] == '-' || bin_number[0] == '+')
    {
        for (int i = 0; i < bit_len_loop; ++i)
        {
//            printf("%c\n", bin_number[i]);
//            printf("ddd = %c\n", bin_number[bit_len - i%(bit_len - 1) - 1]);
            res->number[i / 8] += (bin_number[bit_len - i%(bit_len - 1) - 1] - '0') << (i % 8);
        }
        big_int_dlz(res);

        if (res->number[0] == 0 && res->length == 1)
        {
            res->sign = '+';
        }
        return res;
    }
    for (int i = 0; i < (bit_len_loop); ++i)
    {
        res->number[i / 8] += (bin_number[bit_len - i%bit_len - 1] - '0') << (i % 8);
    }
    big_int_dlz(res);

    if (res->number[0] == 0 && res->length == 1)
    {
        res->sign = '+';
    }
    return res;
}

big_int *big_int_get10(long long int n1)
{
    char *n1_str = bin_str(n1);
    big_int *n1_BI = big_int_get(n1_str);
    free(n1_str);
    return n1_BI;
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

int big_int_to10(big_int *number)
{
    unsigned long long int res = 0;
    unsigned long long int pow2_long = 1;
    for (int i = 0; i < (number->length > 8 ? 8 : number->length) ; ++i)
    {
        char pow2 = 1;
        for (int j = 0; j < 8; ++j)
        {
            if (number->number[i] & pow2)
            {
                res += pow2_long;
            }
            pow2_long <<= 1;
            pow2 <<= 1;
        }
    }
    if(number->sign == '-')
    {
        res *= -1;
    }
    printf("%lld\n", res);
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


void big_int_free(big_int **n)
{
    free((*n)->number);
    free(*n);
    *n=NULL;
}

void big_int_free2(const unsigned int n0, ...)
{
    va_list ptr;
    va_start(ptr, n0);
    for (int j = 0; j < n0; j++) {
        big_int **n = va_arg(ptr, big_int ** );
        if((*n)){
            big_int_free(n);}
    }
    va_end(ptr);
}

void big_int_swap(big_int *n1, big_int *n2)
{
    unsigned int len = n1->length;
    char sign = n1->sign;
    unsigned char *num = calloc(len, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_swap\n");
        return;
    }
    memmove(num, n1->number, len);

    n1->number = realloc(n1->number, n2->length);
    if (n1->number == NULL)
    {
        printf("memory error in big_int_swap\n");
        return;
    }
    memmove(n1->number, n2->number, n2->length);

    n2->number = realloc(n2->number, n1->length);
    if (n2->number == NULL)
    {
        printf("memory error in big_int_swap\n");
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
        printf("memory error in big_int_copy\n");
    }
    unsigned char *num = calloc(x->length, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_copy\n");
    }
    memmove(num, x->number, x->length);
    n->number = num;
    n->length = x->length;
    n->sign = x->sign;
    return n;
}


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
    if (n3 == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }

    unsigned int len_max = n1->length > n2->length ? n1->length + 1 : n2->length + 1;
    unsigned int len_min = n1->length < n2->length ? n1->length : n2->length;
    n3->length = len_max;
    n3->number = calloc(n3->length, sizeof(unsigned char));
    if (n3->number == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }
    unsigned int flag = 0;
    for (unsigned int i = 0; i < n3->length - 1; ++i)
    {
        if (i < len_min)
        {
            n3->number[i] += n2->number[i] + n1->number[i] + flag;
            flag = (256 - (int) n1->number[i] - flag <= (int) n2->number[i]);

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


void big_int_shft_l(big_int *n1)
{
    int flag = 0;
    if (n1->number[n1->length - 1] & 128)
    {
        n1->number = realloc(n1->number, ++n1->length);
        if (n1->number == NULL)
        {
            printf("memory error in big_int_shft_l\n");
            return;
        }

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


//void big_int_shft_r(big_int *n1)
//{
//    if ((n1->number[n1->length - 1] - 1) || n1->length == 1)
//    {
//        for (int i = 0; i < n1->length; ++i)
//        {
//            n1->number[i] >>= 1;
//        }
//    } else {
//        n1->length--;
//        n1->number = realloc(n1->number, n1->length);
//        if (n1->number == NULL)
//        {
//            printf("memory error in big_int_shft_r\n");
//            return;
//        }
//        for (int i = 0; i < n1->length; ++i)
//        {
//            n1->number[i] >>= 1;
//        }
//        n1->number[n1->length - 1] += 128;
//    }
//}


void big_int_shft_r(big_int *n1)
{
    n1->number[0] >>= 1;
    for (int i = 1; i < n1->length; ++i)
    {
        if (n1->number[i] & 1)
        {
            n1->number[i - 1] = n1->number[i - 1] | 128;
        }
        n1->number[i] >>= 1;
    }
    big_int_dlz(n1);
    if (n1->length == 1 && n1->number[0] == 0)
    {
        n1->sign = '+';
    }
}


void big_int_shft_l2(big_int *n1, int cnt)
{
    if (cnt <= 0)
    {
        return;
    }

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
    n1->length += cnt;//
    n1->number = realloc(n1->number, n1->length);
    if (n1->number == NULL)
    {
        printf("memory error in big_int_shft_l2\n");
        return;
    }

    for (int i = n1->length - cnt - 1; i >= 0; --i)
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
        if (n1->number == NULL)
        {
            printf("memory error in big_int_shft_r2\n");
            return;
        }
        n1->number[0] = 0;
    } else {
        for (int i = cnt; i < n1->length; ++i)
        {
            n1->number[i - cnt] = n1->number[cnt];
        }
        n1->length -= cnt;
        n1->number = realloc(n1->number, n1->length);
    }
    big_int_dlz(n1);
    if (n1->length == 1 && n1->number[0] == 0)
    {
        n1->sign = '+';
    }
}


int bit_int_leq(big_int *n1, big_int *n2) //n1<=n2
{
    if (n1->sign == '-' && n2->sign == '+')
    {
        return 1;
    }
    if (n1->sign == '+' && n2->sign == '-')
    {
        return 0;
    }
    big_int_dlz(n1);
    big_int_dlz(n2);
    if (n1->length < n2->length)
    {
        if (n1->sign == '-' && n2->sign == '-')
        {
            return 0;
        }
        return 1;
    }
    if (n1->length > n2->length)
    {
        if (n1->sign == '-' && n2->sign == '-')
        {
            return 1;
        }
        return 0;
    }
    char ret = 1;
    if (n1->sign == '-' && n2->sign == '-')
    {
        ret = 0;
    }
    for (int i = n1->length - 1; i >= 0; --i)
    {
        if (n1->number[i] < n2->number[i]){
            return ret;
        }
        if (n1->number[i] > n2->number[i]){
            return !ret;
        }
    }
    return 1;
}



int bit_int_meq(big_int *n1, big_int *n2) //n1>=n2
{
    if (n1->sign == '-' && n2->sign == '+')
    {
        return 0;
    }
    if (n1->sign == '+' && n2->sign == '-')
    {
        return 1;
    }
    big_int_dlz(n1);
    big_int_dlz(n2);
    char ret = 1;
    if (n1->sign == '-' && n2->sign == '-')
    {
        ret = 0;
    }
    if (n1->length > n2->length)
    {
        return ret;
    }
    if (n1->length < n2->length)
    {
        return !ret;
    }

    for (int i = n1->length - 1; i >= 0; --i)
    {
        if (n1->number[i] > n2->number[i])
        {
            return ret;
        }
        if (n1->number[i] < n2->number[i])
        {
            return !ret;
        }
    }
    return 1;
}


big_int *big_int_sub1(big_int *n1, big_int *n2)
{
    big_int *n3;
    big_int_dlz(n1);
    big_int_dlz(n2);
    if (n1->number[0] == 0 && n2->number[0] == 0 && (n1->length + n2->length) == 2) // n1 == 0 && n2 == 0
    {
        n3 = big_int_get("0");
        return n3;
    }
    if (n1->sign == *"+" && n2->sign == *"-") // n1 - (-n2) = n1 + n2
    {
        n2->sign = *"+";
        n3 = big_int_add1(n1,n2);
        n2->sign = *"-";
        return n3;
    }
    if (n1->sign == *"-" && n2->sign == *"-") // - n1 - (-n2) = - n1 + n2 = n2 - n1
    {
        n1->sign = *"+";
        n2->sign = *"+";
        n3 = big_int_sub1(n2,n1);
        n1->sign = *"-";
        n2->sign = *"-";
        return n3;
    }
    if (n1->sign == *"-" && n2->sign == *"+") // - n1 - n2 = n2 - n1
    {
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
        if (n3 == NULL)
        {
            printf("memory error in big_int_sub1\n");
            return NULL;
        }
        n3->number = calloc(n1->length, sizeof(unsigned char));
        if (n3->number == NULL)
        {
            printf("memory error in big_int_sub1\n");
            return NULL;
        }

        n3->length = n1->length;
        n3->sign = *"+";
        int i = 0;
        int flag = 0;
        for (; i < n2->length; ++i)
        {
            n3->number[i] = n1->number[i] - n2->number[i] - flag;
            flag = ((int)n1->number[i] < (int)n2->number[i] + (int)flag) ? 1 : 0;

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
                else
                {
                    n3->number[i] = 255;
                }
            }
        }
        i += flag;
        for (; i < n1->length; ++i)
        {
            n3->number[i] = n1->number[i];
        }
    }
    big_int_dlz(n3);
    return n3;
}


void big_int_add2(big_int *n1, big_int *n2)
{
    big_int_dlz(n1);
    big_int_dlz(n2);


    if (n1->sign != n2->sign)
    {
        if (n2->sign == '-')
        {
            n2->sign = '+';
            big_int_sub2(n1,n2);
            n2->sign = '-';
            return;
        }
        n1->sign = '+';
        big_int_sub2(n1,n2);
        if (n1->length == 1 && n1->number[0] == 0)
        {
            n1->sign = '+';
            return;
        }
        if (n1->sign == '+')
        {
            n1->sign = '-';
            return;
        }
        n1->sign = '+';
        return;
    }

    if (n1->sign == n2->sign && n1->sign == '-')
    {
        n1->sign = '+';
        n2->sign = '+';
        big_int_add2(n1,n2);
        n1->sign = '-';
        n2->sign = '-';
        return;
    }


    if (n1->sign == n2->sign && n1->sign == '+')
    {
        if (n1->length > n2->length)
        {
            n1->length += 1;
            n1->number = realloc(n1->number, n1->length);
            n1->number[n1->length - 1] = 0;
            short flag1 = 0, flag2 = 0;
            int i = 0;
            for (; i < n2->length; ++i)
            {
                flag1 = (n1->number[i] + n2->number[i] + flag2 >= 256);
                n1->number[i] += n2->number[i] + flag2;
                flag2 = flag1;
            }
            if (flag2)
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
                        break;
                    }
                }
            }
            big_int_dlz(n1);
            return;
        }

        if (n1->length <= n2->length)
        {
            short flag1 = 0, flag2 = 0;
            n1->number = realloc(n1->number, n2->length + 1);
            if (n1->number == NULL)
            {
                printf("memory error in big_int_add2\n");
                return;
            }

            int i = 0;
            for (; i < n1->length; ++i)
            {
                flag1 = (n1->number[i] + n2->number[i] + flag2 >= 256);
                n1->number[i] += n2->number[i] + flag2;
                flag2 = flag1;
            }
            n1->length = n2->length + 1;
            if (flag2)
            {
                for (; i < n2->length; ++i)
                {
                    if (n2->number[i] == 255)
                    {
                        n1->number[i] = 0;
                    }
                    else
                    {
                        n1->number[i] = n2->number[i] + 1;

                        flag2 = 0;
                        ++i;
                        break;
                    }
                }
            }
            for (; i < n2->length; ++i)
            {
                n1->number[i] = n2->number[i];
            }
            n1->number[n2->length] = flag2;
            big_int_dlz(n1);
            return;
        }
    }
}


void big_int_sub2(big_int *n1, big_int *n2)
{
    big_int_dlz(n1);
    big_int_dlz(n2);

    if (n1->sign != n2->sign)
    {
        if (n1->sign == '+')
        {
            n2->sign = '+';
            big_int_add2(n1,n2);
            n2->sign = '-';
            return;
        }
        n2->sign = '-';
        big_int_add2(n1,n2);
        n2->sign = '+';
        return;
    }

    if (n1->sign == n2->sign && n1->sign == '-')
    {
        n2->sign = '+';
        big_int_add2(n1, n2);
        n2->sign = '-';
        return;
    }
    if (n1->sign == n2->sign && n1->sign == '+')
    {
        if (n1->length > n2->length)
        {
            short flag1 = 0, flag2 = 0;
            int i = 0;
            for (; i < n2->length; ++i)
            {
                flag1 = (n2->number[i] - n1->number[i] + flag2 > 0);
                n1->number[i] -= n2->number[i] + flag2;
                flag2 = flag1;
            }

            if (flag2)
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
                        break;
                    }
                }
            }

            big_int_dlz(n1);
            return;
        }

        if (n1->length <= n2->length)
        {
            big_int *n3 = big_int_sub1(n1,n2);
            free(n1->number);
            n1->number = n3->number;
            n1->length = n3->length;
            n1->sign = n3->sign;
            free(n3);
            big_int_dlz(n1);
            return;
        }
    }
}


big_int *big_int_mult1(big_int *n1, big_int *n2)
{
    big_int *n3 = calloc(1, sizeof(big_int));
    if (n3 == NULL)
    {
        printf("memory error in big_int_mult1\n");
        return NULL;
    }
    n3->sign = '+';
    if (n1->sign != n2->sign)
    {
        if (n1->number[0] == 0 && n1->length == 1 || n2->number[0] == 0 && n2->length  == 1)
        {
            n3->number = calloc(1, sizeof(unsigned char));
            n3->length = 1;
            return n3;
        }
        n3->sign = '-';
    }
    n3->length = n1->length + n2->length;
    n3->number = calloc(n3->length, sizeof(n3->number[0]));
    if (n3->number == NULL)
    {
        printf("memory error in big_int_mult1\n");
        return NULL;
    }
    unsigned int mul_res, flag, k;
    for (size_t i = 0; i < n1->length; ++i)
    {
        for (size_t j = 0; j < n2->length; ++j)
        {
            mul_res = n1->number[i] * n2->number[j];
            flag = (n3->number[i + j] + mul_res) >> 8;
            n3->number[i + j] += mul_res & 255;
            k = 1;
            while (flag)
            {
                unsigned int flag2 = (n3->number[i + j + k] + (flag)) >> 8;
                n3->number[i + j + k] += (flag & 255);
                flag = flag2;
                k++;
            }
        }
    }
    big_int_dlz(n3);
    return n3;
}




big_int *big_int_slice(const big_int *n1, long l1, long l2) {
    big_int *n = (big_int *) malloc(sizeof(big_int));
    n->sign = n1->sign;
    n->length = (unsigned int) (l2 - l1 + 1);
    if (l2 >= n1->length) {
        n->length = (unsigned int) (n1->length - l1);
    }
    if (l1 >= n1->length) {
        n->length = 1;
        n->number = (unsigned char *)  calloc(1, sizeof(n1->number[0]));
        return n;
    }
    n->number =(unsigned char *)  calloc(n->length, sizeof(n1->number[0]));
    memcpy(n->number, n1->number + l1, n->length);
    big_int_dlz(n);
    return n;
}


big_int *big_int_karatsuba_mult2(big_int *n1, big_int *n2)
{
    if (n1->length + n2->length <= 4) { return big_int_mult1(n1, n2); }
    else {
        unsigned int mx = (n1->length >= n2->length) ? n1->length : n2->length;
        mx += (mx & 1);

        big_int *q = big_int_slice(n1, 0, mx / 2 - 1);
        big_int *p = big_int_slice(n1, mx / 2, mx - 1);
        big_int *s = big_int_slice(n2, 0, mx / 2 - 1);
        big_int *r = big_int_slice(n2, mx / 2, mx - 1);

        big_int *pr = big_int_karatsuba_mult2(p, r);//A1
        big_int *qs = big_int_karatsuba_mult2(q, s);//A2

        big_int *sm1 = big_int_add1(p, q);
        big_int *sm2 = big_int_add1(r, s);

        big_int *a3 = big_int_karatsuba_mult2(sm1, sm2);//A3=(p+q)(r+s)
        big_int *sm3 = big_int_add1(pr, qs);

        big_int_sub2(a3, sm3);//A3=(p+q)(r+s)-pr-qs=ps+qr

        big_int_shft_l2(pr, mx << 3);//A1<<n
        big_int_shft_l2(a3, mx << 2);//A3=(A3-(A1+A2))<<n/2

        big_int *res = big_int_add1(pr, a3);

        big_int_add2(res, qs);//A1<<n + (A3-(A1+A2))<<n/2 + A2

        big_int_free2(10, &q, &p, &r, &s, &pr, &qs, &a3, &sm1, &sm2, &sm3);
        return res;
    }
}

//Не более чем вспомогательная функция для обычного возведения, для того,
//чтобы не было проблем с скопированными значениями, так проще реализовать, ведь я могу с копиями делать что угодно
static big_int *big_int_pow_help(big_int *n1_cpy, big_int *n2_cpy, big_int *res)
{
//    printf("pow_help\n");
//    printf("n1_cpy = \n");
//    big_int_print(n1_cpy);
//    printf("n2_cpy = \n");
//    big_int_print(n2_cpy);
//    printf("res = \n");
//    big_int_print(res);
    if((n2_cpy->number)[0] > 1 || n2_cpy->length > 1)
    {
        if ((n2_cpy->number)[0] & 1)
        {
            big_int *res2 = big_int_karatsuba_mult2(n1_cpy, res);
            big_int *digit1 = big_int_get("1");
            big_int_sub2(n2_cpy, digit1);
            big_int_free(&digit1);
            big_int_swap2(res, res2);
            big_int_free(&res2);
            big_int_pow_help(n1_cpy, n2_cpy, res);
        } else
        {
            big_int_shft_r(n2_cpy);
            big_int *n1_cpy_cpy = big_int_copy(n1_cpy);
            big_int *n3 = big_int_karatsuba_mult2(n1_cpy, n1_cpy_cpy);
            big_int_free(&n1_cpy_cpy);
            big_int_pow_help(n3, n2_cpy, res);
            big_int_free(&n3);

        }
    }
    else
    {
        if ((n2_cpy->number)[0] > 0)
        {
            big_int *res2 = big_int_karatsuba_mult2(n1_cpy, res);
            big_int *digit1 = big_int_get("1");
            big_int_sub2(n2_cpy, digit1);
            big_int_free(&digit1);
            big_int_swap2(res, res2);
            big_int_free(&res2);
        }
    }
}


big_int *big_int_pow(big_int *n1, big_int *n2)
{
    big_int *res = big_int_get("1");
    big_int *n1_cpy = big_int_copy(n1);
    big_int *n2_cpy = big_int_copy(n2);
    big_int_pow_help(n1_cpy, n2_cpy, res);
    big_int_free(&n1_cpy);
    big_int_free(&n2_cpy);
    return res;
}


big_int *big_int_divided_help(big_int *a, big_int *b)
{
    big_int_dlz(a);
    big_int_dlz(b);
    if ((b->length == 1 && b->number[0] == 0) || b->length > a->length)
    {
        big_int *res = big_int_get("0");
        return res;
    }
    big_int *Q = calloc(1, sizeof(big_int));
    Q->length = a->length - b->length + 1;
    unsigned char *mas_q = calloc(Q->length, sizeof(unsigned char));
    Q->number = mas_q;
    Q->sign = '+';

    big_int *R = big_int_get("0");

    unsigned short char_digit = 1;
    for (; char_digit < a->number[a->length - 1];)
    {
        char_digit <<= 1;
    }

    if (char_digit > a->number[a->length - 1])
    {
        char_digit >>= 1;
    }
    {
        for (int t = char_digit; t >=1; t >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((t & a->number[(a->length - 1)]) && 1);
            if (bit_int_meq(R, b))
            {
                big_int_sub2(R, b);
                Q->number[(a->length - 1)] = Q->number[(a->length - 1)] | t;
            }
        }
    }
    for (int j = (a->length - 2); j >= 0; --j)
    {
        for (int t = 128; t >=1; t >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((t & a->number[j]) && 1);
            if (bit_int_meq(R, b))
            {
                big_int_sub2(R, b);
                Q->number[j] = Q->number[j] | t;
            }
        }
    }
    big_int_free(&R);
    return Q;
}

big_int *big_int_divided(big_int *a, big_int *b)
{
    char sign_a = a->sign;
    char sign_b = b->sign;
    a->sign = '+';
    b->sign = '+';
    big_int *ret = big_int_divided_help(a, b);
    a->sign = sign_a;
    b->sign = sign_b;
    if (a->sign != b->sign)
    {
        if (ret->length > 1 || ret->number[0] != 0)
        {
            ret->sign = '-';
        }
    }
    big_int_dlz(ret);
    return ret;
}








//    unsigned short char_digit = 256;
//    for (int ii = 8; ii >= 0; --ii)
//    {
//        if (MAS_POW2[ii] < a->number[a->length - 1])
//        {
//            char_digit = MAS_POW2[ii];
//        }
//    }
const short MAS_POW2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256};

big_int *big_int_mod_help(big_int *a, big_int *b)
{
    big_int_dlz(a);
    big_int_dlz(b);
    if ((b->length == 1 && b->number[0] == 0))
    {
        big_int *res = big_int_get("0");
        return res;
    }
    big_int *Q = calloc(1, sizeof(big_int));
    Q->length = a->length - b->length + 1;
    unsigned char *mas_q = calloc(Q->length, sizeof(unsigned char));
    Q->number = mas_q;
    Q->sign = '+';

    big_int *R = big_int_get("0");

    unsigned short char_digit = 1;
    for (; char_digit < a->number[a->length - 1];)
    {
        char_digit <<= 1;
    }

    if (char_digit > a->number[a->length - 1])
    {
        char_digit >>= 1;
    }

    {
        for (int t = char_digit; t >=1; t >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((t & a->number[(a->length - 1)]) && 1);
            if (bit_int_meq(R, b))
            {
                big_int_sub2(R, b);
                Q->number[(a->length - 1)] = Q->number[(a->length - 1)] | t;
            }
        }
    }

    for (int j = (a->length - 2); j >= 0; --j)
    {
        for (int t = 128; t >=1; t >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((t & a->number[j]) && 1);
            if (bit_int_meq(R, b))
            {
                big_int_sub2(R, b);
                Q->number[j] = Q->number[j] | t;
            }
        }
    }
    big_int_free(&Q);
    return R;
}


big_int *big_int_mod(big_int *a, big_int *b)
{
    char sign_a = a->sign;
    char sign_b = b->sign;
    a->sign = '+';
    b->sign = '+';
    big_int *ret = big_int_mod_help(a, b);
    a->sign = sign_a;
    b->sign = sign_b;
    if (a->sign == '-')
    {
        if (ret->length > 1 || ret->number[0] != 0)
        {
            ret->sign = '-';
        }
    }
    big_int_dlz(ret);
    return ret;
}


big_int *big_int_rnd(int byte_count)
{
    big_int *res = calloc(1, sizeof(big_int));
    res->number = calloc(byte_count, sizeof(unsigned char));
    res->length = byte_count;
    res->sign = '+';
    srand(time(NULL) + rand());
    for (int i = 0; i < byte_count - 1; ++i)
    {
        res->number[i] = rand()%256;
    }
    int last = rand()%256;
    res->number[byte_count - 1] = last + !last;

    return res;
}


big_int *big_int_rnd_odd(int byte_count)
{
    big_int *res = calloc(1, sizeof(big_int));
    res->number = calloc(byte_count, sizeof(unsigned char));
    res->length = byte_count;
    res->sign = '+';
    srand(time(NULL) + rand());
    for (int i = 1; i < byte_count - 1; ++i)
    {
        res->number[i] = rand()%256;
    }
    int last = rand()%256;
    res->number[byte_count - 1] = last + !last;
    res->number[0] = res->number[0] | 1;
    return res;
}


big_int *big_int_pow_mod(big_int *a, big_int *pow, big_int *modulus)
{
    big_int *res = big_int_get("1");
    big_int *one = big_int_get("1");
    big_int *one_static = big_int_get("1");

    for (; bit_int_leq(one, pow); big_int_add2(one, one_static))
    {
        big_int *mult = big_int_karatsuba_mult2(res, a);
        big_int_free(&res);
        res = big_int_mod(mult, modulus);
        big_int_free(&mult);
    }
    big_int_free2(2, &one, &one_static);
    return res;
}


big_int *big_int_pow_mod_fast(big_int *a, big_int *pow, big_int *modulus)
{
    big_int_dlz(a);
    big_int_dlz(pow);
    big_int_dlz(modulus);
    big_int *res = big_int_get("1");
//    big_int_print(pow);

    unsigned char pow_2 = 128;

    if (pow->length == 1)
    {
        for (int k = 7; k >= 0; --k)
        {
            if (MAS_POW2[k] <= pow->number[0])
            {
                pow_2 = MAS_POW2[k];
                break;
            }
        }
        for (; pow_2 >= 2; pow_2 >>= 1)
        {
            if (pow_2 != 128)
            {
                big_int *new_res = big_int_karatsuba_mult2(res, res);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }

            if (pow->number[0] & pow_2)
            {
                big_int *new_res = big_int_karatsuba_mult2(res, a);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }
            else
            {
                big_int *new_res = big_int_karatsuba_mult2(res, res);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }
        }
        if (pow->number[0] & 1)
        {
            big_int *new_res = big_int_karatsuba_mult2(res, a);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
        else
        {
            big_int *new_res = big_int_karatsuba_mult2(res, res);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
        return res;
    }

    for (int k = 7; k >= 0; --k)
    {
        if (MAS_POW2[k] <= pow->number[pow->length - 1])
        {
            pow_2 = MAS_POW2[k];
            break;
        }
    }

    for (; pow_2 >= 1; pow_2 >>= 1)
    {
        if (pow->number[pow->length - 1] & pow_2)
        {
            big_int *new_res = big_int_karatsuba_mult2(res, a);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);

            new_res = big_int_karatsuba_mult2(res, res);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
        else
        {
            big_int *new_res = big_int_karatsuba_mult2(res, res);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
    }

    for (int byte = pow->length - 2; byte >= 1; --byte)
    {
//        printf("len = %d\n", pow->length);

        pow_2 = 128;
        for (; pow_2 >= 1; pow_2 >>= 1)
        {
            if (pow->number[byte] & pow_2)
            {
                big_int *new_res = big_int_karatsuba_mult2(res, a);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_karatsuba_mult2(res, res);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }
            else
            {
                big_int *new_res = big_int_karatsuba_mult2(res, res);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
                new_res = big_int_mod(res, modulus);
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }
        }
    }


//    printf("pow2 = %d\n", pow_2);

//    for (int k = 7; k >= 0; --k)
//    {
//        if (MAS_POW2[k] <= pow->number[0])
//        {
//            pow_2 = MAS_POW2[k];
//            break;
//        }
//    }
//    printf("res = ");
//    big_int_to10(res);
    pow_2 = 128;
    for (; pow_2 >= 2; pow_2 >>= 1)
    {
        if (pow->number[0] & pow_2)
        {
            big_int *new_res = big_int_karatsuba_mult2(res, a);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);

            new_res = big_int_karatsuba_mult2(res, res);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
        else
        {
            big_int *new_res = big_int_karatsuba_mult2(res, res);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
            new_res = big_int_mod(res, modulus);
            big_int_swap2(new_res, res);
            big_int_free(&new_res);
        }
    }
    if (pow->number[0] & 1)
    {
        big_int *new_res = big_int_karatsuba_mult2(res, a);
        big_int_swap2(new_res, res);
        big_int_free(&new_res);
        new_res = big_int_mod(res, modulus);
        big_int_swap2(new_res, res);
        big_int_free(&new_res);
    }
//    else
//    {
//        big_int *new_res = big_int_karatsuba_mult2(res, res);
//        big_int_swap2(new_res, res);
//        big_int_free(&new_res);
//        new_res = big_int_mod(res, modulus);
//        big_int_swap2(new_res, res);
//        big_int_free(&new_res);
//    }
    return res;
}