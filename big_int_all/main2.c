//
// Created by anton on 27.10.23.
//


#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>
//#include <stdarg.h>
//#include <limits.h>

#include "big_int/big_int.h"
#include "test/test.h"
#include "lib/lib.h"

#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdio.h>

typedef long double complex cd;
typedef cd* vcd;


vcd fft1(const vcd as, int size)
{
    int n = size;
    int k = 0;
    while ((1 << k) < n) k++;
    int* rev = (int*)malloc(sizeof(int) * n);

    rev[0] = 0;
    int high1 = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0)
            high1++;
        rev[i] = rev[i ^ (1 << high1)];
        rev[i] |= (1 << (k - high1 - 1));
    }

    vcd roots = (vcd)malloc(sizeof(cd) * n);
    for (int i = 0; i < n; i++) {
        long double alpha = 2 * M_PI * i / n;
        roots[i] = cos(alpha) + I * sin(alpha);
    }

    vcd cur = (vcd)malloc(sizeof(cd) * n);
    for (int i = 0; i < n; i++)
        cur[i] = as[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vcd ncur = (vcd)malloc(sizeof(cd) * n);
        int rstep = n / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        free(cur);
        cur = ncur;
    }

    free(rev);
    free(roots);

    return cur;
}



vcd ifft1(const vcd as, int size)
{
    int n = size;
    int k = 0;
    while ((1 << k) < n) k++;
    int* rev = (int*)malloc(sizeof(int) * n);

    rev[0] = 0;
    int high1 = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0)
            high1++;
        rev[i] = rev[i ^ (1 << high1)];
        rev[i] |= (1 << (k - high1 - 1));
    }

    vcd roots = (vcd)malloc(sizeof(cd) * n);
    for (int i = 0; i < n; i++) {
        long double alpha = -2 * M_PI * i / n;  // Note the negative sign here
        roots[i] = cos(alpha) + I * sin(alpha);
    }

    vcd cur = (vcd)malloc(sizeof(cd) * n);
    for (int i = 0; i < n; i++)
        cur[i] = as[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vcd ncur = (vcd)malloc(sizeof(cd) * n);
        int rstep = n / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        free(cur);
        cur = ncur;
    }

    for (int i = 0; i < n; i++) {  // Divide by n, as inverse FFT needs this correction
        cur[i] /= n;
    }

    free(rev);
    free(roots);

    return cur;
}







void in_2_copy_1(long double *mas1, long double * mas2, int len){
    for (int i = 0; i < len; ++i){
        *(mas2+i) = *(mas1+i);
    }
}



int main() {
    vcd complex_data = (vcd) malloc(sizeof(cd) * 8);

    complex_data[0] = 4.0;
    complex_data[1] = 3.0;
    complex_data[2] = 2.0;
    complex_data[3] = 1.0;

    for (int i = 5; i < 8; ++i)
    {
        complex_data[i] = 0.0 + I*0.0;
    }

    vcd res = fft1(complex_data, 8);

    long double pr;
    for (int i = 0; i < 8; ++i)
    {
        pr = res[i];
        printf("%Lf  ", pr);
    }

    vcd res2 = ifft1(res, 8);

    printf("\n");

    for (int i = 0; i < 8; ++i)
    {
        pr = res2[i];
        printf("%Lf  ", pr);
    }

    printf("\n");

    free(complex_data);
    free(res);
    free(res2);
    return 0;
}
