//
// Created by anton on 27.10.23.
//


//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <stdarg.h>
//#include <limits.h>
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "big_int/big_int.h"
//#include "test/test.h"
//#include "lib/lib.h"


void test_kar()
{
    big_int *n1 = big_int_get("111100000000000000001111");//111100000000000000001111
    big_int *n2 = big_int_get("101000001111111100001010");//101000001111111100001010
    printf("n1 = ");
    big_int_print(n1);
    printf("n2 = ");
    big_int_print(n2);


    big_int *n4 = big_int_mult1(n1,n2);

    //    printf("n1 = ");
    //    big_int_print(n1);
    //    printf("n2 = ");
    //    big_int_print(n2);

    big_int *n3 = big_int_karatsuba(n1,n2);

    printf("kar = ");
    big_int_print(n3);
    printf("mul = ");
    big_int_print(n4);
}


int main() {

test_kar();

    return 0;
}
