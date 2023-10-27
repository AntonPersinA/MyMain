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

//    FILE *wfile = fopen("big_int_test.txt", "w");
//    FILE *rfile = fopen("big_int_test.txt", "r");

    big_int *n1;

    n1 = big_int_get("10001000");

    big_int_print(n1);

    big_int_test_add();

    big_int_free(n1);

//    fclose(wfile);
//    fclose(rfile);
}

