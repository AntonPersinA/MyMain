//
// Created by anton on 27.10.23.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "big_int/big_int.h"
#include "big_int_test.h"
#include <time.h>
#include <stdarg.h>
#include <limits.h>

int main(){
    big_int *n1;
    big_int *n2;
    big_int *n3;

    n1 = big_int_get("1");
    n2 = big_int_get("10");

//    for(int i = 0; i <= 3277607; ++i){
//        if(i == 32767){
//            printf("n1  = ");
//            big_int_print(n1);
//            printf("n2  = ");
//            big_int_print(n2);
//        }
//        big_int *n3;
//        n3 = big_int_add1(n1,n2);
//        big_int_add2(n2,n1);
//        if(!big_int_equal(n2,n3)){
//            printf("n1s = ");
//            big_int_print(n2);
//            printf("tru = ");
//            big_int_print(n3);
//            big_int_free(n3);
//            printf("\n%d\n", i);
//            break;
//        }
//        big_int_free(n3);
//    }

    big_int_test_add();

//    n1 = big_int_get("00000010"); //1111111111111111
//    n2 = big_int_get("1111111111111111"); //00000010
//
//    n3 = big_int_add1(n1,n2);
//
//    printf("n1 = ");
//    big_int_print(n1);
//    printf("n2 = ");
//    big_int_print(n2);
//    big_int_add2(n1,n2);
//    printf("n3 add2 = ");
//    big_int_print(n1);
//
//    printf("n3 add1 = ");
//    big_int_print(n3);

    big_int_free(n1);
    big_int_free(n2);
}

