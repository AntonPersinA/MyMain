//
// Created by anton on 27.10.23.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "big_int/big_int.h"
#include "big_int_test.h"
#include <time.h>
#include <stdarg.h>
#include <limits.h>


char *bin_int(int a)
{
    int minus = a < 0 ? 1 : 0;
    a = a < 0 ? -a : a;
    if(a == 0)
    {
        char *str = calloc(1, sizeof(char));
        *(str+0) = *"0";
        return str;
    }
    int c = 1, i = 0;
    for (; c <= a; ++i)
    {
        c *= 2;
    }
    char *str = calloc(i, sizeof(char));
    str[0] = minus == 1 ? *"-" : *"+";
//    printf("str = ");
//    printf("%c", str[0]);
    c>>=1;
    for (int j = 1; j <= i; ++j)
    {
        if (c<=a)
        {
            str[j] = *"1";
            a-=c;
            c>>=1;
        }
        else
        {
            str[j] = *"0";
            c>>=1;
        }
//        printf("%c", str[j]);
    }
//    printf("\n");
    return str;
}

int test(int a)
{
    int digit1 = -10;
    int digit2 = -19;
    for(digit1 = -a; digit1 <= a; ++digit1)
    {
        for(digit2 = a; digit2 >= -a; --digit2)
        {
            int answer = digit1 + digit2;

            char *str1 = bin_int(digit1);
            char *str2 = bin_int(digit2);
            char *str_ans = bin_int(answer);

            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *ans = big_int_add1(n1, n2);
            big_int *ans_real = big_int_get(str_ans);

            big_int_dlz(ans);
            big_int_dlz(ans_real);
            if (big_int_equal_sgn(ans, ans_real) == 0){
                printf("n1 = ");
                big_int_print(n1);
                printf("n2 = ");
                big_int_print(n2);
                printf("n3 myy = ");
                big_int_print(ans);
                printf("n3 ans = ");
                big_int_print(ans_real);
                printf("equal sgn = %d\n\n\n\n\n\n", big_int_equal_sgn(ans, ans_real));
                big_int_free(n1);
                big_int_free(n2);
                big_int_free(ans);
                big_int_free(ans_real);
                free(str1);
                free(str2);
                free(str_ans);
                return 1;
            }
            big_int_free(n1);
            big_int_free(n2);
            big_int_free(ans);
            big_int_free(ans_real);
            free(str1);
            free(str2);
            free(str_ans);
        }
    }
}


int test2(int a)
{
    int digit1 = -10;
    int digit2 = -19;
    for(digit1 = -a; digit1 <= a; ++digit1)
    {
        for(digit2 = a; digit2 >= -a; --digit2)
        {
            int answer = digit1 + digit2;

            char *str1 = bin_int(digit1);
            char *str2 = bin_int(digit2);
            char *str_ans = bin_int(answer);


            big_int *n1 = big_int_get(str1);
            big_int *n2 = big_int_get(str2);
            big_int *ans_real = big_int_get(str_ans);
            big_int *help = big_int_copy(n1);

            big_int_add2(n1,n2);//n1+=n2
//
            big_int_dlz(ans_real);
            if (big_int_equal_sgn(n1, ans_real) == 0){
                printf("str1=%s\n",str1);
                printf("str2=%s\n",str2);
                printf("n1 = ");
                big_int_print(help);
                printf("n2 = ");
                big_int_print(n2);
                printf("n3 myy = ");
                big_int_print(n1);
                printf("n3 ans = ");
                big_int_print(ans_real);
//                printf("equal sgn = %d\n\n\n\n\n\n", big_int_equal_sgn(n1, ans_real));
//                big_int_free(n1);
//                big_int_free(n2);
//                big_int_free(ans_real);
//                big_int_free(help);
//                free(str1);
//                free(str2);
//                free(str_ans);
                return 1;
            }
            big_int_free(help);
            big_int_free(n1);
            big_int_free(n2);
            big_int_free(ans_real);
            free(str1);
            free(str2);
            free(str_ans);
        }
    }
}
int main() {

    big_int *n1 = big_int_get("1111111110000000011111111");
    big_int *n2 = big_int_get("0111111111111111111111110");


    printf("n1 = ");
    big_int_print(n1);

    printf("n2 = ");
    big_int_print(n2);

    big_int_fastsub2(n1,n2);

    printf("n1 before = ");
    big_int_print(n1);

    big_int_free(n1);
    big_int_free(n2);

    return 0;
}