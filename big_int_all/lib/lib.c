
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "../test/test.h"


char *bin_str(long long a)
{
    int minus = a < 0 ? 1 : 0;
    a = a < 0 ? -a : a;
    if (a > 1234567890123456789)
    {
        printf("\nERRRROOOOORRRRR bin_str function           eeeeeeeerrrrrrrrrrrrrrrroooooooooooooorrrrrrrrrrrrr\n\n");
    }
    a %= 1234567890123456789;
    if(a == 0)
    {
        char *str = calloc(1, sizeof(char));
        *(str+0) = *"0";
        return str;
    }
    long long c = 1, i = 0;
    for (; c <= a; ++i)
    {
        c *= 2;
    }
    char *str = calloc(i, sizeof(char));
    str[0] = minus == 1 ? *"-" : *"+";
    c>>=1;
    for (long long j = minus; j < i + minus; ++j)
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
    }
    return str;
}