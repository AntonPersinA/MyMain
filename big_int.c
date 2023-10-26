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
            int bit = 128;
            for(int j = 7; j >=0; --j) {
                printf("%d", (bit&(number->number[i * sizeof(number->number[0])]))!=0);
                bit >>=1;
            }
        printf(" ");
    }
    printf("\n");
}


void big_int_dlz(big_int *n){
    unsigned int i = n->length-1;
    while((i>0) && (n->number[i]==0)){
        --i;
    }
    if (i != n->length-1){
        n->length = i+1;
        n->number = realloc(n->number, n->length);
        if (n->number == NULL){printf("memory error in big_int_dlz\n");return;}
    }
}


char big_int_equal(big_int *n1, big_int *n2){
    if (n1->length != n2->length){return 0;}
    for(int i = 0; i < n1->length; ++i){
        if (n1->number[i] != n2->number[i]){return 0;}
    }
    return 1;
}


void big_int_free(big_int *n){
    free(n->number);
    free(n);
}


void big_int_swap(big_int *n1, big_int *n2){
    unsigned int len = n1->length;
    unsigned char *num = calloc(len, sizeof(unsigned char));
    for(int i = 0; i < len; ++i){
        num[i] = n1->number[i];
    }
    n1->number = realloc(n1->number, n2->length);
    for(int i = 0; i < n2->length; ++i){
        n1->number[i] = n2->number[i];
    }
    n2->number = realloc(n2->number, n1->length);
    for(int i = 0; i < n1->length; ++i){
        n2->number[i] = num[i];
    }
    n1->length = n2->length;
    n2->length = len;
    free(num);
}