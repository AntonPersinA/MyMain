    //#include <limits.h>
    //#include <math.h>
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

    //Если впереди строки был какой то лишний знак, то мы его учитывем
    if (*bin_number == '-')
    {
        sign_bin = 1;
        res->sign = '-';
    } else { res->sign = '+'; }
    if (*bin_number == '+') {
        sign_bin = 1;
    }

    res->length = (bit_len + 7 - sign_bin) >> 3; //Учитываем начальные
    // нулевые биты числа
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_get\n");
        return NULL;
    }

    for (int i = 0; i < bit_len - sign_bin; ++i)
    {
        res->number[i / 8] += (bin_number[bit_len - i - 1] - '0') << (i % 8); //переворачиваем биг_инт, так проще с ним работать
    }
    big_int_dlz(res);

    if (res->number[0] == 0 && res->length == 1) //Смотрим чтобы не было отрицательного нуля
    {
        res->sign = '+';
    }
    return res;
}


big_int *big_int_reget(big_int *number, char *bin_number)
{
    free(number->number);

    int bit_len = strlen(bin_number);
    char sign_bin = 0;

    if (*bin_number == '-')
    {
        sign_bin = 1;
        number->sign = '-';
    } else{
        number->sign = '+';
    }
    if (*bin_number == '+')
    {
        sign_bin = 1;
    }

    number->length = (bit_len + 7 - sign_bin) >> 3;
    number->number = calloc(number->length, sizeof(number->number[0]));
    if (number->number == NULL)
    {
        printf("memory error in big_int_reget\n");
        return NULL;
    }

    for (int i = 0; i < bit_len - sign_bin; ++i)
    {
        number->number[i / 8] += (bin_number[bit_len - i - 1] - '0') << (i % 8);
    }
    big_int_dlz(number);

    if (number->number[0] == 0 && number->length == 1)
    {
        number->sign = '+';
    }
    return number;
}


big_int *big_int_getloop(char *bin_number, int loop)
{
    long long bit_len = strlen(bin_number);
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
    long long  bit_len_loop = (strlen(bin_number) - sign_bin) * loop;

    res->length = (bit_len_loop + 7) >> 3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL)
    {
        printf("memory error in big_int_getloop\n");
        return NULL;
    }
    if (bin_number[0] == '-' || bin_number[0] == '+')
    {
        for (int i = 0; i < bit_len_loop; ++i)
        {
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
    while ((i > 0) && (number->number[i] == 0)) //Ищем на каком моменте закочились ненужные нули
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
    return 1; //Если до этого все норм то они =
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
    unsigned char *num = calloc(len, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_swap\n");
        return;
    }
    memmove(num, num_1->number, len);

    num_1->number = realloc(num_1->number, num_2->length);
    if (num_1->number == NULL)
    {
        printf("memory error in big_int_swap\n");
        return;
    }
    memmove(num_1->number, num_2->number, num_2->length);

    num_2->number = realloc(num_2->number, num_1->length);
    if (num_2->number == NULL)
    {
        printf("memory error in big_int_swap\n");
        return;
    }
    memmove(num_2->number, num, num_1->length);

    num_1->length = num_2->length;
    num_2->length = len;

    num_1->sign = num_2->sign;
    num_2->sign = sign;

    free(num);
}


void big_int_swap2(big_int *num_1, big_int *num_2)
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
    }
    unsigned char *num = calloc(number->length, sizeof(unsigned char));
    if (num == NULL)
    {
        printf("memory error in big_int_copy\n");
    }
    memmove(num, number->number, number->length);
    res->number = num;
    res->length = number->length;
    res->sign = number->sign;
    return res;
}


//Сложение когда оба числа +
static big_int *big_int_add1_help(big_int *num_1, big_int *num_2)
{
    char sign = '+';
    if (num_1->sign == '-' && num_2->sign == '-')
    {
        sign = '-';
    }
    big_int *res = calloc(1, sizeof(big_int));
    if (res == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }

    unsigned int len_max = num_1->length > num_2->length ? num_1->length + 1 : num_2->length + 1;
    unsigned int len_min = num_1->length < num_2->length ? num_1->length : num_2->length;
    res->length = len_max;
    res->number = calloc(res->length, sizeof(unsigned char));
    if (res->number == NULL)
    {
        printf("memory error in big_int_add1\n");
        return NULL;
    }
    unsigned int flag = 0;
    for (unsigned int i = 0; i < res->length - 1; ++i)
    {
        if (i < len_min)
        {
            res->number[i] += num_2->number[i] + num_1->number[i] + flag;
            flag = (256 - (int) num_1->number[i] - flag <= (int) num_2->number[i]);
        } else{
            if (num_1->length < num_2->length)
            {
                res->number[i] += num_2->number[i] + flag;
                if (num_2->number[i] != 255)
                {
                    flag = 0;
                }
            } else
            {
                res->number[i] += num_1->number[i] + flag;
                if (num_1->number[i] != 255)
                {
                    flag = 0;
                }
            }
        }
    }
    if (flag)
    {
        res->number[res->length - 1] += flag;
    }
    res->sign = sign;
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
    return big_int_add1_help(num_1, num_2);
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
    if (cnt >= num_1->length)
    {
        num_1->length = 1;
        num_1->number = realloc(num_1->number, 1);
        if (num_1->number == NULL)
        {
            printf("memory error in big_int_shift_r2\n");
            return;
        }
        num_1->number[0] = 0;
    } else {
        for (int i = cnt; i < num_1->length; ++i)
        {
            num_1->number[i - cnt] = num_1->number[cnt];
        }
        num_1->length -= cnt;
        num_1->number = realloc(num_1->number, num_1->length);
    }
    big_int_dlz(num_1);
    if (num_1->length == 1 && num_1->number[0] == 0)
    {
        num_1->sign = '+';
    }
}


int big_int_leq(big_int *num_1, big_int *num_2) //num_1<=num_2
{
    if (num_1->sign == '-' && num_2->sign == '+')
    {
        return 1;
    }
    if (num_1->sign == '+' && num_2->sign == '-')
    {
        return 0;
    }
    big_int_dlz(num_1);
    big_int_dlz(num_2);
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



int big_int_meq(big_int *num_1, big_int *num_2) //num_1>=num_2
{
    if (num_1->sign == '-' && num_2->sign == '+')
    {
        return 0;
    }
    if (num_1->sign == '+' && num_2->sign == '-')
    {
        return 1;
    }
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    char ret = 1;
    if (num_1->sign == '-' && num_2->sign == '-')
    {
        ret = 0;
    }
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
    return 1;
}


//Вычитаем когда оба числа +
static big_int *big_int_sub1_help(big_int *num_1, big_int *num_2)
{
    big_int *res;
    if (big_int_leq(num_1,num_2) && !big_int_equal(num_1,num_2))
    {
        res = big_int_sub1(num_2,num_1); //Меняем местами чтобы из большего вычитать меньшее
        res->sign = '-';
        return res;
    }
    else // Иначе просто вычитаем
    {
        res = calloc(1, sizeof(big_int));
        if (res == NULL)
        {
            printf("memory error in big_int_sub1\n");
            return NULL;
        }
        res->number = calloc(num_1->length, sizeof(unsigned char));
        if (res->number == NULL)
        {
            printf("memory error in big_int_sub1\n");
            return NULL;
        }

        res->length = num_1->length;
        res->sign = '+';
        int i = 0;
        int flag = 0;
        for (; i < num_2->length; ++i)
        {
            res->number[i] = num_1->number[i] - num_2->number[i] - flag; //Обычное вычитание Си
            flag = ((int)num_1->number[i] < (int)num_2->number[i] + (int)flag) ? 1 : 0; //Учитываем перенос

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
                    res->number[i] = 255;
                }
            }
        }
        i += flag;
        for (; i < num_1->length; ++i)
        {
            res->number[i] = num_1->number[i];
        }
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
    return big_int_sub1_help(num_1, num_2);
}


//Складываем когда первое число больше чем второе
static void big_int_add2_help__num_1morenum_2(big_int *num_1, big_int *num_2)
{
    num_1->length += 1;
    num_1->number = realloc(num_1->number, num_1->length);
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
            if (num_1->number[i] == 255)
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


//Складываем когда первое число <= второго
static void big_int_add2_help_num_1leq2(big_int *num_1, big_int *num_2)
{
    short flag1 = 0, flag2 = 0;
    num_1->number = realloc(num_1->number, num_2->length + 1);
    if (num_1->number == NULL)
    {
        printf("memory error in big_int_add2\n");
        return;
    }

    int i = 0;
    for (; i < num_1->length; ++i)
    {
        flag1 = (num_1->number[i] + num_2->number[i] + flag2 >= 256);
        num_1->number[i] += num_2->number[i] + flag2;
        flag2 = flag1;
    }
    num_1->length = num_2->length + 1;
    if (flag2)
    {
        for (; i < num_2->length; ++i)
        {
            if (num_2->number[i] == 255)
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
    big_int_dlz(num_1);
    return;
}


//Складываем когда оба числа положительные, разбиваемся на два случая -> две доп функции
static void big_int_add2_help(big_int *num_1, big_int *num_2)
{
    if (num_1->sign == num_2->sign && num_1->sign == '+')
    {
        if (num_1->length > num_2->length)
        {
            big_int_add2_help__num_1morenum_2(num_1, num_2);
        }

        if (num_1->length <= num_2->length)
        {
            big_int_add2_help_num_1leq2(num_1, num_2);
        }
    }
}


void big_int_add2(big_int *num_1, big_int *num_2)
{
    big_int_dlz(num_1);
    big_int_dlz(num_2);
    if (num_1->sign != num_2->sign)
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
    big_int_add2_help(num_1, num_2);
}


//Вычитаем когда оба числа положительные
static void big_int_sub2_help(big_int *num_1, big_int *num_2)
{

    if (num_1->sign == num_2->sign && num_1->sign == '+')
    {
        if (num_1->length > num_2->length)
        {
            short flag1 = 0, flag2 = 0;
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
                        num_1->number[i] = 255;
                    }
                    else
                    {
                        num_1->number[i] -= 1;
                        break;
                    }
                }
            }

            big_int_dlz(num_1);
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
    big_int_sub2_help(num_1, num_2);
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
        if (num_1->number[0] == 0 && num_1->length == 1 || num_2->number[0] == 0 && num_2->length  == 1)
        {
            res->number = calloc(1, sizeof(unsigned char));
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
    unsigned int mul_res, flag, k;
    for (size_t i = 0; i < num_1->length; ++i)
    {
        for (size_t j = 0; j < num_2->length; ++j)
        {
            mul_res = num_1->number[i] * num_2->number[j];
            flag = (res->number[i + j] + mul_res) >> 8;
            res->number[i + j] += mul_res & 255;
            k = 1;
            while (flag)
            {
                unsigned int flag2 = (res->number[i + j + k] + (flag)) >> 8;
                res->number[i + j + k] += (flag & 255);
                flag = flag2;
                k++;
            }
        }
    }
    big_int_dlz(res);
    return res;
}




big_int *big_int_slice(const big_int *num_1, long int left_bound, long int right_bound)
{
    big_int *res = (big_int *) malloc(sizeof(big_int));
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
        return res;
    }
    res->number = (unsigned char *) calloc(res->length, sizeof(num_1->number[0]));
    memcpy(res->number, num_1->number + left_bound, res->length);
    big_int_dlz(res);
    return res;
}


big_int *big_int_karatsuba_mult2(big_int *num_1, big_int *num_2)
{
    if (num_1->length + num_2->length <= 4)
    {
        return big_int_mult1(num_1, num_2);
    }
    else
    {
        unsigned int mx = (num_1->length >= num_2->length) ? num_1->length : num_2->length;
        mx += (mx & 1);

        big_int *q = big_int_slice(num_1, 0, mx / 2 - 1); //Берем срез первой половины включительно
        big_int *p = big_int_slice(num_1, mx / 2, mx - 1); //Берем срез второй половины
        big_int *s = big_int_slice(num_2, 0, mx / 2 - 1); //... также
        big_int *r = big_int_slice(num_2, mx / 2, mx - 1); //... также

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
static big_int *big_int_pow_help(big_int *num_1_cpy, big_int *num_2_cpy, big_int *res)
{
    if((num_2_cpy->number)[0] > 1 || num_2_cpy->length > 1) //Если число больше 1
    {
        if ((num_2_cpy->number)[0] & 1)
        {
            big_int *res2 = big_int_karatsuba_mult2(num_1_cpy, res);
            (num_2_cpy->number)[0] -= 1;
            big_int_swap2(res, res2);
            big_int_free(&res2);
            big_int_pow_help(num_1_cpy, num_2_cpy, res);
        } else
        {
            big_int_shft_r(num_2_cpy);
            big_int *num_1_cpy_cpy = big_int_copy(num_1_cpy);
            big_int *n3 = big_int_karatsuba_mult2(num_1_cpy, num_1_cpy_cpy);
            big_int_free(&num_1_cpy_cpy);
            big_int_pow_help(n3, num_2_cpy, res);
            big_int_free(&n3);
        }
    }
    else
    {
        if ((num_2_cpy->number)[0] > 0) //Если число = 1
        {
            big_int *res2 = big_int_karatsuba_mult2(num_1_cpy, res);
            big_int *digit1 = big_int_get("1");
            big_int_sub2(num_2_cpy, digit1);
            big_int_free(&digit1);
            big_int_swap2(res, res2);
            big_int_free(&res2);
        }
    }
}


big_int *big_int_pow(big_int *num_1, big_int *num_2)
{
    big_int *res = big_int_get("1");
    big_int *num_1_cpy = big_int_copy(num_1);
    big_int *num_2_cpy = big_int_copy(num_2);
    big_int_pow_help(num_1_cpy, num_2_cpy, res);
    big_int_free(&num_1_cpy);
    big_int_free(&num_2_cpy);
    return res;
}

//Просто делим одно на другое нацело, не учитывая знак, но учитвая что не делим на ноль
static big_int *big_int_divide_help(big_int *dividend, big_int *denominator)
{
    big_int *Q = calloc(1, sizeof(big_int)); //Частное, результат, обозначается за Q
    if (((signed long int)dividend->length - (signed long int)denominator->length + 1) > 0)
    {
        Q->length = dividend->length - denominator->length + 1;
    }
    else{
        Q->length = 1; //denominator->length - dividend->length + 1
    }
    unsigned char *Q_array = calloc(Q->length, sizeof(unsigned char));
    Q->number = Q_array;
    Q->sign = '+';

    big_int *R = big_int_get("0"); //Остаток, обозначается за R

    unsigned short no_meaning_zero = 1; //0000000123
    for (; no_meaning_zero < dividend->number[dividend->length - 1];)
    {
        no_meaning_zero <<= 1;
    }

    if (no_meaning_zero > dividend->number[dividend->length - 1])
    {
        no_meaning_zero >>= 1;
    }
    {
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
    }
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
    big_int *res = big_int_divide_help(dividend, denominator);
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









const short MAS_POW2[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256};

//Просто ищем число по модулю одно, не учитывая знак, но учитвая что не делим на ноль
static big_int *big_int_mod_help(big_int *dividend, big_int *denominator)
{
    big_int *Q = calloc(1, sizeof(big_int)); //Частное, обозначается за Q
    if (((signed long int)dividend->length - (signed long int)denominator->length + 1) > 0)
    {
        Q->length = dividend->length - denominator->length + 1;
    }
    else{
        Q->length = 2; //denominator->length - dividend->length + 1
    }

    unsigned char *Q_array = calloc(Q->length, sizeof(unsigned char));
    Q->number = Q_array;
    Q->sign = '+';

    big_int *R = big_int_get("0"); //Остаток, результат, обозначается за R

    unsigned short no_meaning_zero = 256; //0000000123
    for (int index = 8; index >= 0; --index)
    {
        if (MAS_POW2[index] <= dividend->number[dividend->length - 1])
        {
            no_meaning_zero = MAS_POW2[index];
            break;
        }
    }

    {
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
    }

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
    big_int *res = big_int_mod_help(number, modulus);
    number->sign = sign_number;
    modulus->sign = sign_modulus;
    if (number->sign == '-')
    {
        if (res->length > 1 || res->number[0] != 0)
        {
            res->sign = '-';
        }
    }
    big_int_dlz(res);
    return res;
}


big_int *big_int_rnd(int byte_count) //
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


big_int *big_int_rnd_odd(int byte_count) //
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

    unsigned char pow_2 = 128;
    long long int cnt_power_two = 0;
    char exit = 0;
    for (int i = 0; i < power->length; ++i)
    {
        if (exit)
        {
            break;
        }
        unsigned short pow2= 1;
        for (; pow2 < 255; pow2 <<= 1)
        {
            if ((power->number[i] & pow2))
            {
                exit = 1;
                break;
            }
            else
            {
                cnt_power_two += 1;
            }
        }
    } //Теперь мы знаем сколько степеней двойки содержится в числе = cnt_power_two, ну или количество нулей в конце

    char first_one = 0;
    for (int i = power->length - 1; i >= 0; --i) //(cnt_power_two  + 7)/8
    {
        short pow2 = 128;
        char bit = 7;
        for (; pow2 >= 1; pow2 >>= 1)
        {
            if (power->number[i] & pow2)
            {
                first_one = 1;
                big_int *new_res = big_int_karatsuba_mult2(res, res); //Возводим в квадрат
                big_int_swap2(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_mod(res, modulus); // Берем модуль
                big_int_swap2(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_karatsuba_mult2(res, num); //Домнажаем на изначальное число так как щас 1(нечетное число)
                big_int_swap2(new_res, res);
                big_int_free(&new_res);

                new_res = big_int_mod(res, modulus); //Снова модуль
                big_int_swap2(new_res, res);
                big_int_free(&new_res);
            }
            else
            {
                if (first_one)
                {
                    big_int *new_res = big_int_karatsuba_mult2(res, res); //Здесь просто возводим в квадрат, так как четное(0)
                    big_int_swap2(new_res, res);
                    big_int_free(&new_res);

                    new_res = big_int_mod(res, modulus);
                    big_int_swap2(new_res, res);
                    big_int_free(&new_res);
                }
            }
        }
    }
    big_int_dlz(res);
    return res;
}

//big_int_witness_to_prime
static int big_int_witness_to_prime(big_int *number, big_int *number_without_two_in_pow, big_int *witness_num, long long int cnt_power_two) //
{
    big_int *one = big_int_get("1"); //Создаем единицу чтобы ее потом вычитать
    big_int *negative_one = big_int_sub1(number, one); //Минус 1 в кольце вычетов по основанию number
    long long int count = 1; //Для контроля степени 2 в числе д
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


int big_int_miller_rabin(big_int *number, int count_of_check) //
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

    big_int_sub2(number_without_two_in_pow, one); //вычитаем из числа number_without_two_in_pow единцу

    for (int i = 0; i < number->length; ++i)
    {
        if (exit)
        {
            break;
        }
        unsigned short pow2= 1;
        for (; pow2 < 255; pow2 <<= 1)
        {
            if ((number_without_two_in_pow->number[i] & pow2))
            {
                exit = 1;
                break;
            }
            else
            {
                cnt_power_two += 1;
            }
        }
    } //Теперь мы знаем сколько степеней двойки содержится в числе = cnt_power_two
    big_int_shft_r2(number_without_two_in_pow, cnt_power_two); //Выносим из под д степень 2

    for (int check = 0; check < count_of_check; ++check)
    {
        srand(time(NULL) + rand());
        int generate_len = rand() % number->length;
        big_int *witness_num = big_int_rnd(generate_len + !generate_len); //Выбираем свидетеля простоты
        if (number->length == 1)
        {
            big_int_free(&witness_num);
            int generate_len = (int)(rand()) % number->number[0];
            witness_num = big_int_get10(generate_len + !generate_len);
        }
        if (!big_int_witness_to_prime(number, number_without_two_in_pow, witness_num, cnt_power_two)) // number - само число;    number_without_two_in_pow - число без степеней 2;
        {                                                                                             // witness_num - свидетель простоты;      cnt_power_two - количество 2 в разложении number;
            big_int_free2(3, &witness_num, &number_without_two_in_pow, &one);
            return 0;
        }
        big_int_free(&witness_num);
    }
    big_int_free2(2, &number_without_two_in_pow, &one);
    return 1;
}


big_int *big_int_get_prime(int byte_len, int tst_count)
{
    big_int *rnd_digit = big_int_rnd_odd(byte_len);
    while (!big_int_miller_rabin(rnd_digit, tst_count))
    {
        big_int_free(&rnd_digit);
        rnd_digit = big_int_rnd_odd(byte_len);
    }
    return rnd_digit;
}