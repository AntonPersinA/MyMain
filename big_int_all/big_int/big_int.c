#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "big_int.h"
#include "../lib/lib.h"


#define _ALMOST_BYTE_ 7
#define _BYTE_ 8
#define _MAX_CHAR_ 8

static big_int* big_int_get_func_res(big_int *res, int *bit_len, char *sign_bin, char *bin_number) //Return the result for the function get big_int
{
    res->length = (*bit_len + _ALMOST_BYTE_ - *sign_bin) >> 3; //We take into account the initial, zero bits of the number
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }

    for (int i = 0; i < *bit_len - *sign_bin; ++i)
    {
        res->number[i / _BYTE_] += (bin_number[*bit_len - i - 1] - '0') << (i % _BYTE_); //we flip big_int, it’s easier to work with it this way
    }
    big_int_dlz(res);

    if (res->number[0] == 0 && res->length == 1) //Make sure there is no negative zero
    {
        res->sign = '+';
    }
    return res;
}


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

    //If there was some extra sign ahead of the line, then we take it into account
    if (bin_number[0] == '-')
    {
        sign_bin = 1;
        res->sign = '-';
    } else {
        res->sign = '+';
    }
    if (bin_number[0] == '+')
    {
        sign_bin = 1;
    }

    return big_int_get_func_res(res, &bit_len, &sign_bin, bin_number);
}


static big_int *big_int_getloop_func(char *bin_number, long long int bit_len_loop, long long int bit_len, big_int *res) //Returns the resultant for the getloop big_int function
{
    if (bin_number[0] == '-' || bin_number[0] == '+')
    {
        for (int i = 0; i < bit_len_loop; ++i)
        {
            res->number[i / _BYTE_] += (bin_number[bit_len - i%(bit_len - 1) - 1] - '0') << (i % _BYTE_);
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
        res->number[i / _BYTE_] += (bin_number[bit_len - i%bit_len - 1] - '0') << (i % _BYTE_);
    }
    big_int_dlz(res);


    if (res->number[0] == 0 && res->length == 1)
    {
        res->sign = '+';
    }
    return res;
}


big_int *big_int_getloop(char *bin_number, int loop)
{
    long long int bit_len = strlen(bin_number);
    loop = loop <= 0 ? 1 : loop;
    char sign_bin = 0;
    big_int *res = (big_int *) calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_getloop\n");
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
    long long int bit_len_loop = (strlen(bin_number) - sign_bin) * loop;

    res->length = (bit_len_loop + _ALMOST_BYTE_) >> 3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_getloop\n");
        return NULL;
    }
    return big_int_getloop_func(bin_number, bit_len_loop, bit_len, res);
}


big_int *big_int_get10(long long int num_1)
{
    char *num_1_str = bin_str(num_1);
    big_int *res = big_int_get(num_1_str);
    free(num_1_str);
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


void big_int_print10(big_int *number)
{
    signed long long int res = 0;
    unsigned long long int pow2_long_long = 1;
    for (int i = 0; i < (number->length > 8 ? 8 : number->length) ; ++i)
    {
        char pow2_char = 1;
        for (int j = 0; j < 8; ++j)
        {
            if (number->number[i] & pow2_char)
            {
                res += pow2_long_long;
            }
            pow2_long_long <<= 1;
            pow2_char <<= 1;
        }
    }
    if(number->sign == '-')
    {
        res *= -1;
    }
    printf("%lld\n", res);
}


signed long long int big_int_to10(big_int *number)
{
    signed long long int res = 0;
    unsigned long long int pow2_long_long = 1;
    for (int i = 0; i < (number->length > 8 ? 8 : number->length) ; ++i)
    {
        char pow2 = 1;
        for (int j = 0; j < 8; ++j)
        {
            if (number->number[i] & pow2)
            {
                res += pow2_long_long;
            }
            pow2_long_long <<= 1;
            pow2 <<= 1;
        }
    }
    if(number->sign == '-')
    {
        res *= -1;
    }
    return res;
}


void big_int_dlz(big_int *number)
{
    unsigned int i = number->length - 1;
    while ((i > 0) && (number->number[i] == 0)) //We are looking for the moment at which unnecessary zeros ended
    {
        --i;
    }

    if (i != number->length - 1)
    {
        number->length = i + 1;
        number->number = realloc(number->number, number->length);
        if (number->number == NULL)
        {
            printf("memory error in big_int_dlz\n");
            return;
        }
    }
}


int big_int_equal(big_int *num_1, big_int *num_2)
{
    if (num_1->length != num_2->length)
    {
        return 0;
    }
    for (int i = 0; i < num_1->length; ++i)
    {
        if (num_1->number[i] != num_2->number[i])
        {
            return 0;
        }
    }
    return 1; //If everything was fine before then they =
}


int big_int_equal_sgn(big_int *num_1, big_int *num_2)
{
    if (num_1->length != num_2->length || num_1->sign != num_2->sign)
    {
        return 0;
    }

    for (int i = 0; i < num_1->length; ++i)
    {
        if (num_1->number[i] != num_2->number[i])
        {
            return 0;
        }
    }
    return 1;
}


void big_int_free(big_int **number)
{
    free((*number)->number);
    free(*number);
    *number=NULL;
}


void big_int_free2(const unsigned int cnt_free, ...)
{
    va_list ptr;
    va_start(ptr, cnt_free);
    for (int j = 0; j < cnt_free; j++) {
        big_int **num = va_arg(ptr, big_int ** );
        if((*num)){
            big_int_free(num);}
    }
    va_end(ptr);
}


void big_int_swap(big_int *num_1, big_int *num_2)
{
    unsigned int len = num_1->length;
    char sign = num_1->sign;
    unsigned char *num = num_1->number;

    num_1->number = num_2->number;
    num_1->sign = num_2->sign;
    num_1->length = num_2->length;

    num_2->number = num;
    num_2->sign = sign;
    num_2->length = len;
}


big_int *big_int_copy(big_int *number)
{
    big_int *res = calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_copy\n");
        return NULL;
    }
    unsigned char *num = calloc(number->length, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_copy\n");
        return NULL;
    }
    memmove(num, number->number, number->length);
    res->number = num;
    res->length = number->length;
    res->sign = number->sign;
    return res;
}

// Calculation res
static void big_int_add1_calculate(big_int *res, big_int *num_1, big_int *num_2, unsigned int len_min, short *flag)
{
    for (unsigned int i = 0; i < res->length - 1; ++i)
    {
        if (i < len_min)
        {
            res->number[i] += num_2->number[i] + num_1->number[i] + *flag;
            *flag = (256 - (short) num_1->number[i] - *flag <= (short) num_2->number[i]);
        } else{
            if (num_1->length < num_2->length)
            {
                res->number[i] += num_2->number[i] + *flag;
                if (num_2->number[i] != _MAX_CHAR_)
                {
                    *flag = 0;
                }
            } else
            {
                res->number[i] += num_1->number[i] + *flag;
                if (num_1->number[i] != _MAX_CHAR_)
                {
                    *flag = 0;
                }
            }
        }
    }
}


//Addition when both numbers are +
static big_int *big_int_add1_helper(big_int *num_1, big_int *num_2)
{
    big_int *res = calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }

    unsigned int len_min = num_1->length < num_2->length ? num_1->length : num_2->length;
    res->length = num_1->length > num_2->length ? num_1->length + 1 : num_2->length + 1;
    res->number = calloc(res->length, sizeof(unsigned char));
    if (res->number == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }
    short flag = 0;
    big_int_add1_calculate(res, num_1, num_2, len_min, &flag);
    if (flag)
    {
        res->number[res->length - 1] += flag;
    }
    res->sign = '+';
    big_int_dlz(res);
    return res;
}


big_int *big_int_add1(big_int *num_1, big_int *num_2)
{
    big_int *res;
    if (num_1->number[0] == 0 && num_2->number[0] == 0 && (num_1->length + num_2->length) == 2) // num_1 == 0 && num_2 == 0
    {
        res = big_int_get("0");
        return res;
    }
    if (num_1->sign == '+' && num_2->sign == '-')
    {
        num_2->sign = '+';
        res = big_int_sub1(num_1,num_2);
        num_2->sign = '-';
        return res;
    }
    if (num_1->sign == '-' && num_2->sign == '+')
    {
        num_1->sign = '+';
        res = big_int_sub1(num_2,num_1);
        num_1->sign = '-';
        return res;
    }
    if (num_1->sign == '-' && num_2->sign == '-')
    {
        res = big_int_add1_helper(num_1, num_2);
        res->sign = '-';
        return res;
    }
    return big_int_add1_helper(num_1, num_2);
}


//If the most significant byte of a number is less than 128,
//then there is no need to create a new byte, just increase each byte by 2
static void big_int_shft_l_helper_less128(big_int *num_1, int flag)
{
    for (int i = 0; i < num_1->length; ++i)
    {
        if (num_1->number[i] & 128)
        {
            num_1->number[i] <<= 1;
            num_1->number[i] += flag;
            flag = 1;
        } else {
            num_1->number[i] <<= 1;
            num_1->number[i] += flag;
            flag = 0;
        }
    }
}


void big_int_shft_l(big_int *num_1)
{
    int flag = 0;
    if (num_1->number[num_1->length - 1] & 128)
    {
        num_1->number = realloc(num_1->number, ++num_1->length);
        if (num_1->number == NULL)
        {
            printf("memory error in big_int_shft_l\n");
            return;
        }

        num_1->number[num_1->length - 1] = 1;
        for (int i = 0; i < num_1->length - 1; ++i)
        {
            if (num_1->number[i] & 128)
            {
                num_1->number[i] <<= 1;
                num_1->number[i] += flag;
                flag = 1;
            } else {
                num_1->number[i] <<= 1;
                num_1->number[i] += flag;
                flag = 0;
            }
        }
        return;
    }
    big_int_shft_l_helper_less128(num_1, flag);
}


void big_int_shft_r(big_int *num_1)
{
    num_1->number[0] >>= 1;
    for (int i = 1; i < num_1->length; ++i)
    {
        if (num_1->number[i] & 1)
        {
            num_1->number[i - 1] = num_1->number[i - 1] | 128;
        }
        num_1->number[i] >>= 1;
    }
    big_int_dlz(num_1);
    if (num_1->length == 1 && num_1->number[0] == 0)
    {
        num_1->sign = '+';
    }
}


void big_int_shft_l2(big_int *num_1, int cnt)
{
    if (cnt <= 0)
    {
        return;
    }
    big_int_dlz(num_1);
    for (int i = 0; i < (cnt & 7); ++i)
    {
        big_int_shft_l(num_1);
    }
    cnt >>= 3;
    if (!cnt)
    {
        return;
    }
    num_1->length += cnt;//
    num_1->number = realloc(num_1->number, num_1->length);
    if (num_1->number == NULL)
    {
        printf("memory error in big_int_shft_l2\n");
        return;
    }

    for (int i = num_1->length - cnt - 1; i >= 0; --i)
    {
        num_1->number[i + cnt] = num_1->number[i];
    }
    for (int i = 0; i < cnt; ++i)
    {
        num_1->number[i] = 0;
    }
}


static char big_int_shft_r2_helper_do(big_int *num_1, int cnt) //Implementation of the shift itself
{
    if (cnt >= num_1->length)
    {
        num_1->length = 1;
        num_1->number = realloc(num_1->number, 1);
        if (num_1->number == NULL)
        {
            printf("memory error in big_int_shift_r2\n");
            return 0;
        }
        num_1->number[0] = 0;
    } else {
        for (int i = cnt; i < num_1->length; ++i)
        {
            num_1->number[i - cnt] = num_1->number[cnt];
        }
        num_1->length -= cnt;
        num_1->number = realloc(num_1->number, num_1->length);
        if (num_1->number == NULL)
        {
            printf("memory error in big_int_shift_r2\n");
            return 0;
        }
    }
    return 1;
}


void big_int_shft_r2(big_int *num_1, int cnt)
{
    big_int_dlz(num_1);
    for (int i = 0; i < (cnt & 7); ++i)
    {
        big_int_shft_r(num_1);
    }
    cnt >>= 3;
    if (!cnt)
    {
        return;
    }
    if (!big_int_shft_r2_helper_do(num_1, cnt)) //If a memory allocation error occurs
    {
        return;
    }
    big_int_dlz(num_1);
    if (num_1->length == 1 && num_1->number[0] == 0)
    {
        num_1->sign = '+';
    }
}


#define _SMTH_CONST_NOT1OR0_ 123
static int big_int_leq_helper_if(big_int *num_1, big_int *num_2) //The function looks at signs and length, nothing more
{
    if (num_1->sign == '-' && num_2->sign == '+')
    {
        return 1;
    }
    if (num_1->sign == '+' && num_2->sign == '-')
    {
        return 0;
    }
    if (num_1->length < num_2->length)
    {
        if (num_1->sign == '-' && num_2->sign == '-')
        {
            return 0;
        }
        return 1;
    }
    if (num_1->length > num_2->length)
    {
        if (num_1->sign == '-' && num_2->sign == '-')
        {
            return 1;
        }
        return 0;
    }
    return _SMTH_CONST_NOT1OR0_; //Any number is important not 0 and 1
}


int big_int_leq(big_int *num_1, big_int *num_2) //num_1<=num_2
{
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    int exit = big_int_leq_helper_if(num_1, num_2);
    if (exit != _SMTH_CONST_NOT1OR0_)
    {
        return exit;
    }
    char ret = 1;
    if (num_1->sign == '-' && num_2->sign == '-')
    {
        ret = 0;
    }
    for (int i = num_1->length - 1; i >= 0; --i)
    {
        if (num_1->number[i] < num_2->number[i]){
            return ret;
        }
        if (num_1->number[i] > num_2->number[i]){
            return !ret;
        }
    }
    return 1;
}


static int big_int_meq_helper_ret(big_int *num_1, big_int *num_2, int ret) // The function will return the desired value
{
    if (num_1->length > num_2->length)
    {
        return ret;
    }
    if (num_1->length < num_2->length)
    {
        return !ret;
    }

    for (int i = num_1->length - 1; i >= 0; --i)
    {
        if (num_1->number[i] > num_2->number[i])
        {
            return ret;
        }
        if (num_1->number[i] < num_2->number[i])
        {
            return !ret;
        }
    }
    return 1; // So they are exactly equal
}

int big_int_meq(big_int *num_1, big_int *num_2) //num_1>=num_2
{
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    if (num_1->sign == '-' && num_2->sign == '+')
    {
        return 0;
    }
    if (num_1->sign == '+' && num_2->sign == '-')
    {
        return 1;
    }

    int ret = 1;
    if (num_1->sign == '-' && num_2->sign == '-')
    {
        ret = 0;
    }
    return big_int_meq_helper_ret(num_1, num_2, ret);
}


// Let's subtract directly
static void big_int_sub1_helper_sub(big_int *res, big_int *num_1, big_int *num_2)
{
    int i = 0;
    short flag = 0;
    for (; i < num_2->length; ++i)
    {
        res->number[i] = num_1->number[i] - num_2->number[i] - flag; //Common subtraction in C
        flag = ((short)num_1->number[i] < (short)num_2->number[i] + flag) ? 1 : 0; //Taking into account the transfer

    }
    if (flag)
    {
        for (; i < num_1->length; ++i)
        {
            if (num_1->number[i] != 0)
            {
                res->number[i] = num_1->number[i] - 1;
                break;
            }
            else
            {
                res->number[i] = _MAX_CHAR_;
            }
        }
    }
    i += flag;
    for (; i < num_1->length; ++i)
    {
        res->number[i] = num_1->number[i];
    }
}


//Subtract when both numbers are +
static big_int *big_int_sub1_helper(big_int *num_1, big_int *num_2)
{
    big_int *res;
    if (big_int_leq(num_1,num_2) && !big_int_equal(num_1,num_2))
    {
        res = big_int_sub1(num_2,num_1); //We change places to subtract the smaller from the larger
        res->sign = '-';
        return res;
    }
    else // Otherwise we just subtract
    {
        res = calloc(1, sizeof(big_int));
        if (res == NULL)
        {
            printf("memory error in big_int_sub1_helper\n");
            return NULL;
        }
        res->number = calloc(num_1->length, sizeof(unsigned char));
        if (res->number == NULL)
        {
            printf("memory error in big_int_sub1_helper\n");
            return NULL;
        }

        res->length = num_1->length;
        res->sign = '+';
        big_int_sub1_helper_sub(res, num_1, num_2);
    }
    big_int_dlz(res);
    return res;
}


big_int *big_int_sub1(big_int *num_1, big_int *num_2)
{
    big_int *res;
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    if (num_1->number[0] == 0 && num_2->number[0] == 0 && (num_1->length + num_2->length) == 2) // num_1 == 0 && num_2 == 0
    {
        res = big_int_get("0");
        return res;
    }
    if (num_1->sign == '+' && num_2->sign == '-') // num_1 - (-num_2) = num_1 + num_2
    {
        num_2->sign = '+';
        res = big_int_add1(num_1,num_2);
        num_2->sign = '-';
        return res;
    }
    if (num_1->sign == '-' && num_2->sign == '-') // - num_1 - (-num_2) = - num_1 + num_2 = num_2 - num_1
    {
        num_1->sign = '+';
        num_2->sign = '+';
        res = big_int_sub1(num_2,num_1);
        num_1->sign = '-';
        num_2->sign = '-';
        return res;
    }
    if (num_1->sign == '-' && num_2->sign == '+') // - num_1 - num_2 = num_2 - num_1
    {
        num_2->sign = '-';
        res = big_int_add1(num_1,num_2);
        num_2->sign = '+';
        return res;
    }
    return big_int_sub1_helper(num_1, num_2);
}


//Add when the first number is greater than the second
static void big_int_add2_helper__num_1morenum_2(big_int *num_1, big_int *num_2)
{
    num_1->length += 1;
    num_1->number = realloc(num_1->number, num_1->length);
    if (num_1->number == NULL)
    {
        printf("memory error in big_int_add2_helper__num_1morenum_2\n");
        return;
    }
    num_1->number[num_1->length - 1] = 0;
    short flag1 = 0, flag2 = 0;
    int i = 0;
    for (; i < num_2->length; ++i)
    {
        flag1 = (num_1->number[i] + num_2->number[i] + flag2 >= 256);
        num_1->number[i] += num_2->number[i] + flag2;
        flag2 = flag1;
    }
    if (flag2)
    {
        for (; i < num_1->length; ++i)
        {
            if (num_1->number[i] == _MAX_CHAR_)
            {
                num_1->number[i] = 0;
            }
            else
            {
                num_1->number[i] += 1;
                break;
            }
        }
    }
    big_int_dlz(num_1);
    return;
}

// Taking into account the transfer
static void big_int_add2_num_1leq2__helper_transfer_up(big_int *num_1, big_int *num_2, short flag2, unsigned int i)
{
    if (flag2)
    {
        for (; i < num_2->length; ++i)
        {
            if (num_2->number[i] == _MAX_CHAR_)
            {
                num_1->number[i] = 0;
            }
            else
            {
                num_1->number[i] = num_2->number[i] + 1;

                flag2 = 0;
                ++i;
                break;
            }
        }
    }
    for (; i < num_2->length; ++i)
    {
        num_1->number[i] = num_2->number[i];
    }
    num_1->number[num_2->length] = flag2;
}


//Addition when first number <= second
static void big_int_add2_helper_num_1leq2(big_int *num_1, big_int *num_2)
{
    num_1->number = realloc(num_1->number, num_2->length + 1);
    if (num_1->number == NULL)
    {
        printf("memory error in big_int_add2_helper_num_1leq2\n");
        return;
    }

    short flag1 = 0;
    short flag2 = 0;
    unsigned int i = 0;
    for (; i < num_1->length; ++i)
    {
        flag1 = (num_1->number[i] + num_2->number[i] + flag2 >= 256);
        num_1->number[i] += num_2->number[i] + flag2;
        flag2 = flag1;
    }
    num_1->length = num_2->length + 1;
    big_int_add2_num_1leq2__helper_transfer_up(num_1, num_2, flag2, i);
    big_int_dlz(num_1);
    return;
}


//We add when both numbers are positive, split into two cases -> two additional functions
static void big_int_add2_helper(big_int *num_1, big_int *num_2)
{
    if (num_1->sign == num_2->sign && num_1->sign == '+')
    {
        if (num_1->length > num_2->length)
        {
            big_int_add2_helper__num_1morenum_2(num_1, num_2);
        }

        if (num_1->length <= num_2->length)
        {
            big_int_add2_helper_num_1leq2(num_1, num_2);
        }
    }
}


static void big_int_add2_various_sign(big_int *num_1, big_int *num_2)
{
    if (num_2->sign == '-')
    {
        num_2->sign = '+';
        big_int_sub2(num_1,num_2);
        num_2->sign = '-';
        return;
    }
    num_1->sign = '+';
    big_int_sub2(num_1,num_2);
    if (num_1->length == 1 && num_1->number[0] == 0)
    {
        num_1->sign = '+';
        return;
    }
    if (num_1->sign == '+')
    {
        num_1->sign = '-';
        return;
    }
    num_1->sign = '+';
}

void big_int_add2(big_int *num_1, big_int *num_2)
{
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    if (num_1->sign != num_2->sign)
    {
        big_int_add2_various_sign(num_1, num_2);
        return;
    }

    if (num_1->sign == num_2->sign && num_1->sign == '-')
    {
        num_1->sign = '+';
        num_2->sign = '+';
        big_int_add2(num_1,num_2);
        num_1->sign = '-';
        num_2->sign = '-';
        return;
    }
    big_int_add2_helper(num_1, num_2);
}


static void big_int_sub2_helper_len1_les_len2(big_int *num_1, big_int *num_2) // Calculate the difference if length num_1 < num_2
{
    short flag1 = 0;
    short flag2 = 0;
    int i = 0;
    for (; i < num_2->length; ++i)
    {
        flag1 = (num_2->number[i] - num_1->number[i] + flag2 > 0);
        num_1->number[i] -= num_2->number[i] + flag2;
        flag2 = flag1;
    }
    if (flag2)
    {
        for (; i < num_1->length; ++i)
        {
            if (num_1->number[i] == 0)
            {
                num_1->number[i] = _MAX_CHAR_;
            }
            else
            {
                num_1->number[i] -= 1;
                break;
            }
        }
    }
    big_int_dlz(num_1);
}


//Subtract when both numbers are positive
static void big_int_sub2_helper_plus(big_int *num_1, big_int *num_2)
{
    if (num_1->sign == num_2->sign && num_1->sign == '+')
    {
        if (num_1->length > num_2->length)
        {
            big_int_sub2_helper_len1_les_len2(num_1, num_2);
            return;
        }

        if (num_1->length <= num_2->length)
        {
            big_int *res = big_int_sub1(num_1,num_2);
            free(num_1->number);
            num_1->number = res->number;
            num_1->length = res->length;
            num_1->sign = res->sign;
            free(res);
            big_int_dlz(num_1);
            return;
        }
    }
}


void big_int_sub2(big_int *num_1, big_int *num_2)
{
    big_int_dlz(num_1);
    big_int_dlz(num_2);

    if (num_1->sign != num_2->sign)
    {
        if (num_1->sign == '+')
        {
            num_2->sign = '+';
            big_int_add2(num_1,num_2);
            num_2->sign = '-';
            return;
        }
        num_2->sign = '-';
        big_int_add2(num_1,num_2);
        num_2->sign = '+';
        return;
    }

    if (num_1->sign == num_2->sign && num_1->sign == '-')
    {
        num_2->sign = '+';
        big_int_add2(num_1, num_2);
        num_2->sign = '-';
        return;
    }
    big_int_sub2_helper_plus(num_1, num_2);
}


static void big_int_mult1_helper_calculate(big_int *res, big_int *num_1, big_int *num_2) // Computational part of multiplication
{
    unsigned int mul_res = 0;
    unsigned int flag = 0;
    unsigned int k = 0;
    for (size_t i = 0; i < num_1->length; ++i)
    {
        for (size_t j = 0; j < num_2->length; ++j)
        {
            mul_res = num_1->number[i] * num_2->number[j];
            flag = (res->number[i + j] + mul_res) >> _BYTE_;
            res->number[i + j] += mul_res & 255;
            k = 1;
            while (flag)
            {
                unsigned int flag2 = (res->number[i + j + k] + (flag)) >> _BYTE_;
                res->number[i + j + k] += (flag & 255);
                flag = flag2;
                k++;
            }
        }
    }
    big_int_dlz(res);
}


big_int *big_int_mult1(big_int *num_1, big_int *num_2)
{
    big_int *res = calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_mult1\n");
        return NULL;
    }
    res->sign = '+';
    if (num_1->sign != num_2->sign)
    {
        if (num_1->number[0] == 0 && num_1->length == 1 || num_2->number[0] == 0 && num_2->length == 1)
        {
            res->number = calloc(1, sizeof(unsigned char));
            if (res->number == NULL)
            {
                printf("memory error in big_int_mult1\n");
                return NULL;
            }
            res->length = 1;
            return res;
        }
        res->sign = '-';
    }
    res->length = num_1->length + num_2->length;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_mult1\n");
        return NULL;
    }
    big_int_mult1_helper_calculate(res, num_1, num_2);
    return res;
}




big_int *big_int_slice(const big_int *num_1, long int left_bound, long int right_bound)
{
    big_int *res = (big_int *) malloc(sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_slice\n");
        return NULL;
    }
    res->sign = num_1->sign;
    res->length = (unsigned int) (right_bound - left_bound + 1);
    if (right_bound >= num_1->length)
    {
        res->length = (unsigned int) (num_1->length - left_bound);
    }
    if (left_bound >= num_1->length)
    {
        res->length = 1;
        res->number = (unsigned char *) calloc(1, sizeof(num_1->number[0]));
        if (res->number == NULL)
        {
            printf("memory error in big_int_slice\n");
            return NULL;
        }
        return res;
    }
    res->number = (unsigned char *) calloc(res->length, sizeof(num_1->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_slice\n");
        return NULL;
    }
    memcpy(res->number, num_1->number + left_bound, res->length);
    big_int_dlz(res);
    return res;
}


big_int *big_int_karatsuba_mult2(big_int *num_1, big_int *num_2)
{
    if (num_1->length + num_2->length < 100) // 100
    {
        return big_int_mult1(num_1, num_2);
    }
    else
    {
        unsigned int mx = (num_1->length >= num_2->length) ? num_1->length : num_2->length;
        mx += (mx & 1);

        big_int *q = big_int_slice(num_1, 0, mx / 2 - 1); //We take a slice of the first half inclusive
        big_int *p = big_int_slice(num_1, mx / 2, mx - 1); //We take a slice of the number of the second half
        big_int *s = big_int_slice(num_2, 0, mx / 2 - 1); //... Also
        big_int *r = big_int_slice(num_2, mx / 2, mx - 1); //... Also

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

//Nothing more than an auxiliary function for normal exponentiation,
//so that there are no problems with copied values,
//it’s easier to implement, because I can do whatever I want with the copies
static big_int *big_int_pow_helper(big_int *num_1_cpy, big_int *num_2_cpy, big_int *res)
{
    if((num_2_cpy->number)[0] > 1 || num_2_cpy->length > 1) //If the number is greater than 1
    {
        if ((num_2_cpy->number)[0] & 1)
        {
            big_int *res2 = big_int_karatsuba_mult2(num_1_cpy, res);
            (num_2_cpy->number)[0] -= 1;
            big_int_swap(res, res2);
            big_int_free(&res2);
            big_int_pow_helper(num_1_cpy, num_2_cpy, res);
        } else
        {
            big_int_shft_r(num_2_cpy);
            big_int *num_1_cpy_cpy = big_int_copy(num_1_cpy);
            big_int *n3 = big_int_karatsuba_mult2(num_1_cpy, num_1_cpy_cpy);
            big_int_free(&num_1_cpy_cpy);
            big_int_pow_helper(n3, num_2_cpy, res);
            big_int_free(&n3);
        }
    } else
    {
        if ((num_2_cpy->number)[0] > 0) //If number = 1
        {
            big_int *res2 = big_int_karatsuba_mult2(num_1_cpy, res);
            big_int *digit1 = big_int_get("1");
            big_int_sub2(num_2_cpy, digit1);
            big_int_free(&digit1);
            big_int_swap(res, res2);
            big_int_free(&res2);
        }
    }
}


big_int *big_int_pow(big_int *num_1, big_int *num_2)
{
    big_int *res = big_int_get("1");
    big_int *num_1_cpy = big_int_copy(num_1);
    big_int *num_2_cpy = big_int_copy(num_2);
    big_int_pow_helper(num_1_cpy, num_2_cpy, res);
    big_int_free(&num_1_cpy);
    big_int_free(&num_2_cpy);
    return res;
}


static big_int *big_int_divide_helper_get_Q(big_int *Q, big_int *dividend, big_int *denominator) // Working on Q
{
    if (Q == NULL)
    {
        printf("memory error in big_int_divide_helper\n");
        return NULL;
    }
    if (((signed long int)dividend->length - (signed long int)denominator->length + 1) > 0)
    {
        Q->length = dividend->length - denominator->length + 1;
    }
    else{
        Q->length = 1; //denominator->length - dividend->length + 1
    }
    unsigned char *Q_array = calloc(Q->length, sizeof(unsigned char));
    if (Q_array == NULL)
    {
        printf("memory error in big_int_divide_helper\n");
        free(Q);
        return NULL;
    }
    Q->number = Q_array;
    Q->sign = '+';
    return Q;
}

// The most important calculations in this function
static void big_int_divide_helper_do(big_int *Q, big_int *R, big_int *dividend, big_int *denominator)
{
    for (int j = (dividend->length - 2); j >= 0; --j)
    {
        for (int i = 128; i >=1; i >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((i & dividend->number[j]) && 1);
            if (big_int_meq(R, denominator))
            {
                big_int_sub2(R, denominator);
                Q->number[j] = Q->number[j] | i;
            }
        }
    }
    big_int_free(&R);
    big_int_dlz(Q);
}


//We simply divide one by the other completely, without taking into account the sign
static big_int *big_int_divide_helper(big_int *dividend, big_int *denominator)
{
    big_int *Q = calloc(1, sizeof(big_int)); //The quotient, the result, is denoted by Q
    if (big_int_divide_helper_get_Q(Q, dividend, denominator) == NULL)
    {
        return NULL;
    }
    big_int *R = big_int_get("0"); //Remainder, denoted by R

    unsigned short no_meaning_zero = 1; //00 00000101, in this case we have two no meaning zero
    for (; no_meaning_zero < dividend->number[dividend->length - 1];)
    {
        no_meaning_zero <<= 1;
    }
    if (no_meaning_zero > dividend->number[dividend->length - 1])
    {
        no_meaning_zero >>= 1;
    }

    for (int index = no_meaning_zero; index >=1; index >>= 1)
    {
        big_int_shft_l(R);
        R->number[0] = (R->number[0]) | ((index & dividend->number[(dividend->length - 1)]) && 1);
        if (big_int_meq(R, denominator))
        {
            big_int_sub2(R, denominator);
            Q->number[(dividend->length - 1)] = Q->number[(dividend->length - 1)] | index;
        }
    }
    big_int_divide_helper_do(Q, R, dividend, denominator);
    return Q;
}

big_int *big_int_divide(big_int *dividend, big_int *denominator)
{
    big_int_dlz(dividend);
    big_int_dlz(denominator);
    if ((denominator->length == 1 && denominator->number[0] == 0) || denominator->length > dividend->length)
    {
        big_int *res = big_int_get("0");
        return res; // x / 0 = 0
    }

    char sign_dividend = dividend->sign;
    char sign_denominator = denominator->sign;
    dividend->sign = '+';
    denominator->sign = '+';
    big_int *res = big_int_divide_helper(dividend, denominator);
    dividend->sign = sign_dividend;
    denominator->sign = sign_denominator;
    if (dividend->sign != denominator->sign)
    {
        if (res->length > 1 || res->number[0] != 0)
        {
            res->sign = '-';
        }
    }
    big_int_dlz(res);
    return res;
}


static big_int *big_int_mod_helper_get_Q(big_int *Q, big_int *dividend, big_int *denominator) // Change Q as needed
{
    if (Q == NULL)
    {
        printf("memory error in big_int_mod_helper\n");
        return NULL;
    }
    if (((signed long int)dividend->length - (signed long int)denominator->length + 1) > 0)
    {
        Q->length = dividend->length - denominator->length + 1;
    }
    else{
        Q->length = 2; //denominator->length - dividend->length + 1
    }

    unsigned char *Q_array = calloc(Q->length, sizeof(unsigned char));
    if (Q_array == NULL)
    {
        printf("memory error in big_int_mod_helper\n");
        free(Q);
        return NULL;
    }
    Q->number = Q_array;
    Q->sign = '+';
    return Q;
}

// The most serious calculations for the result
static void big_int_mod_helper_do(big_int *Q, big_int *R, big_int *dividend, big_int *denominator)
{
    for (int j = (dividend->length - 2); j >= 0; --j)
    {
        for (int i = 128; i >= 1; i >>= 1)
        {
            big_int_shft_l(R);
            R->number[0] = (R->number[0]) | ((i & dividend->number[j]) && 1);
            if (big_int_meq(R, denominator))
            {
                big_int_sub2(R, denominator);
                Q->number[j] = Q->number[j] | i;
            }
        }
    }
    big_int_free(&Q);
}


const short MAS_POW2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256};

//We are simply looking for a number modulo one, not taking into account the sign
static big_int *big_int_mod_helper(big_int *dividend, big_int *denominator)
{
    big_int *Q = calloc(1, sizeof(big_int)); //Quotient, denoted by Q
    if (big_int_mod_helper_get_Q(Q, dividend, denominator) == NULL)
    {
        return NULL;
    }
    big_int *R = big_int_get("0"); //Remainder, result, denoted by R

    unsigned short no_meaning_zero = 256; //00 00000101, in this case we have two no meaning zero
    for (int index = 8; index >= 0; --index)
    {
        if (MAS_POW2[index] <= dividend->number[dividend->length - 1])
        {
            no_meaning_zero = MAS_POW2[index];
            break;
        }
    }

    for (int index = no_meaning_zero; index >=1; index >>= 1)
    {
        big_int_shft_l(R);
        R->number[0] = (R->number[0]) | ((index & dividend->number[(dividend->length - 1)]) && 1);
        if (big_int_meq(R, denominator))
        {
            big_int_sub2(R, denominator);
            Q->number[(dividend->length - 1)] = Q->number[(dividend->length - 1)] | index;
        }
    }
    big_int_mod_helper_do(Q, R, dividend, denominator);
    return R;
}


big_int *big_int_mod(big_int *number, big_int *modulus)
{
    big_int_dlz(number);
    big_int_dlz(modulus);
    if ((modulus->length == 1 && modulus->number[0] == 0))
    {
        big_int *res = big_int_get("0");
        return res;
    }
    char sign_number = number->sign;
    char sign_modulus = modulus->sign;
    number->sign = '+';
    modulus->sign = '+';
    big_int *res = big_int_mod_helper(number, modulus);
    number->sign = sign_number;
    modulus->sign = sign_modulus;
    if (number->sign == '-' && !(res->length == 1 && res->number[0] ==0))
    {
        char sgn = modulus->sign;
        modulus->sign = '+';
        big_int_sub2(res, modulus);
        res->sign = '+';
        modulus->sign = sgn;
    }
    big_int_dlz(res);
    return res;
}


big_int *big_int_rnd(int byte_count) //
{
    big_int *res = calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_rnd\n");
        return NULL;
    }
    res->number = calloc(byte_count, sizeof(unsigned char));
    if (res->number == NULL)
    {
        printf("memory error in big_int_rnd\n");
        free(res);
        return NULL;
    }
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
    if (res == NULL)
    {
        printf("memory error in big_int_rnd_odd\n");
        return NULL;
    }
    res->number = calloc(byte_count, sizeof(unsigned char));
    if (res->number == NULL)
    {
        printf("memory error in big_int_rnd_odd\n");
        free(res);
        return NULL;
    }
    res->length = byte_count;
    res->sign = '+';
    srand(time(NULL) + rand());
    for (int i = 0; i < byte_count - 1; ++i)
    {
        res->number[i] = rand()%256;
    }
    res->number[0] = rand()%256;
    res->number[res->length - 1] += !(res->number[res->length - 1]);
    res->number[0] += !(res->number[0] & 1);
    return res;
}


big_int *big_int_pow_mod(big_int *num, big_int *power, big_int *modulus) //
{
    big_int_dlz(num);
    big_int_dlz(power);
    big_int_dlz(modulus);
    big_int *res = big_int_get("1");

    unsigned char pow2 = 128;
    char first_one = 0; //Let's look at the first time a significant zero appeared
    for (int i = power->length - 1; i >= 0; --i)
    {
        pow2 = 128;
        for (; pow2 >= 1; pow2 >>= 1)
        {
            if (power->number[i] & pow2)
            {
                first_one = 1;
                big_int *new_res = big_int_karatsuba_mult2(res, res); //Squaring
                big_int_swap(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_mod(res, modulus); // Take the module
                big_int_swap(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_karatsuba_mult2(res, num); //We press on the original number since right now it’s 1 (odd number)
                big_int_swap(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_mod(res, modulus); //Take the module
                big_int_swap(new_res, res);
                big_int_free(&new_res);
            }
            else
            {
                if (first_one)
                {
                    big_int *new_res = big_int_karatsuba_mult2(res, res); //Here we simply square it, since even (0)
                    big_int_swap(new_res, res);
                    big_int_free(&new_res);

                    new_res = big_int_mod(res, modulus);
                    big_int_swap(new_res, res);
                    big_int_free(&new_res);
                }
            }
        }
    }
    big_int_dlz(res);
    return res;
}


static int big_int_witness_to_prime(big_int *number, big_int *number_without_two_in_pow, big_int *witness_num, long long int cnt_power_two) //Реализация свидетеля простоты
{
    big_int *one = big_int_get("1"); //Create a unit to subtract it later
    big_int *negative_one = big_int_sub1(number, one); //Minus 1 in the ring of residues based on number
    long long int count = 1; //To control the degree of 2 in a number
    big_int *a_powd_modn = big_int_pow_mod(witness_num, number_without_two_in_pow, number);
    big_int *d_second = big_int_copy(number_without_two_in_pow);

    if (!big_int_equal(a_powd_modn, one))
    {
        if (big_int_equal(negative_one, a_powd_modn))
        {
            big_int_free2(4, &one, &negative_one, &a_powd_modn, &d_second);
            return 1;
        }
        for (; count < cnt_power_two; ++count)
        {
            big_int_shft_l(d_second);
            big_int *karatsuba = big_int_karatsuba_mult2(a_powd_modn, a_powd_modn);
            big_int_free(&a_powd_modn);
            a_powd_modn = big_int_mod(karatsuba, number);
            big_int_free(&karatsuba);

            if (big_int_equal(negative_one, a_powd_modn))
            {
                big_int_free2(4, &one, &negative_one, &a_powd_modn, &d_second);
                return 1;
            }
        }
        big_int_free2(4, &one, &negative_one, &a_powd_modn, &d_second);
        return 0;
    }
    big_int_free2(4, &one, &negative_one, &a_powd_modn, &d_second);
    return 1;
}


static void big_int_helper_cnt_power_two(big_int *number, char *exit, big_int* number_without_two_in_pow, long long int *cnt_power_two)
{
    for (int i = 0; i < number->length; ++i)
    {
        if (*exit)
        {
            break;
        }
        unsigned short pow2 = 1;
        for (; pow2 < _MAX_CHAR_; pow2 <<= 1)
        {
            if ((number_without_two_in_pow->number[i] & pow2))
            {
                *exit = 1;
                break;
            }
            else
            {
                *cnt_power_two += 1;
            }
        }
    } //Now we know how many powers of two are contained in the number = cnt_power_two
}


int big_int_miller_rabin(big_int *number, int count_of_check)
{
    if (number->length == 1)
    {
        if (number->number[0] <= 1)
        {
            return 0;
        }
        if (number->number[0] <= 3)
        {
            return 1;
        }
    }
    long long int cnt_power_two = 0;
    char exit = 0;
    big_int *number_without_two_in_pow = big_int_copy(number);
    big_int *one = big_int_get("1");

    big_int_sub2(number_without_two_in_pow, one); //subtract one from number_without_two_in_pow
    big_int_helper_cnt_power_two(number, &exit, number_without_two_in_pow, &cnt_power_two);
    big_int_shft_r2(number_without_two_in_pow, cnt_power_two); //We take it out from under d degree 2

    for (int check = 0; check < count_of_check; ++check)
    {
        srand(time(NULL) + rand());
        int generate_len = rand() % number->length;
        big_int *witness_num = big_int_rnd(generate_len + !generate_len); //Choosing a Witness to Simplicity
        if (number->length == 1)
        {
            big_int_free(&witness_num);
            int generate_len = (int)(rand()) % number->number[0];
            witness_num = big_int_get10(generate_len + !generate_len);
        }
        if (!big_int_witness_to_prime(number, number_without_two_in_pow, witness_num, cnt_power_two)) // number - the number itself; number_without_two_in_pow - number without powers 2;
        {                                                                                             // witness_num - simplicity witness; cnt_power_two - quantity 2 in number expansion;
            big_int_free2(3, &witness_num, &number_without_two_in_pow, &one);
            return 0;
        }
        big_int_free(&witness_num);
    }
    big_int_free2(2, &number_without_two_in_pow, &one);
    return 1;
}

const long long int MAS_BIG_INT_PRIME1000[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                                               59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
                                               113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                                               181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
                                               251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
                                               317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
                                               397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
                                               463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
                                               557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
                                               617, 619, 631, 641, 643, 647, 653, 659,661, 673, 677,
                                               683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
                                               761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
                                               839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
                                               919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

int test_mod_knowprime(big_int *number)
{
    for (int i = 0; i < 167; ++i)
    {
        big_int *tester = big_int_get10(MAS_BIG_INT_PRIME1000[i]);
        big_int *mod_num = big_int_mod(number, tester);
        big_int_free(&tester);
        if (mod_num->length == 1 && mod_num->number[0] == 0)
        {
            big_int_free(&mod_num);
            return 0;
        }
        big_int_free(&mod_num);
    }
    return 1;
}

big_int *big_int_get_prime(int byte_len, int tst_count)
{
    srand(time(NULL) + rand());
    big_int *rnd_digit = big_int_rnd_odd(byte_len);
    while (1)
    {
        if (byte_len > 2)
        {
            while (test_mod_knowprime(rnd_digit) == 0)
            {
                big_int_free(&rnd_digit);
                rnd_digit = big_int_rnd_odd(byte_len);
            }
        }

        if (big_int_miller_rabin(rnd_digit, tst_count) != 0)
        {
            return rnd_digit;
        }
        big_int_free(&rnd_digit);
        rnd_digit = big_int_rnd_odd(byte_len);
    }
}


big_int *big_int_get_prime_for(int byte_len, int tst_count)
{
    srand(time(NULL) + rand());
    big_int *two = big_int_get("10");
    big_int *four = big_int_get("100");
    big_int *six = big_int_get("110");
    big_int *rnd_digit = big_int_rnd_odd(byte_len);
    rnd_digit->number[rnd_digit->length - 1] %= (rand()%70 + 30);
    rnd_digit->number[rnd_digit->length - 1] += 1;
    rnd_digit->number[0] += !(rnd_digit->number[0] % 2);
    big_int *digit_mod6 = big_int_mod(rnd_digit, six);
    for (int i = big_int_to10(digit_mod6) - 1; i > 0; i -= 2)
    {
        big_int_add2(rnd_digit, two);
    }
    while(1)
    {
        big_int_add2(rnd_digit, four);
        if (big_int_miller_rabin(rnd_digit, tst_count))
        {
            big_int_free2(4, &two, &four, &six, &digit_mod6);
            return rnd_digit;
        }
        big_int_add2(rnd_digit, two);
        if (big_int_miller_rabin(rnd_digit, tst_count))
        {
            big_int_free2(4, &two, &four, &six, &digit_mod6);
            return rnd_digit;
        }
    }

}


big_int *big_int_GCD(big_int *num_1, big_int *num_2) //Greatest Common Divisor, НОД
{
    big_int *n1_cpy = big_int_copy(num_1);
    big_int *n2_cpy = big_int_copy(num_2);
    while(1)
    {
        big_int *MD1 = big_int_mod(n1_cpy, n2_cpy);
        if (MD1->length == 1 && MD1->number[0] == 0)
        {
            big_int_free2(2, &MD1, &n1_cpy);
            return n2_cpy;
        }
        big_int *md2 = big_int_mod(n2_cpy, MD1);
        if (md2->length == 1 && md2->number[0] == 0)
        {
            big_int_free2(3, &md2, &n1_cpy, &n2_cpy);
            return MD1;
        }
        big_int_swap(MD1, n1_cpy);
        big_int_swap(md2, n2_cpy);
        big_int_free2(2, &MD1, &md2);
    }
}


static big_int *big_int_extended_euclid(big_int *number_2, big_int *num_1, big_int *num_2, big_int *bezu_x0, big_int *bezu_x1, big_int *bezu_y0, big_int *bezu_y1, big_int *R)
{
    while (R->length > 1 || R->number[0] != 0)
    {
        big_int *Q = big_int_divide(num_1, num_2);
        big_int_swap(num_1, num_2);
        big_int_swap(num_2, R);

        big_int *temp_bezu_x = big_int_karatsuba_mult2(Q, bezu_x1);
        big_int_swap(bezu_x1, bezu_x0);
        big_int_sub2(bezu_x1, temp_bezu_x);

        big_int *temp_bezu_y = big_int_karatsuba_mult2(Q, bezu_y1);
        big_int_swap(bezu_y1, bezu_y0);
        big_int_sub2(bezu_y1, temp_bezu_y);
        big_int_free2(4, &R, &temp_bezu_x, &temp_bezu_y, &Q);
        R = big_int_mod(num_1, num_2);
    }
    big_int_free2(6, &bezu_x0, &bezu_y0, &bezu_y1, &R, &num_2, &num_1);
    while (bezu_x1->sign == '-')
    {
        big_int_add2(bezu_x1, number_2);
    }
    return bezu_x1;
}


big_int *big_int_reverse_in_ring(big_int *number_1, big_int *number_2)
{
    big_int *ret = big_int_GCD(number_1, number_2);
    if (ret->length > 1 || ret->number[0] != 1)
    {
        big_int *res = big_int_get("0");
        big_int_free(&ret);
        return res;
    }
    big_int_free(&ret);

    big_int *num_1 = big_int_copy(number_1);
    big_int *num_2 = big_int_copy(number_2);
    big_int *bezu_x0 = big_int_get("1");
    big_int *bezu_x1 = big_int_get("0");
    big_int *bezu_y0 = big_int_get("0");
    big_int *bezu_y1 = big_int_get("1");
    big_int *R = big_int_mod(num_1, num_2);

    return big_int_extended_euclid(number_2, num_1, num_2, bezu_x0, bezu_x1, bezu_y0, bezu_y1, R);
}