
#include <stdlib.h>

#include "lib.h"
#include "../test/test.h"


char *bin_str(int a)
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
    }
    return str;
}