//
// Created by anton on 27.10.23.
//


#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <stdarg.h>
//#include <limits.h>

#include "big_int/big_int.h"
#include "test/test.h"
//#include "lib/lib.h"

int main() {

    test_all(258);

    big_int *n1 = big_int_get("11111111111111111111111111");

    big_int_print(n1);

    big_int_reget(n1, "+10");

    big_int_print(n1);

    big_int_free(n1);

    return 0;
}