//
// Created by anton on 25.10.23.
//
#pragma once

typedef struct big_int{
    char sign;
    unsigned char *number;
    unsigned int length;
} big_int;

big_int* big_int_get(char *bin_number); //Получение big_int через строку

void big_int_print(big_int *number); //Вывод big_int

void big_int_dlz(big_int *n); //Удаляет лидирующие нули

char big_int_equal(big_int *n1, big_int *n2); //Сравнивает big_int

char big_int_equal_sgn(big_int *n1, big_int *n2); //Сравнивает учитывая знак

void big_int_free(big_int *n); //Освобождает память выделенную под big_int

void big_int_swap(big_int *n1, big_int *n2); //Меняет местами два big_int

big_int* big_int_copy(big_int *x); //Копирует один big_int в другой

big_int *big_int_add1(big_int *n1, big_int *n2); //Сложение big_int a = b + c

void big_int_add2(big_int *n1, big_int *n2); //Сложение big_int a += b

void big_int_shft_l(big_int *n1); //Сдвиг влево на один бит

void big_int_shft_r(big_int *n1); //Сдвиг вправо на один бит

void big_int_shft_l2(big_int *n1, int cnt); //Быстрый сдвиг влево

void big_int_shft_r2(big_int *n1, int cnt); //Быстрый сдвиг вправо

int bit_int_leq(big_int *n1, big_int *n2); //Сравнение n1<=n2

//! \brief Сравнение n1 >= n2
int bit_int_meq(big_int *n1, big_int *n2);

void big_int_sub2(big_int *n1, big_int *n2);