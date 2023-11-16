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
#include <gmp.h>

#include "big_int/big_int.h"
#include "test/test.h"
#include "lib/lib.h"

#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdio.h>

typedef long double complex cd;
typedef cd* vcd;


//#include <gmp.h>
//#include <math.h>
//
//typedef struct {
//    mpf_t re;
//    mpf_t im;
//} complex1;
//
//typedef complex1* vcomplex1;
//
//
//vcomplex1 fft1gmp(const vcomplex1 A, int size)
//{
//    // Initialize PI
//    mpf_t PI;
//    mpf_init_set_d(PI, M_PI);
//
//    int n = size;
//    int bits = (int)ceil(log2(n));
//
//    // Reverse bit order
//    int* rev = (int*)malloc(sizeof(int) * n);
//    for (int i = 0; i < n; ++i) {
//        rev[i] = 0;
//        for (int j = 0; j < bits; ++j)
//            if ((i >> j) & 1)
//                rev[i] |= 1 << (bits - 1 - j);
//    }
//
//    // Calculate roots of unity
//    vcomplex1 roots = (vcomplex1)malloc(sizeof(complex1) * n);
//    for (int i = 0; i < n; i++) {
//        mpf_t temp;
//        mpf_init(temp);
//        mpf_div_ui(temp, PI, i + 1);
//        mpf_mul_ui(temp, temp, -2);
//
//        compute_cosine(roots[i].re, temp);
//        mpf_sin(roots[i].im, temp);
//
//        mpf_clear(temp);  // Clear the temporary variable
//    }
//
//    // FFT Code goes here. The details depend on whether you're using the
//    // Cooley-Tukey algorithm, or another algorithm. If you're using a
//    // recursive approach, you'll want to break your input array down into
//    // smaller chunks.
//
//    // Cleanup
//    mpf_clear(PI);
//
//    for (int i = 0; i < n; i++) {
//        mpf_clear(roots[i].re);
//        mpf_clear(roots[i].im);
//    }
//
//    free(rev);
//    free(roots);
//
//    return NULL;  // Returning NULL for now, since FFT hasn't been implemented
//}



#include <mpfr.h>
#include <math.h>

typedef struct {
    mpfr_t re;
    mpfr_t im;
} complex1;

typedef complex1* vcomplex1;




vcomplex1 fft1mpfr(const vcomplex1 A, int size)
{
    // Initialize PI
    mpfr_t PI;
    mpfr_init_set_d(PI, M_PI, MPFR_RNDN);

    int n = size;
    int bits = (int)ceil(log2(n));

    // Reverse bit order
    int* rev = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i) {
        rev[i] = 0;
        for(int j = 0; j < bits; ++j)
            if((i >> j) & 1)
                rev[i] |= 1 << (bits - 1 - j);
    }

    // Calculate roots of unity
    vcomplex1 roots = (vcomplex1)malloc(sizeof(complex1) * n);
    for(int i = 0; i < n; i++) {
        mpfr_t temp;
        mpfr_init(roots[i].re);
        mpfr_init(roots[i].im);
        mpfr_init(temp);

        mpfr_mul_ui(temp, PI, 2 * i, MPFR_RNDN);
        mpfr_div_ui(temp, temp, n, MPFR_RNDN);
        mpfr_mul_si(temp, temp, -1, MPFR_RNDN);

        mpfr_cos(roots[i].re, temp, MPFR_RNDN);
        mpfr_sin(roots[i].im, temp, MPFR_RNDN);
        mpfr_clear(temp);
    }


    vcomplex1 cur = (vcomplex1)malloc(sizeof(complex1) * n);
    for(int i = 0; i < n; i++){
        mpfr_init(cur[i].re);
        mpfr_init(cur[i].im);

        mpfr_set(cur[i].re, A[rev[i]].re, MPFR_RNDN);
        mpfr_set(cur[i].im, A[rev[i]].im, MPFR_RNDN);
    }

    for(int len = 1; len < n; len <<= 1) {
        vcomplex1 ncur = (vcomplex1)malloc(sizeof(complex1) * n);
        int rstep = n / (len * 2);
        for(int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for(int i = 0; i < len; i++) {
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
    for(int i = 0; i < n; i++) {
        mpfr_init(A[i].re);
        mpfr_init(A[i].im);

        mpfr_clear(roots[i].re);
        mpfr_clear(roots[i].im);
    }

    free(rev);
    free(roots);

    return cur;
}




void print_complex_array(vcomplex1 cur, int size)
{
    printf("Массив комплексных чисел:\n");
    for(int i = 0; i < size; i++)
    {
        char *re_str, *im_str;
        mpfr_exp_t re_exp, im_exp;

        re_str = mpfr_get_str(NULL, &re_exp, 10, 0, cur[i].re, MPFR_RNDN);
        im_str = mpfr_get_str(NULL, &im_exp, 10, 0, cur[i].im, MPFR_RNDN);

        printf("Элемент #%d: ", i+1);
        printf("%se%d + ", re_str, (int)re_exp);
        printf("%se%d * i\n", im_str, (int)im_exp);

        mpfr_free_str(re_str);
        mpfr_free_str(im_str);
    }
}



int init_my()
{
    int size = 8;  // выберите размер массива
    vcomplex1 A = (vcomplex1)malloc(sizeof(complex1) * size);

    // Инициализируйте массив A с некоторыми значениями
    for(int i = 0; i < 4; ++i) {
        mpfr_init_set_d(A[i].re, (float)(4.0 - i), MPFR_RNDN); // например, устанавливаем вещественную часть равной i+1
        mpfr_init_set_d(A[i].im, 0.0, MPFR_RNDN); // устанавливаем мнимую часть равной 0
    }

    for(int i = 4; i < size; ++i) {
        mpfr_init_set_d(A[i].re, 0.0, MPFR_RNDN); // например, устанавливаем вещественную часть равной i+1
        mpfr_init_set_d(A[i].im, 0.0, MPFR_RNDN); // устанавливаем мнимую часть равной 0
    }

    printf("Исходный массив:\n");
    print_complex_array(A, size);    // печатаем исходный массив

    // Вызываем FFT
    vcomplex1 result = fft1mpfr(A, size);

    // Печатаем результат FFT
    printf("\nРезультат FFT:\n");
    print_complex_array(result, size);

    // Освобождаем память
    for(int i = 0; i < size; ++i) {
        mpfr_clear(A[i].re);
        mpfr_clear(A[i].im);
        mpfr_clear(result[i].re);
        mpfr_clear(result[i].im);
    }
    free(A);
    free(result);

    return 0;
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


int float_test()
{

    mpf_t num1, num2, sum;

    // Инициализация чисел
    mpf_init(num1);
    mpf_init(num2);
    mpf_init(sum);

    // Установка значений для num1 и num2
    mpf_set_d(num1, 3.14);
    mpf_set_str(num2, "2.71828", 10);

    // Сложение num1 и num2
    mpf_add(sum, num1, num2);

    // Вывод результата
    gmp_printf("Сумма: %.10Ff\n", sum);

    // Освобождение ресурсов
    mpf_clear(num1);
    mpf_clear(num2);
    mpf_clear(sum);

    return 0;
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




vcd elementwise_multiply(vcd a, vcd b, int n) {
    vcd result = (vcd)malloc(sizeof(cd) * n);
    if (result == NULL) {
        fprintf(stderr, "Failed to allocate memory for result array\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        result[i] = a[i] * b[i];
    }
    return result;
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
