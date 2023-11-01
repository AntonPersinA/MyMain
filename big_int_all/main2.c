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

    n1 = big_int_get("1");
    n2 = big_int_get("10");

    for(int i = 0; i < 100; ++i){
        big_int *n3;
        n3 = big_int_add1(n1,n2);
        big_int_add2(n1,n2);
        if(!big_int_equal(n1,n3)){
            big_int_print(n1);
            big_int_print(n3);
            big_int_free(n3);
            break;
        }
        big_int_free(n3);
    }

    big_int_test_add();

    big_int_free(n1);
    big_int_free(n2);
}

