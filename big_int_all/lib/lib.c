
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "../test/test.h"


char *bin_str(long long int a)
{
    int minus = a < 0 ? 1 : 0;
    a = a < 0 ? -a : a;
    if (a > 1234567890123456789) {
        printf("\nERRRROOOOORRRRR bin_str function           eeeeeeeerrrrrrrrrrrrrrrroooooooooooooorrrrrrrrrrrrr\n\n");
        a = 1;
    }
    if (a == 0) {
        char *str = calloc(2, sizeof(char));  // Выделяем пространство под '0' и окончание строки '\0'
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    long long int c = 1, i = 0;
    for (; c <= a; ++i) {
        c *= 2;
    }
    char *str = calloc(i + 3, sizeof(char)); //redo
    str[0] = (minus == 1) ? '-' : '+';
    c >>= 1;
    for (long long int j = 1; j < i + 1; ++j)
    {
        if (c <= a) {
            str[j] = '1';
            a -= c;
            c >>= 1;
        } else {
            str[j] = '0';
            c >>= 1;
        }
    }
    *(str + i + 1) = '\0';
    return str;
}