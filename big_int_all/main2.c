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
    int c = 1;
    int i = 0;
    for (; c < a; ++i)
    {
        c*=2;
    }
    char *str = calloc(i, sizeof(char));
    c>>=1;
    for (int j = 0; j < i; ++j)
    {
        if (c <= a)
        {
            str[j] = *"1";
            a-=c;
            c>>=1;
        }
        else{
            str[j] = *"0";
            c>>=1;
        }
    }
    return str;
}


int main() {
    int digit1 = 3;
    int digit2 = 2;
    int answer = digit1 - digit2;

    big_int *n1 = big_int_get(bin_int(digit1));
    big_int *n2 = big_int_get(bin_int(digit2));
    big_int *ans = big_int_get(bin_int(answer));

    big_int_print(n1);
    big_int_print(n2);
    big_int_print(ans);

    big_int_free(n1);
    big_int_free(n2);
    big_int_free(ans);
}