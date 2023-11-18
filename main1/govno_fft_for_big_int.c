//
// Created by anton on 27.10.23.
//


#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#include <string.h>
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





int fft_test()
{
    int size = 8;//
    vcd complex_data = (vcd) malloc(sizeof(cd) * size);//

    complex_data[0] = 1.0;
    complex_data[1] = 0.0;
    complex_data[2] = 0.0;
    complex_data[3] = 2.0;

    for (int i = 4; i < size; ++i)
    {
        complex_data[i] = 0.0 + I*0.0;
    }/////////////////////////////////////////////////////////

    vcd res = fft1(complex_data, size);


    printf("fft(res1)  = ");

    long double pr;
    for (int i = 0; i < size; ++i)
    {
        pr = res[i];
        printf("%Lf  ", pr);
    }

    printf("\n\n");


    vcd complex_data2 = (vcd) malloc(sizeof(cd) * size);
////////////////////////////////
    complex_data2[0] = 3.0;
    complex_data2[1] = 0.0;
    complex_data2[2] = 0.0;
    complex_data2[3] = 1.0;
    for (int i = 4; i < size; ++i)
    {
        complex_data2[i] = 0.0 + I*0.0;
    }

    vcd res2 = fft1(complex_data2, size);/////////////////////////////////////


    printf("fft(res2)  = ");

    long double pr2;
    for (int i = 0; i < size; ++i)
    {
        pr2 = res2[i];
        printf("%Lf  ", pr2);
    }

    printf("\n\n");




    vcd mul_res;

    mul_res = elementwise_multiply(res, res2, size);//////////////////////////////////////

    printf("(fr1,fr2)  = ");

    for (int i = 0; i < size; ++i)
    {
        pr2 = mul_res[i];
        printf("%Lf  ", pr2);
    }

    printf("\n\n");




    vcd res_otv = ifft1(mul_res, size);

    printf("ifft(mul)  = ");


    for (int i = 0; i < size; ++i)
    {
        pr = res_otv[i];
        printf("%Lf  ", pr);
    }

    printf("\n");

    free(complex_data);
    free(complex_data2);
    free(res);
    free(mul_res);
    free(res2);
    free(res_otv);
}









long double *mul_polynomials(long double *a,
                             long double *b,
                             long long int size_a,
                             long long int size_b)
{

    long long int new_size = size_b + size_a - 1;
    long double pr = 0.0;
    long long k = 1;
    while (k < new_size)
    {
        k *= 2;
    }
    new_size = k;



    vcd complex_data = (vcd) malloc(sizeof(cd) * new_size);
    for (int i = 0; i < size_a; ++i)
    {
        complex_data[i] = a[i];
    }
    for (int i = size_a; i < new_size; ++i)
    {
        complex_data[i] = 0.0;
    }



    vcd res = fft1(complex_data, new_size);



    vcd complex_data2 = (vcd) malloc(sizeof(cd) * new_size);

    for (int i = 0; i < size_b; ++i)
    {
        complex_data2[i] = b[i];
    }
    for (int i = size_b; i < new_size; ++i)
    {
        complex_data2[i] = 0.0;
    }



    vcd res2 = fft1(complex_data2, new_size);



    vcd mul_res = elementwise_multiply(res, res2, new_size);

    vcd res_otv = ifft1(mul_res, new_size);

    long double *retruned_array = calloc(new_size, sizeof(long double));
    for (int i = 0; i < new_size; ++i)
    {
        retruned_array[i] = res_otv[i];
    }


    free(complex_data);
    free(complex_data2);
    free(res);
    free(mul_res);
    free(res2);
    free(res_otv);
    return retruned_array;
}

void print_array_polynomials(long double *array, long long int len_array)
{
    for (int i = 0; i < len_array; ++i)
    {
        printf("%Lf ", array[i]);
    }
    printf("\n");
}


void test_mul_pol()
{
    long long int size_a = 3;
    long long int size_b = 1;
    long double *a = calloc(size_a, sizeof(long double));
    long double *b = calloc(size_b, sizeof(long double));

    a[0] = 200;
    a[1] = -5;
    a[2] = 3;
    b[0] = 1000;
//    b[1] = 4;

    long double *output = mul_polynomials(a,b,size_a,size_b);

    print_array_polynomials(output, size_a + size_b - 1);
    free(a);
    free(b);
    free(output);
}





vcd big_int_to_complex(const big_int* bi)
{
    int n = bi->length;

    vcd complex_arr = (vcd)malloc(sizeof(cd) * n);

    for (int i = 0; i < n; ++i)
    {
        complex_arr[i] = bi->number[i] + I * 0.0;
    }

    return complex_arr;
}




int main() {

    big_int *n1 = big_int_getloop("00000001", 530);
    big_int *n2 = big_int_getloop("10000000", 1);

    big_int_fftmul(n1,n2);


    big_int_free2(2,n1,n2);

    return 0;
}
