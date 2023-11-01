//
// Created by anton on 25.10.23.
//
#pragma once

typedef struct big_int{
    unsigned char* number;
    unsigned int length;
} big_int;

big_int* big_int_get(char *bin_number);

void big_int_print(big_int *number);

void big_int_dlz(big_int *n);

char big_int_equal(big_int *n1, big_int *n2);

void big_int_free(big_int *n);

void big_int_swap(big_int *n1, big_int *n2);

big_int* big_int_copy(big_int *x);

big_int *big_int_add1(big_int *n1, big_int *n2);

void big_int_add2(big_int *n1, big_int *n2);

void big_int_shft_l(big_int *n1);

void big_int_shft_r(big_int *n1);
