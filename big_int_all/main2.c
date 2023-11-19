//
// Created by anton on 27.10.23.
//

#include "test/test.h"
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

#include "lib/lib.h"


void test_kar()
{
    big_int *n1 = big_int_get("1111111000011111111000100010000000000111111100001111111100010001000000000011111110000111111110001000100"); //11110000111111110001000100000000
    big_int *n2 = big_int_get("1010000011111111000010100000000010100000111111110000101"); //10100000111111110000101000000000
//    printf("n1 = ");
//    big_int_print(n1);
//    printf("n2 = ");
//    big_int_print(n2);
//    printf("\n");
//
//
//
    //    printf("n1 = ");
    //    big_int_print(n1);
    //    printf("n2 = ");
    //    big_int_print(n2);

    big_int *n4 = big_int_mult1(n1,n2);
    big_int *n3 = big_int_karatsuba_mult2(n1,n2);

    printf("\nkar = ");
    big_int_print(n3);
    printf("mul = ");
    big_int_print(n4);


//    printf("n1 = ");
//    big_int_print(n1);
//    printf("n2 = ");
//    big_int_print(n2);
//    printf("\n");


    printf("equal = %d\n", big_int_equal_sgn(n3,n4));

    big_int_free2(4, n1, n2, n3,n4);

}


int main() {

test_kar();
//    test_all(41);
}
