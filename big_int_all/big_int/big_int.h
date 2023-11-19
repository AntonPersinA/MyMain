//
// Created by anton on 25.10.23.
//
#pragma once

typedef struct big_int{
    char sign;
    unsigned char *number;
    unsigned int length;
} big_int;

//big_int *big_int_copy_part(big_int *n1)
//{
//
//    big_int *res = calloc(1, sizeof(big_int));
//    res->length = (n1->length / 2) + (n1->length & 1);
//    res->sign = n1->sign;
//    res->number = calloc(res->length, sizeof(unsigned char));
//    memcpy(res->number, n1->number - res->length-1, res->length);
//    res->number = (n1->number + n1->length / 2);
//    n1->length /= 2;
//    return res;
//}
//big_int *big_int_mult1(big_int *n1, big_int *n2) {
//    big_int *n3 = calloc(1, sizeof(big_int));
//    if (n3 == NULL)
//    {
//        printf("memory error in big_int_mult1\n");
//        return NULL;
//    }
//    n3->length = n1->length + n2->length;
//    n3->number = calloc(n3->length, sizeof(n3->number[0]));
//    if (n3->number == NULL)
//    {
//        printf("memory error in big_int_mult1\n");
//        return NULL;
//    }
//    n3->sign = '-';
//    if (n1->sign == n2->sign)
//    {
//        n3->sign = '+';
//    }
//    unsigned int mult, flag, k;
//    for (size_t i = 0; i < n1->length; ++i)
//    {
//        for (size_t j = 0; j < n2->length; ++j)
//        {
//            mult = n1->number[i] * n2->number[j];
//            flag = (n3->number[i + j] + mult) >> 8;
//            n3->number[i + j] += mult & 255;
//            k = 1;
//            while (flag)
//            {
//                unsigned int flag2 = (n3->number[i + j + k] + (flag)) >> 8;
//                n3->number[i + j + k] += (flag & 255);
//                flag = flag2;
//                k++;
//            }
//        }
//    }
//    big_int_dlz(n3);
//    return n3;
//}
//
//big_int *big_int_karatsuba_help(big_int *n1, big_int *n2)
//{
//    if (n1->length > 2 || n2->length > 2)
//    {
//        if (n1->length >= n2->length) {
//            n2->number = realloc(n2->number, n1->length);
//            for (int i = n2->length; i < n1->length; ++i)
//            {
//                n2->number[i] = 0;
//            }
//            n2->length = n1->length;
//            int domnoz = n1->length;
//            big_int *a1 = big_int_copy_part(n1);
//            big_int *b1 = big_int_copy_part(n2);
//            big_int *a1b1 = big_int_karatsuba(a1,b1);
//            big_int *a0b0 = big_int_karatsuba(n1,n2);
//            big_int *a1a0 = big_int_add1(a1,n1);
//            big_int *b1b0 = big_int_add1(b1,n2);
//            big_int *second = big_int_karatsuba(a1a0, b1b0);
//            big_int_dlz(b1b0);
//            big_int_sub2(second, a1b1);
//            big_int_sub2(second, a0b0);
//            big_int_shft_l2(a1b1, ((domnoz/2)*2)*8);
//            big_int_shft_l2(second, (domnoz/2)*8);
//            big_int *res = big_int_add1(a1b1, second);
//            big_int_add2(res, a0b0);
//            printf("res = ");
//            big_int_print(res);
//            n1->length =domnoz;
//            n2->length =domnoz;
//            return res;
//        }
//    }
//    big_int *res = big_int_mult1(n1,n2);
//    return res;
//}







//! \brief Получение big_int через строку
big_int* big_int_get(char *bin_number);

big_int *big_int_get_n(char *bin_number, int count);

big_int *big_int_getloop(char *bin_number, int loop);

//! \brief Переопределение big_int через строку
big_int *big_int_reget(big_int *n1, char *bin_number);

//! \brief Вывод big_int
void big_int_print(big_int *number);

//! \brief Удаляет лидирующие нули
void big_int_dlz(big_int *n);

//! \brief Сравнивает big_int
char big_int_equal(big_int *n1, big_int *n2);

//! \brief Сравнивает учитывая знак
char big_int_equal_sgn(big_int *n1, big_int *n2);

//! \brief Освобождает память выделенную под big_int
void big_int_free(big_int *n);

//! \brief Освобождает выделенную память под несколько big_int
void big_int_free2(char times, ...);

//! \brief Меняет местами два big_int
void big_int_swap(big_int *n1, big_int *n2);

//! \brief Перезаписывает один big_int в другой
big_int* big_int_copy(big_int *x);

//! \brief Сложение big_int a = b + c
big_int *big_int_add1(big_int *n1, big_int *n2);

//! \brief Сложение big_int a += b
void big_int_add2(big_int *n1, big_int *n2);

//! \brief Сдвиг влево на один бит
void big_int_shft_l(big_int *n1);

//! \brief Сдвиг вправо на один бит
void big_int_shft_r(big_int *n1);

//! \brief Быстрый сдвиг влево
void big_int_shft_l2(big_int *n1, int cnt);

//! \brief Быстрый сдвиг вправо
void big_int_shft_r2(big_int *n1, int cnt);

//! \brief n1 <= n2
int bit_int_leq(big_int *n1, big_int *n2);

//! \brief Сравнение n1 >= n2
int bit_int_meq(big_int *n1, big_int *n2);

//! \brief Вычитание a = b + c
big_int *big_int_sub1(big_int *n1, big_int *n2);

//! \brief Меняет местами два big_int O(1)
void big_int_swap2(big_int *n1, big_int *n2);

//! \brief Суммирует a += b
void big_int_add2(big_int *n1, big_int *n2);

//! \brief Вычитание a -= b
void big_int_sub2(big_int *n1, big_int *n2);

big_int *big_int_mult1(big_int *n1, big_int *n2);

big_int *big_int_karatsuba_help(big_int *n1, big_int *n2);

big_int *big_int_karatsuba_mult2(big_int *n1, big_int *n2);