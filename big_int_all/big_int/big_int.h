//
// Created by anton on 25.10.23.
//
#pragma once

typedef struct big_int{
    char sign;
    unsigned char *number;
    unsigned int length;
} big_int;


//! \brief Получение big_int через строку
big_int* big_int_get(char *bin_number);//

big_int *big_int_getloop(char *bin_number, int loop);//

//! \brief Переопределение big_int через строку
big_int *big_int_reget(big_int *n1, char *bin_number);

big_int *big_int_get10(long long int n1);//

//! \brief Вывод big_int
void big_int_print(big_int *number);//

int big_int_to10(big_int *number);

//! \brief Удаляет лидирующие нули
void big_int_dlz(big_int *n);//

//! \brief Сравнивает big_int
char big_int_equal(big_int *n1, big_int *n2);//

//! \brief Сравнивает учитывая знак
char big_int_equal_sgn(big_int *n1, big_int *n2);//

//! \brief Освобождает память выделенную под big_int
void big_int_free(big_int **n);//

//! \brief Освобождает выделенную память под несколько big_int
void big_int_free2(const unsigned int n0, ...);//

//! \brief Меняет местами два big_int, работает за O(n)
void big_int_swap(big_int *n1, big_int *n2);//

//! \brief Перезаписывает один big_int в другой
big_int* big_int_copy(big_int *x);//

//! \brief Сложение big_int a = b + c
big_int *big_int_add1(big_int *n1, big_int *n2);//

//! \brief Сложение big_int a += b
void big_int_add2(big_int *n1, big_int *n2);//

//! \brief Сдвиг влево на один бит
void big_int_shft_l(big_int *n1);//

//! \brief Сдвиг вправо на один бит
void big_int_shft_r(big_int *n1);//

//! \brief Быстрый сдвиг влево
void big_int_shft_l2(big_int *n1, int cnt);//

//! \brief Быстрый сдвиг вправо
void big_int_shft_r2(big_int *n1, int cnt);//

//n1 <= n2                                 ???????????????????????????????????????????
int big_int_leq(big_int *n1, big_int *n2);//

//! \brief Сравнение n1 >= n2
int big_int_meq(big_int *n1, big_int *n2);//

//! \brief Вычитание a = b + c
big_int *big_int_sub1(big_int *n1, big_int *n2);//

//! \brief Меняет местами два big_int, работает за O(1)
void big_int_swap2(big_int *n1, big_int *n2);//

//! \brief Суммирует a += b
void big_int_add2(big_int *n1, big_int *n2);//

//! \brief Вычитание a -= b
void big_int_sub2(big_int *n1, big_int *n2);//

//! \brief Умножение за О(n^2)
big_int *big_int_mult1(big_int *n1, big_int *n2);//

//! \brief Умножение за О(n^1.5)
big_int *big_int_karatsuba_mult2(big_int *n1, big_int *n2);//

//! \brief Возведение в степень за О(logn)
big_int *big_int_pow(big_int *n1, big_int *n2);//

//! \brief Деление за О(n^2)
big_int *big_int_divided(big_int *a, big_int *b);//

//! \brief Взятие модуля за О(n^2)
big_int *big_int_mod(big_int *a, big_int *b);//

//! \brief Генерирует рандомное число заданной длины
big_int *big_int_rnd(int byte_count);

//! \brief Генерирует рандомное нечетное число заданной длины
big_int *big_int_rnd_odd(int byte_count);//

//! \brief Возведение в степень по модулю за О(logn)
big_int *big_int_pow_mod(big_int *a, big_int *pow, big_int *modulus);//

//! \brief Тест числа на простоту за О(klogn), где n длина,
//! а k количество тестов, вероятность сгенерировать не простое = 0.25^k
int big_int_miller_rabin(big_int *n, int count_of_check);

big_int *big_int_prime_digit(int byte_len);





int big_int_primality_test(big_int *n, unsigned int tst_cnt);

big_int *big_int_get_prime(unsigned int len, unsigned int tst_cnt);

void big_int_div2_for_pow(const big_int *n1, big_int *n2, big_int *rmdr);