
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"
#include "../test/test.h"


char *bin_str(long long a) {
    int minus = a < 0 ? 1 : 0;
    a = a < 0 ? -a : a;
    if (a > 1234567890123456789) {
        printf("\nERRRROOOOORRRRR bin_str function           eeeeeeeerrrrrrrrrrrrrrrroooooooooooooorrrrrrrrrrrrr\n\n");
    }
    a %= 1234567890123456789;
    if (a == 0) {
        char *str = calloc(1, sizeof(char));
        *(str + 0) = *"0";
        return str;
    }
    long long c = 1, i = 0;
    for (; c <= a; ++i) {
        c *= 2;
    }
    char *str = calloc(i, sizeof(char));
    str[0] = minus == 1 ? *"-" : *"+";
    c >>= 1;
    for (long long j = minus; j < i + minus; ++j) {
        if (c <= a) {
            str[j] = *"1";
            a -= c;
            c >>= 1;
        } else {
            str[j] = *"0";
            c >>= 1;
        }
    }
    return str;
}














#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

//typedef double complex cd;
//typedef cd* vcd;
//
//vcd fft(const vcd as, int size)
//{
//    int n = size;
//    int k = 0;
//    while ((1 << k) < n) k++;
//    int* rev = (int*)malloc(sizeof(int) * n);
//
//    rev[0] = 0;
//    int high1 = -1;
//    for (int i = 1; i < n; i++) {
//        if ((i & (i - 1)) == 0)
//            high1++;
//        rev[i] = rev[i ^ (1 << high1)];
//        rev[i] |= (1 << (k - high1 - 1));
//    }
//
//    vcd roots = (vcd)malloc(sizeof(cd) * n);
//    for (int i = 0; i < n; i++) {
//        double alpha = 2 * M_PI * i / n;
//        roots[i] = cos(alpha) + I * sin(alpha);
//    }
//
//    vcd cur = (vcd)malloc(sizeof(cd) * n);
//    for (int i = 0; i < n; i++)
//        cur[i] = as[rev[i]];
//
//    for (int len = 1; len < n; len <<= 1) {
//        vcd ncur = (vcd)malloc(sizeof(cd) * n);
//        int rstep = n / (len * 2);
//        for (int pdest = 0; pdest < n;) {
//            int p1 = pdest;
//            for (int i = 0; i < len; i++) {
//                cd val = roots[i * rstep] * cur[p1 + len];
//                ncur[pdest] = cur[p1] + val;
//                ncur[pdest + len] = cur[p1] - val;
//                pdest++, p1++;
//            }
//            pdest += len;
//        }
//        free(cur);
//        cur = ncur;
//    }
//
//    free(rev);
//    free(roots);
//
//    return cur;
//}