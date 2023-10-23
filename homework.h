//#ifndef __HOME_WORK__
//#define  __HOME_WORK__
#pragma once

int value_num_byte(int start_value, int count); //Возвращает будет 1 на месте count в двоичной СС

void swap_value_or(int *number1, int *number2); //Меняет значения переменных через ^

void swap_value_math(int *num1, int *num2); //Меняет значения переменных через +/-

int array_zero(int *mas, int len); //Возвращает колчество нулевых элементов в массиве

int remainder1(int divider, int denominator); //Остаток от деления

int len_num(int num); //Длина числа

int sum_num(int num); //Сумма цифр числа

int luck_ticket(); //Кол-во счастливых билетов

int parenthesis_rule(char *stroka); //Правильно ли закрыты скобки

int is_it_prime(int num); //Простое ли число

void print_prime_before(int num_before); //Простые числа до числа начиная с 2

int str_in_str(char *stroka1, char *stroka2); //Сколько раз строка 1 есть в строке 2

void print_array(int *mas, int length); //Выводит массив

int *array_reverse(int *mas, int a, int b); //Переворачиваает массив по индексам, все включительно

long long fibonachi_def(int n); //n-ое число фибоначи рекурсией

long long fibonachi_for(int n); //n-ое число фибоначи циклом for

long long int_pow_n(long long m, long long n); //Возвращает результат возведения числа m в степень n за О(n)

long long int_pow_logn(long long m, long long n); //Возвращает результат возведения числа m в степень n за О(logn)

void *buble_sort(int *mas, int len, char if1down); //Сортировка пузырьком сложности O(n^2)

void *selection_sort(int * mas, int len, char if1down); //Сортировка выбором сложности O(n^2)

void fill_mas_rand(int*mas, int len, int limit); //Заполняет массив рандомными значениями

void sort_depend_first(int *mas, int len); //Сортирует массив, относительно первого элемента, все что меньше слева, все что больше справа

void q_sort(int *mas, int len); //Быстра сортировка сложности O(logn)

void in_2_copy_1(int *mas1,int * mas2, int len); //В массив 2 копирует массив 1

char is_sort(int *mas, int len, int if1down); //Проверяет отсортирован ли массив

char el_in_sort_mas(int *mas, size_t len_mas, int element); //В отсортированном массиве проверяет наличие элемента

void matching_elements(int *masn, size_t len_masn,
                       int *mask, size_t len_mask,
                       int *mas_new, size_t len_mas_new); //В третий массив записывает элементы, находящиеся как в 1, так и во 2 массивах

int more_meet_el(int *mas, size_t len_mas); //Возвращает какой элемент встречается чаще всего в массиве

void insertion_sort(int *mas, int len_mas); //Сортировка вставкой сложности O(n^2)

void counting_sort(int *mas, size_t len_mas); //Сортировка подсчетом сложности O(n+k)

int compare_array(int *mas1, int *mas2, int len); //Сравнивает массивы

//#endif

//-O3 -march=native