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
//    big_int *n3;

    n1 = big_int_get("11111111");
    n2 = big_int_get("10");

//    printf("00000000 ");
    big_int_print(n1);

    big_int_shft_l(n1);

    big_int_print(n1);




    big_int_free(n1);
    big_int_free(n2);
}

