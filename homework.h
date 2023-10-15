#ifndef __HOME_WORK__
#define  __HOME_WORK__
int value_num_byte(int start_value, int count);

void swap_value_or(int *number1, int *number2);

void swap_value_math(int *num1, int *num2);

int array_zero(int *mas);

int remainder1(int divider, int denominator);

int len_num(int num);

int sum_num(int num);

int luck_ticket();

int parenthesis_rule(char *stroka);

int is_it_prime(int num);

void print_prime_before(int num_before);

int str_in_str(char *stroka1, char *stroka2);

void print_array(int *mas, int length);

int *array_reverse(int *mas, int a, int b);

long long fibonachi_def(int n);

long long fibonachi_for(int n);

long long int_pow_n(long long m, long long n);

long long int_pow_logn(long long m, long long n);

void *buble_sort(int *mas, int len, char if1down);

void *selection_sort(int * mas, int len, char if1down);

void fill_mas_rand(int*mas, int len, int limit);

void sort_depend_first(int *mas, int len);

void q_sort(int *mas, int len);

void in_2_copy_1(int *mas1,int * mas2, int len);

char is_sort(int *mas, int len, int if1down);

char el_in_sort_mas(int *mas, size_t len_mas, int element);

void matching_elements(int *masn, size_t len_masn,
                       int *mask, size_t len_mask,
                       int *mas_new, size_t len_mas_new);

#endif