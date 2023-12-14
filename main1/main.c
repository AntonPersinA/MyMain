#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "homework.h"
#include <time.h>
#include <stdarg.h>
#include <limits.h>


#define sq(A, B) "sq of rectangle ("#A") * ("#B")\n"
#define test(gg) x##gg


//clock_t start, end;
//long long x;
//start = clock();
//x = int_pow_n(3, int_pow_n(8,10)-1);
//end = clock();
//printf("%lld\n%f\n", x, ((double)end - start)/CLOCKS_PER_SEC);


#define size 10



unsigned long long int factorial(int x)
{
    unsigned long long int res = 1;
    for (int i = 2; i <= x; ++i)
    {
        res *= i;
    }
    return res;
}




long double sinx_m(long double x, long int tochnost)
{

    long double res = 0;
    long double x_pow = x;
    long double one = -1;
    long double my_10 = 0.1;
    for (int i = 1; i < tochnost; ++i)
    {
        my_10 *= 0.1;
    }
    int t = 1;
    for (;; ++t)
    {
        x_pow *= x_pow;
        if (- x_pow + my_10 >= 0)
        {
            break;
        }
    }
    printf("t = %d\n", t);
    for (int i = 1; i < t + 2; i += 2)
    {
        res += ((long double)x_pow / (long double)factorial(i));
        x_pow *= one * 0.01;
        x_pow *= 0.01;
    }
    return res;
}


int main()
{
    printf("sin() = %.20Lf\n", sinx_m(0.1, 20));
}





