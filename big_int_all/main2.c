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

//typedef long double complex cd;
//typedef cd* vcd;


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
#include <stdlib.h>
#include <tgmath.h>

typedef struct {
    mpfr_t re;
    mpfr_t im;
} complex1;

typedef complex1* vcomplex1;

//vcomplex1 fft1mpfr(const vcomplex1 as, int size, mpfr_prec_t prec) //прек это точность в битах
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
//    vcomplex1 roots = (vcomplex1)malloc(sizeof(complex1) * n);
//    for (int i = 0; i < n; i++) {
//        mpfr_t alpha;
//        mpfr_init2(alpha, prec);
//        mpfr_set_d(alpha, 2 * M_PI * i / n, MPFR_RNDN);
//        mpfr_cos(roots[i].re, alpha, MPFR_RNDN);
//        mpfr_sin(roots[i].im, alpha, MPFR_RNDN);
//        mpfr_clear(alpha);
//    }
//
//    vcomplex1 cur = (vcomplex1)malloc(sizeof(complex1) * n);
//    for (int i = 0; i < n; i++)
//        cur[i] = as[rev[i]];
//
//    for (int len = 1; len < n; len <<= 1) {
//        vcomplex1 ncur = (vcomplex1)malloc(sizeof(complex1) * n);
//        int rstep = n / (len * 2);
//        for (int pdest = 0; pdest < n;) {
//            int p1 = pdest;
//            for (int i = 0; i < len; i++) {
//                complex1 val;
//                mpfr_init2(val.re, prec);
//                mpfr_init2(val.im, prec);
//
//                mpfr_mul(val.re, roots[i * rstep].re, cur[p1 + len].re, MPFR_RNDN);
//                mpfr_sub(val.re, cur[p1].re, val.re, MPFR_RNDN);
//
//                mpfr_mul(val.im, roots[i * rstep].im, cur[p1 + len].im, MPFR_RNDN);
//                mpfr_add(val.im, cur[p1].im, val.im, MPFR_RNDN);
//
//                ncur[pdest] = val;
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


//int float_test()
//{
//
//    mpf_t num1, num2, sum;
//
//    // Инициализация чисел
//    mpf_init(num1);
//    mpf_init(num2);
//    mpf_init(sum);
//
//    // Установка значений для num1 и num2
//    mpf_set_d(num1, 3.14);
//    mpf_set_str(num2, "2.71828", 10);
//
//    // Сложение num1 и num2
//    mpf_add(sum, num1, num2);
//
//    // Вывод результата
//    gmp_printf("Сумма: %.10Ff\n", sum);
//
//    // Освобождение ресурсов
//    mpf_clear(num1);
//    mpf_clear(num2);
//    mpf_clear(sum);
//
//    return 0;
//}




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






//void in_2_copy_1(long double *mas1, long double * mas2, int len){
//    for (int i = 0; i < len; ++i){
//        *(mas2+i) = *(mas1+i);
//    }
//}







int main() {
    int size = 4;
    vcd complex_data = (vcd) malloc(sizeof(cd) * size);

    complex_data[0] = 40005542567887.0;
    complex_data[1] = 3546543245678878778.0;
    complex_data[2] = 124567890967544564632.0;
    complex_data[3] = 1345654532134567865.0;

    for (int i = 5; i < size; ++i)
    {
        complex_data[i] = 789854323456789.0 + I*0.0;
    }

    vcd res = fft1(complex_data, size);

    long double pr;
    for (int i = 0; i < size; ++i)
    {
        pr = res[i];
        printf("%Lf  ", pr);
    }

    printf("\n\n\n\n");

    vcd res2 = ifft1(res, size);

    printf("\n");

    for (int i = 0; i < size; ++i)
    {
        pr = res2[i];
        printf("%Lf  ", pr);
    }

    printf("\n");

    //надо создать еще одно уравнение и потом использовать уже мул поэлементно, после это ifft

    free(complex_data);
    free(res);
    free(res2);





    char *str1 = bin_str(40005542567887);

    big_int *n1 = big_int_get(str1);

    printf("len = %d\n\n", n1->length);

    big_int_free(n1);

    free(str1);

    return 0;
}
