#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

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
    long long  bit_len_loop = strlen(bin_number) * loop;
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

    res->length = (bit_len_loop + 7 - sign_bin) >> 3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }

    for (int i = 0; i < (bit_len_loop - sign_bin); ++i)
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
//        printf("flag = %d\n", flag);
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

//big_int *big_int_add1(big_int * n1,big_int *n2) {
//    if (n1->sign != n2->sign) {
//        int t = n1->sign == '+';
//        if (t) {
//            n2->sign = '+';
//            big_int *n4 = (big_int_sub1(n1, n2));
//            n2->sign = '-';
//            big_int_dlz(n4);
//            return n4;
//        } else {
//            n1->sign = '+';
//            big_int *n4 = (big_int_sub1(n2, n1));
//            n1->sign = '-';
//            big_int_dlz(n4);
//            return n4;
//        }
//    }
//    int mx = (int) fmax(n1->length, n2->length), carry = 0, x;
//    big_int *n3 = (big_int *) malloc(sizeof(big_int));
//    n3->length = mx + 1;
//    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
//    if (n3->number == NULL) { printf("memory error in big_int_add\n"); }
//    int t = n1->length <= n2->length;
//    if (t) big_int_swap2(n1, n2);
//    for (int i = 0; i < mx; i++) {
//        if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;
//        else x = n1->number[i] + carry;
//        n3->number[i] = x & 0xFF;
//        carry = x >> 8;
//    }
//    if (t) big_int_swap2(n1, n2);
//    n3->number[mx] = carry;
//    n3->sign = n1->sign;
//    big_int_dlz(n3);
//    return n3;
//}



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
    big_int_dlz(n1);
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
        n1->length = n1->length - cnt;
        n1->number = realloc(n1->number, n1->length);
        if (n1->number == NULL)
        {
            printf("memory error in big_int_shft_r2\n");
            return;
        }
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
//            printf("flag = %d\n", flag);

        }
        if (flag)
        {
            for (; i < n1->length; ++i)
            {
//                printf("flag = %d\n", flag);
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

//big_int *big_int_sub1(big_int *n1, big_int *n2) {
//    if (n1->sign != n2->sign) {
//        if (n1->sign == '+') {
//            n2->sign = '+';
//            big_int *n4 = (big_int_add1(n1, n2));
//            big_int_dlz(n4);
//            n2->sign = '-';
//            return n4;
//        } else {
//            n2->sign = '-';
//            big_int *n4 = (big_int_add1(n2, n1));
//            big_int_dlz(n4);
//            n2->sign = '+';
//            return n4;
//        }
//    }
//    int mx = (int) fmax(n1->length, n2->length), carry = 0;
//    big_int *n3 = (big_int *) malloc(sizeof(big_int));
//    n3->length = mx;
//    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
//    if (n3->number == NULL) { printf("memory error in big_int_sub\n"); }
//    int t = bit_int_leq(n1, n2);
//    if (t)big_int_swap2(n1, n2);
//    for (int i = 0; i < mx; i++) {
//        if (i < n2->length) {
//            if (n1->number[i] > n2->number[i]) {
//                n3->number[i] = n1->number[i] - n2->number[i] - carry;
//                carry = 0;
//            }
//            if (n1->number[i] == n2->number[i]) {
//                if (carry) {
//                    n3->number[i] = 0xFF;
//                } else {
//                    n3->number[i] = 0;
//                }
//            }
//            if (n1->number[i] < n2->number[i]) {
//                if (carry) {
//                    n3->number[i] = 0xFF + n1->number[i] - n2->number[i];
//                } else {
//                    n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
//                    carry = 1;
//                }
//            }
//        } else {
//            if (carry) {
//                if (n1->number[i]) {
//                    n3->number[i] = n1->number[i] - 1;
//                    carry = 0;
//                } else {
//                    n3->number[i] = 0xFF;
//                }
//            } else {
//                n3->number[i] = n1->number[i];
//            }
//        }
//    }
//    if (t) big_int_swap2(n1, n2);
//    if (n1->sign == '+') {
//        if (t)n3->sign = '-';
//        else n3->sign = '+';
//    } else {
//        if (t)n3->sign = '+';
//        else n3->sign = '-';
//    }
//    big_int_dlz(n3);
//    return n3;
//}

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

//void big_int_add2(big_int *n1, big_int *n2) {
//    if (n1->sign != n2->sign) {
//        int t = n1->sign == '+';
//        if (t) {
//            n2->sign = '+';
//            big_int *n4 = (big_int_sub1(n1, n2));
//            n2->sign = '-';
//            n1->sign = n4->sign;
//            n1->length = n4->length;
//            n1->number=(unsigned char*) realloc(n1->number,n4->length);
//            memmove(n1->number, n4->number, n4->length);
//            big_int_free(&n4);
//            big_int_dlz(n1);
//        } else {
//            n1->sign = '+';
//            big_int *n4 = (big_int_sub1(n2, n1));
//            n1->sign = '-';
//            n1->sign = n4->sign;
//            n1->length = n4->length;
//            n1->number=(unsigned char*) realloc(n1->number,n4->length);
//            memmove(n1->number, n4->number, n4->length);
//            big_int_free(&n4);
//            big_int_dlz(n1);
//        }
//    } else {
//        int mx = (int) fmax(n1->length, n2->length), carry = 0, x;
//        big_int *n3 = (big_int *) malloc(sizeof(big_int));
//        n3->length = mx + 1;
//        n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
//        if (n3->number == NULL) { printf("memory error in big_int_add2\n"); }
//        int t = n1->length <= n2->length;
//        if (t) big_int_swap2(n1, n2);
//        for (int i = 0; i < mx; i++) {
//            if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;
//            else x = n1->number[i] + carry;
//            n3->number[i] = x & 0xFF;
//            carry = x >> 8;
//        }
//        if (t) big_int_swap2(n1, n2);
//        n3->number[mx] = carry;
//        n3->sign = n1->sign;
//        big_int_dlz(n3);
//        n1->length = n3->length;
//        n1->number=(unsigned char*) realloc(n1->number,n3->length);
//        memmove(n1->number, n3->number, n3->length);
//        big_int_free(&n3);
//    }
//}


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
    unsigned int mult, flag, k;
    for (size_t i = 0; i < n1->length; ++i)
    {
        for (size_t j = 0; j < n2->length; ++j)
        {
            mult = n1->number[i] * n2->number[j];
            flag = (n3->number[i + j] + mult) >> 8;
            n3->number[i + j] += mult & 255;
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


//big_int *big_int_mult1(big_int *n1, big_int *n2) {
//
//    unsigned int new_length = n1->length + n2->length;
//
//    big_int *result = (big_int *) malloc(sizeof(big_int));
//    if (!result) return NULL;
//    result->length = new_length;
//
//    result->number = (unsigned char *) calloc(result->length, sizeof(unsigned char));
//
//    for (size_t i = 0; i < n1->length; i++) {
//        for (size_t j = 0; j < n2->length; j++) {
//            unsigned short mult = n1->number[i] * n2->number[j];
//            unsigned short carry = (result->number[i + j] + mult) >> 8;
//            result->number[i + j] += mult;
//            int k = 1;
//            while (carry) {
//                unsigned short carry2 = (result->number[i + j + k] + carry) >> 8;
//                result->number[i + j + k] += carry;
//                carry = carry2;
//                k++;
//            }
//        }
//    }
//    result->sign = n1->sign != n2->sign ? '-' : '+';
//    big_int_dlz(result);
//    return result;
//}




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
