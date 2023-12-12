//
// Created by anton on 25.10.23.
//
#pragma once

typedef struct big_int{
    char sign;
    unsigned char *number;
    unsigned int length;
} big_int;


//! \brief Получение big_int через строку, big_int лежит в памяти перевернуто\n
//! \Example big_int_get("111101101")\n
//! number[0] = 237\n
//! number[1] = 1
big_int* big_int_get(char *bin_number);//

//! \brief Получение big_int через строку, продублированную loop раз
big_int *big_int_getloop(char *bin_number, int loop);//

//! \brief Переопределение big_int через строку bin_number
big_int *big_int_reget(big_int *num_1, char *bin_number);

//! \brief Получение big_int через число в десятичной системе счисления
big_int *big_int_get10(long long int num_1);//

//! \brief Вывод big_int
void big_int_print(big_int *number);//

//! \brief Выводит big_int в десятичной системе счисления
void big_int_print10(big_int *number);

//! \brief Переводит и возвращает big_int в десятичной системе счисления
signed long long int big_int_to10(big_int *number);

//! \brief Удаляет лидирующие нули
void big_int_dlz(big_int *number);//

//! \brief Сравнивает big_int
int big_int_equal(big_int *num_1, big_int *num_2);//

//! \brief Сравнивает учитывая знак
int big_int_equal_sgn(big_int *num_1, big_int *num_2);//

//! \brief Освобождает память выделенную под big_int
void big_int_free(big_int **number);//

//! \brief Освобождает выделенную память под несколько big_int
void big_int_free2(const unsigned int cnt_free, ...);//

//! \brief Меняет местами два big_int, работает за O(n)
void big_int_swap(big_int *num_1, big_int *num_2);//

//! \brief Копирует один big_int в другой
big_int* big_int_copy(big_int *number);//

//! \brief Сложение big_int\n
//! result = num_1 + num_2
big_int *big_int_add1(big_int *num_1, big_int *num_2);//

//! \brief Сложение big_int\n
//! num_1 += num_2
void big_int_add2(big_int *num_1, big_int *num_2);//

//! \brief Сдвиг влево на один бит
void big_int_shft_l(big_int *num_1);//

//! \brief Сдвиг вправо на один бит
void big_int_shft_r(big_int *num_1);//

//! \brief Быстрый сдвиг влево
void big_int_shft_l2(big_int *num_1, int cnt);//

//! \brief Быстрый сдвиг вправо
void big_int_shft_r2(big_int *num_1, int cnt);//

//! \brief num_1 \<= num_2
int big_int_leq(big_int *num_1, big_int *num_2);//

//! \brief Сравнение num_1 >= num_2
int big_int_meq(big_int *num_1, big_int *num_2);//

//! \brief Вычитание\n
//! result = num_1 - num_2
big_int *big_int_sub1(big_int *num_1, big_int *num_2);//

//! \brief Вычитание num_1 -= num_2
void big_int_sub2(big_int *num_1, big_int *num_2);//

//! \brief Меняет местами два big_int, работает за O(1)
void big_int_swap2(big_int *num_1, big_int *num_2);//

//! \brief Умножение за О(n^2)
big_int *big_int_mult1(big_int *num_1, big_int *num_2);//

//! \brief Берет срез относительно первого элемента
big_int *big_int_slice(const big_int *num_1, long int left_bound, long int right_bound);

//! \brief Умножение за О(n^1.5)
big_int *big_int_karatsuba_mult2(big_int *num_1, big_int *num_2);//

//! \brief Возведение в степень за О(logn)
big_int *big_int_pow(big_int *num_1, big_int *num_2);//

//! \brief Деление за О(n^2)
big_int *big_int_divide(big_int *dividend, big_int *denominator);//

//! \brief Взятие модуля за О(n^2)
big_int *big_int_mod(big_int *number, big_int *modulus);//

//! \brief Генерирует рандомное число заданной длины
big_int *big_int_rnd(int byte_count);

//! \brief Генерирует рандомное нечетное число заданной длины
big_int *big_int_rnd_odd(int byte_count);//

//! \brief Возведение в степень по модулю за О(logn)
big_int *big_int_pow_mod(big_int *num, big_int *power, big_int *modulus);//

//! \brief Тест числа на простоту за О(klogn), где n длина,
//! а k количество тестов, вероятность сгенерировать не простое = 0.25^k
int big_int_miller_rabin(big_int *number, int count_of_check);//

//! \brief Генерирует простое число, шанс что число не простое = 0.25^k
big_int *big_int_get_prime(int byte_len, int tst_count);//