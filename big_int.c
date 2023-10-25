#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "homework.h"
#include "homework.h"
#include "big_int.h"
#include <time.h>
#include <stdarg.h>
#include <limits.h>




big_int* big_int_get(char *bin_number){
    int bit_len = strlen(bin_number);
    big_int *res = (big_int *)malloc(sizeof(big_int));
    if (res == NULL){printf("memory error in big_int_get\n");return NULL;}
    res->length = (bit_len+7)>>3;
    res->number = calloc(res->length, sizeof(res->number[0]));
    if (res->number == NULL){printf("memory error in big_int_get\n");return NULL;}
    for (int i = 0; i < bit_len; ++i){
        res->number[i/8] += (bin_number[bit_len - i - 1] - '0') << (i%8);
    }
    return res;
}


void big_int_print(big_int *number){
    for(int i = number->length - 1; i>=0; --i){
        for(int j = 0; j < sizeof(number->number[0]);++j){
            int leading_one = 128;
            for(int print_01 = 7; print_01 >=0; --print_01) {
                printf("%d", leading_one&(number->number[j + i * sizeof(number->number[0])])?1:0);
                leading_one >>=1;
            }
        }
        printf(" ");
    }
    printf("\n");
}