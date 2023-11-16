//
// Created by anton on 16.11.23.
//


#include <gmp.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    mpf_t re;
    mpf_t im;
} complex1;

typedef complex1* vcomplex1;

void add(mpf_t a_re, mpf_t a_im, mpf_t b_re, mpf_t b_im, mpf_t res_re, mpf_t res_im) {
    mpf_add(res_re, a_re, b_re);
    mpf_add(res_im, a_im, b_im);
}

void sub(mpf_t a_re, mpf_t a_im, mpf_t b_re, mpf_t b_im, mpf_t res_re, mpf_t res_im) {
    mpf_sub(res_re, a_re, b_re);
    mpf_sub(res_im, a_im, b_im);
}

void mul(mpf_t a_re, mpf_t a_im, mpf_t b_re, mpf_t b_im, mpf_t res_re, mpf_t res_im) {
    mpf_t temp1, temp2, temp3;
    mpf_inits(temp1, temp2, temp3, NULL);

    mpf_mul(temp1, a_re, b_re);
    mpf_mul(temp2, a_im, b_im);
    mpf_sub(res_re, temp1, temp2);

    mpf_mul(temp1, a_re, b_im);
    mpf_mul(temp2, a_im, b_re);
    mpf_add(res_im, temp1, temp2);

    mpf_clears(temp1, temp2, temp3, NULL);
}

vcomplex1 fft1(const vcomplex1 A, int size) {
    mpf_t PI;
    mpf_init_set_d(PI, M_PI);

    int n = size;
    int bits = (int)ceil(log2(n));

    int* rev = (int*)malloc(sizeof(int) * n);
    // Вычисление обратной последовательности
    for (int i = 0; i < n; ++i) {
        rev[i] = 0;
        for (int j = 0; j < bits; ++j)
            if ((i >> j) & 1)
                rev[i] |= 1 << (bits - 1 - j);
    }

    vcomplex1 cur = (vcomplex1)malloc(sizeof(complex1) * n);
    for (int i = 0; i < n; i++) {
        mpf_set(cur[i].re, A[rev[i]].re);
        mpf_set(cur[i].im, A[rev[i]].im);
    }

    // Вычисление корней единицы
    vcomplex1 roots = (vcomplex1)malloc(sizeof(complex1) * n);
    for (int i = 0; i < n; i++) {
        mpf_t temp;
        mpf_init(temp);
        mpf_div_ui(temp, PI, i + 1);
        mpf_mul_ui(temp, temp, -2);

        mpf_cos(roots[i].re, temp);
        mpf_sin(roots[i].im, temp);

        mpf_clear(temp);
    }

    // FFT преобразование
    for (int len = 1; len < n; len <<= 1) {
        vcomplex1 ncur = (vcomplex1)malloc(sizeof(complex1) * n);
        int rstep = n / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                mpf_t val_re, val_im;
                mpf_inits(val_re, val_im, NULL);
                mul(roots[i * rstep].re, roots[i * rstep].im, cur[p1 + len].re, cur[p1 + len].im, val_re, val_im);
                add(cur[p1].re, cur[p1].im, val_re, val_im, ncur[pdest].re, ncur[pdest].im);
                sub(cur[p1].re, cur[p1].im, val_re, val_im, ncur[pdest + len].re, ncur[pdest + len].im);
                mpf_clears(val_re, val_im, NULL);
                pdest++, p1++;
            }
            pdest += len;
        }
        free(cur);
        cur = ncur;
    }

    mpf_clear(PI);

    for (int i = 0; i < n; i++) {
        mpf_clear(roots[i].re);
        mpf_clear(roots[i].im);
    }

    free(rev);
    free(roots);

    return cur;
}


















































































































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


















#include <mpfr.h>
#include <math.h>

typedef struct {
    mpfr_t re;
    mpfr_t im;
} complex1;

typedef complex1* vcomplex1;

vcomplex1 fft1mpfr(const vcomplex1 A, int size) {
// Initialize PI
    mpfr_t PI;
    mpfr_init_set_d(PI, M_PI, MPFR_RNDN);

    int n = size;
    int bits = (int) ceil(log2(n));

// Reverse bit order
    int *rev = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        rev[i] = 0;
        for (int j = 0; j < bits; ++j)
            if ((i >> j) & 1)
                rev[i] |= 1 << (bits - 1 - j);
    }

// Calculate roots of unity
    vcomplex1 roots = (vcomplex1) malloc(sizeof(complex1) * n);
    for (int i = 0; i < n; i++) {
        mpfr_t temp;
        mpfr_init(temp);
        mpfr_div_ui(temp, PI, i + 1, MPFR_RNDN);
        mpfr_mul_si(temp, temp, -2, MPFR_RNDN);

        mpfr_cos(roots[i].re, temp, MPFR_RNDN);
        mpfr_sin(roots[i].im, temp, MPFR_RNDN);
        mpfr_clear(temp);
    }

    vcomplex1 cur = (vcomplex1) malloc(sizeof(complex1) * n);
    for (int i = 0; i < n; i++) {
        mpfr_set(cur[i].re, A[rev[i]].re, MPFR_RNDN);
        mpfr_set(cur[i].im, A[rev[i]].im, MPFR_RNDN);
    }

    for (int len = 1; len < n; len <<= 1) {
        vcomplex1 ncur = (vcomplex1) malloc(sizeof(complex1) * n);
        int rstep = n / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                complex1 val, mult;
                mpfr_t temp_re, temp_im;

                mpfr_init(val.re);
                mpfr_init(val.im);
                mpfr_init(mult.re);
                mpfr_init(mult.im);
                mpfr_init(temp_re);
                mpfr_init(temp_im);

                mpfr_mul(mult.re, roots[i * rstep].re, cur[p1 + len].re, MPFR_RNDN);  // re*re
                mpfr_mul(temp_im, roots[i * rstep].im, cur[p1 + len].im, MPFR_RNDN);  // im*im
                mpfr_sub(val.re, mult.re, temp_im, MPFR_RNDN);  // re*re - im*im

                mpfr_mul(mult.re, roots[i * rstep].re, cur[p1 + len].im, MPFR_RNDN);  // re*im
                mpfr_mul(temp_im, roots[i * rstep].im, cur[p1 + len].re, MPFR_RNDN);  // im*re
                mpfr_add(val.im, mult.re, temp_im, MPFR_RNDN);  // re*im + im*re

                mpfr_add(ncur[pdest].re, cur[p1].re, val.re, MPFR_RNDN);
                mpfr_sub(ncur[pdest + len].re, cur[p1].re, val.re, MPFR_RNDN);
                mpfr_add(ncur[pdest].im, cur[p1].im, val.im, MPFR_RNDN);
                mpfr_sub(ncur[pdest + len].im, cur[p1].im, val.im, MPFR_RNDN);

                mpfr_clear(val.re);
                mpfr_clear(val.im);
                mpfr_clear(mult.re);
                mpfr_clear(mult.im);
                mpfr_clear(temp_re);
                mpfr_clear(temp_im);

                pdest++, p1++;
            }
            pdest += len;
        }
        free(cur);
        cur = ncur;
    }

    mpfr_clear(PI);
    for (int i = 0; i < n; i++) {
        mpfr_clear(roots[i].re);
        mpfr_clear(roots[i].im);
    }

    free(rev);
    free(roots);

    return cur;
}